/*
 * traffic_light_fsm_set.c
 *
 *  Created on: Oct 1, 2024
 *      Author: hachi
 */

#include "traffic_light_fsm_set.h"
static void add_duration(int val){
	temp_duration+=val;
	if(temp_duration > 99) temp_duration = 0;
	sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
	lcd_send();
}

static uint8_t isValid(int red_dur, int amber_dur, int green_dur){
	if(green_dur > amber_dur && red_dur > green_dur) return 1;
	sprintf(lcd_line2,"Invalid value");
	lcd_send();
	return 0;
}
void traffic_light_fsm_set(){
	switch (status) {
		case SET_RED:
			if(isButtonPressed(BT_SET)){
				add_duration(1);
				setTimer(0, SETTING_TIMEOUT);
			}else if(isButtonHolding(BT_SET)){
				if(isFlagTimer(2)){
					setTimer(2, 200);
					add_duration(1);
				}
			}else if(isButtonPressed(BT_OK)){
				if(isValid(temp_duration, amber_duration, temp_duration - amber_duration)){
					status = INIT;
					red_duration = temp_duration;
					green_duration = temp_duration - amber_duration;
				}
			}else if(isFlagTimer(0) || isButtonPressed(BT_MODE)){
				status = INIT;
			}
			break;
		case SET_AMBER:
			if(isButtonPressed(BT_SET)){
				add_duration(1);
				setTimer(0, SETTING_TIMEOUT);
			}else if(isButtonHolding(BT_SET)){
				if(isFlagTimer(2)){
					setTimer(2, 200);
					add_duration(1);
				}
			}else if(isButtonPressed(BT_OK)){
				if(isValid(red_duration, temp_duration, red_duration - temp_duration )){
					status = INIT;
					amber_duration = temp_duration;
					green_duration = red_duration - temp_duration;
				}
			}else if(isFlagTimer(0) || isButtonPressed(BT_MODE)){
				status = INIT;
			}
			break;
		case SET_GREEN:
			if(isButtonPressed(BT_SET)){
				add_duration(1);
				setTimer(0, SETTING_TIMEOUT);
			}else if(isButtonHolding(BT_SET)){
				if(isFlagTimer(2)){
					setTimer(2, 200);
					add_duration(1);
				}
			}else if(isButtonPressed(BT_OK)){
				if(isValid(red_duration, red_duration - temp_duration, temp_duration )){
					status = INIT;
					green_duration = temp_duration;
					amber_duration = red_duration - temp_duration;
				}
			}else if(isFlagTimer(0) || isButtonPressed(BT_MODE)){
				status = INIT;
			}
			break;
		default:
			break;
	}
}
