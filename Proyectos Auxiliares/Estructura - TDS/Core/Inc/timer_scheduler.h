/*
 * timer_monitor.h
 *
 *  Created on: Jul 1, 2020
 *      Author: esala
 */

#ifndef INC_TIMER_SCHEDULER_H_
#define INC_TIMER_SCHEDULER_H_

	#include "stm32f1xx_hal.h"
	#include <stdint.h>


	void initSchedulerTimer(uint32_t divisor_us);
	void startSchedulerTimer(void);
	#define getSchedulerTimer()	(TIM2->CNT)
	uint32_t stopSchedulerTimer(void);

#endif /* INC_TIMER_SCHEDULER_H_ */
