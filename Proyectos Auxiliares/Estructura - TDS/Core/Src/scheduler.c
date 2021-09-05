/*
 * scheduler.c
 *
 *  Created on: 4 sept. 2021
 *      Author: saldi
 */

#include "scheduler.h"
#include <string.h>


void initScheduler(Scheduler *s, uint32_t max_len){

	s->max_len_tasks_list = max_len;
	s->len_tasks_list = 0;

	// Reservo memoria para la lista (array) de Tasks
	memset( s->tasks_list, 0, s->max_len_tasks_list*sizeof(Task) );

	// Seteo los punteros a función
	s->addTask = addTask;
	s->runTask = runTask;
	s->run = run;

	// Inicializo el timer cada 1 us
	initSchedulerTimer( 1 );

}

uint8_t addTask(Scheduler *s, void (*task)(void *p), void *param, uint32_t offset, uint32_t period, uint32_t bcet, uint32_t wcet){

	if( period == 0 || task == NULL || s->len_tasks_list >= s->max_len_tasks_list || bcet > wcet ){
		return -1;
	}

	// Seteo la tarea
	s->tasks_list[s->len_tasks_list].task = task;
	s->tasks_list[s->len_tasks_list].param = param;

	// Seteo período y offset
	s->tasks_list[s->len_tasks_list].period = period;
	s->tasks_list[s->len_tasks_list].offset = offset;
	s->tasks_list[s->len_tasks_list].periods_left = period;
	s->tasks_list[s->len_tasks_list].offset_left = offset;

	// Seteo las estadísticas
	s->tasks_list[s->len_tasks_list].stats.exec_time = 0;
	s->tasks_list[s->len_tasks_list].stats.exec_wcet = 0;
	s->tasks_list[s->len_tasks_list].stats.preconf_bcet = bcet;
	s->tasks_list[s->len_tasks_list].stats.preconf_wcet = (wcet != 0) ? wcet : _DEFAULT_SCHEDULER_WCET_;

	// Aumento el tamaño
	s->len_tasks_list ++;

	// Ordenar vector tasks_list por "offset" de menor a mayor

	return 0;
}

uint8_t runTask(Scheduler *s, uint8_t i_task_to_run){
	uint32_t et = 0;
	Task *task_to_run = &s->tasks_list[i_task_to_run];

	if( task_to_run->offset_left != 0 ){
		startSchedulerTimer();
		while( task_to_run->offset_left > getSchedulerTimer() );
		stopSchedulerTimer();
	}

	task_to_run->periods_left = task_to_run->period - 1;

	// Monitor execution
	startSchedulerTimer();
	task_to_run->task( task_to_run->param );
	et = stopSchedulerTimer();

	// Save stats
	task_to_run->stats.exec_time = et;
	if( task_to_run->stats.exec_wcet < et )
		task_to_run->stats.exec_wcet = et;

	// Check for SYSTEM FAILURE
	if( et < task_to_run->stats.preconf_bcet || et > task_to_run->stats.preconf_wcet )
		return -1;

	return 0;
}

void run(Scheduler *s){

	uint32_t i;
	uint8_t fail = 0;

	for( i = 0; i < s->len_tasks_list; i++ ){

		if( s->tasks_list[i].periods_left == 0 ){
			// Debe ejecutarse en este período
			s->tasks_list[i].periods_left = s->tasks_list[i].period - 1;

			fail = runTask( s, i );
			if( fail )
				break;

		}
		else
			s->tasks_list[i].periods_left --;

	}
	if( fail )
		scheduler_system_failure();

}

void scheduler_system_failure(void){
	while(1){
		// SCHEDULER SYSTEM FAILURE
	}
}

