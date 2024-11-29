/*
 * software_timer.h
 *
 *  Created on: Sep 25, 2024
 *      Author: hachi
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_TIMERS 4
#define COUNTER_TIMER 0
#define BLINK_TIMER	1
#define HOLD_TIMER 	2
#define LCD_TIMER 	3

#include "main.h"
uint8_t isFlagTimer(uint8_t index);
void setTimer(uint8_t index, uint32_t duration);
void timerInit(uint32_t prescaler, uint32_t period);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
