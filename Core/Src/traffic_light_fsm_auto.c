/*
 * traffic_light_fsm_auto.c
 *
 *  Created on: Sep 25, 2024
 *      Author: hachi
 */


#include "traffic_light_fsm_auto.h"

void traffic_light_fsm_auto(){
	switch (status) {
		case AUTO_RED_GREEN:
			counterRun();
			if(counters[1] == 0){
				status = AUTO_RED_AMBER;
				led_on(WAY1, RED);
				led_on(WAY2, AMBER);
				setCounter(1, amber_duration);
			}else if(isButtonPressed(0)){
				status = INIT;
			}
			break;
		case AUTO_RED_AMBER:
			counterRun();
			if(counters[1]==0){
				status = AUTO_GREEN_RED;
				led_on(WAY1, GREEN);
				led_on(WAY2, RED);
				setCounter(0, green_duration);
				setCounter(1, red_duration);
			}else if(isButtonPressed(0)){
				status = INIT;
			}
			break;
		case AUTO_GREEN_RED:
			counterRun();
			if(counters[0]==0){
				status = AUTO_AMBER_RED;
				led_on(WAY1, AMBER);
				led_on(WAY2, RED);
				setCounter(0, amber_duration);
			}else if(isButtonPressed(0)){
				status = INIT;
			}
			break;
		case AUTO_AMBER_RED:
			counterRun();
			if(counters[0]==0 || counters[1] == 0){
				status = AUTO_RED_GREEN;
				led_on(WAY1, RED);
				led_on(WAY2, GREEN);
				setCounter(0, red_duration);
				setCounter(1, green_duration);
			}else if(isButtonPressed(0)){
				status = INIT;
			}
			break;
		default:
			break;
	}
}
