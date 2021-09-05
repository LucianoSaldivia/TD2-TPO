/*
 * scheduler.h
 *
 *  Created on: 4 sept. 2021
 *      Author: saldi
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include <timer_scheduler.h>

#define _DEFAULT_SCHEDULER_WCET_  	((uint32_t) 600000)


typedef struct TaskStats{
	uint32_t exec_time;
	uint32_t exec_wcet;
	uint32_t preconf_bcet;
	uint32_t preconf_wcet;
} TaskStats;

typedef struct Task{
	void (*task)(void *p);
	void *param;
	uint32_t period;
	uint32_t periods_left;
	uint32_t offset;
	uint32_t offset_left;

	TaskStats stats;
} Task;

typedef struct Scheduler Scheduler;
struct Scheduler{
	/* Variables */
	uint32_t max_len_tasks_list;
	uint32_t len_tasks_list;
	Task *tasks_list;

	/* Funciones */
	uint8_t (*addTask)(Scheduler *self, void (*tarea)(void *p), void *param, uint32_t offset, uint32_t periodo, uint32_t bcet, uint32_t wcet);
	uint8_t (*runTask)(Scheduler *self, uint8_t i_task_to_run);
	void (*run)(Scheduler *self);
};


void initScheduler(Scheduler *scheduler, uint32_t max_len);
uint8_t addTask(Scheduler *scheduler, void (*tarea)(void *p), void *param, uint32_t offset, uint32_t periodo, uint32_t bcet, uint32_t wcet);
uint8_t runTask(Scheduler *scheduler, uint8_t i_task_to_run);
void run(Scheduler *scheduler);


void scheduler_system_failure(void);



#endif /* INC_SCHEDULER_H_ */
