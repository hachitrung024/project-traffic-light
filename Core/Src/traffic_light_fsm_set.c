/*
 * traffic_light_fsm_set.c
 *
 *  Created on: Oct 1, 2024
 *      Author: hachi
 */

#include "traffic_light_fsm_set.h"

void traffic_light_fsm_set(){
	switch (status) {
		case SET_RED:
			if(isButtonPressed(BT_SET)){
				temp_duration++;
				if(temp_duration > 99) temp_duration = 5;
//				updateBuffer7SEG(3, temp_duration);
				sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
				lcd_send();
				setTimer(0, SETTING_TIMEOUT);
			}
			if(isButtonHolding(BT_SET)){
				if(isFlagTimer(2)){
					setTimer(2, 200);
					temp_duration++;
					if(temp_duration > 99) temp_duration = 5;
//					updateBuffer7SEG(3, temp_duration);
					sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
					lcd_send();
				}
			}
			if(isButtonPressed(BT_OK)){
				red_duration = temp_duration;
				if(red_duration <= amber_duration) amber_duration = 2;
				green_duration = red_duration - amber_duration;
				status = INIT;
			}else if(isFlagTimer(0) || isButtonPressed(BT_MODE)){
				status = INIT;
			}
			break;
		case SET_AMBER:
			if(isButtonPressed(BT_SET)){
				temp_duration++;
				if(temp_duration >= green_duration) temp_duration = 2;
//				updateBuffer7SEG(3, temp_duration);
				sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
				lcd_send();
				setTimer(0, SETTING_TIMEOUT);
			}
			if(isButtonHolding(BT_SET)){
				if(isFlagTimer(2)){
					setTimer(2, 200);
					temp_duration++;
					if(temp_duration >= green_duration) temp_duration = 2;
//					updateBuffer7SEG(3, temp_duration);
					sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
					lcd_send();
				}
			}
			if(isButtonPressed(BT_OK)){
				amber_duration = temp_duration;
				green_duration = red_duration - amber_duration;
				status = INIT;
			}else if(isFlagTimer(0) || isButtonPressed(BT_MODE)){
				status = INIT;
			}
			break;
		case SET_GREEN:
			if(isButtonPressed(BT_SET)){
				temp_duration++;
				if(temp_duration >= red_duration) temp_duration = 3;
//				updateBuffer7SEG(3, temp_duration);
				sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
				lcd_send();
				setTimer(0, SETTING_TIMEOUT);
			}
			if(isButtonHolding(BT_SET)){
				if(isFlagTimer(2)){
					setTimer(2, 200);
					temp_duration++;
					if(temp_duration >= red_duration) temp_duration = 3;
//					updateBuffer7SEG(3, temp_duration);
					sprintf(lcd_line2,"Duration: %d%d    ", temp_duration/10, temp_duration%10);
					lcd_send();
				}
			}
			if(isButtonPressed(BT_OK)){
				green_duration = temp_duration;
				if(green_duration <= amber_duration) amber_duration = 2;
				red_duration = green_duration + amber_duration;
				status = INIT;
			}else if(isFlagTimer(0) || isButtonPressed(BT_MODE)){
				status = INIT;
			}
			break;
		default:
			break;
	}
}
