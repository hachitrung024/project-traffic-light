/*
 * traffic_light_fsm_sel.c
 *
 *  Created on: Sep 26, 2024
 *      Author: hachi
 */


#include "traffic_light_fsm_sel.h"

void traffic_light_fsm_sel(){
	switch (status) {
		case INIT:
			if(1){
				status = SEL_AUTO;
				setCounter(0, 0);
				setCounter(1, 0);
				setTimer(0, SELECT_TIMEOUT);
				isButtonPressed(0);
				isButtonPressed(1);
				isButtonPressed(2);
				sprintf(lcd_line1,">AUTO RED  GREEN");
				sprintf(lcd_line2," MANU AMBER     ");
				lcd_send();
			}
			break;
		case SEL_AUTO:
			if(isFlagTimer(0) || isButtonPressed(BT_OK)){
				status = AUTO_RED_GREEN;
				led_on(WAY1, RED);
				led_on(WAY2, GREEN);
				setCounter(0, red_duration);
				setCounter(1, green_duration);
			}else if(isButtonPressed(BT_MODE)){
//				updateBuffer7SEG(2, 2);
				status = SEL_MAN;
				setTimer(0, SELECT_TIMEOUT);

				sprintf(lcd_line1," AUTO RED  GREEN");
				sprintf(lcd_line2,">MANU AMBER     ");
				lcd_send();
			}
			break;
		case SEL_MAN:
			if(isFlagTimer(0)){
				status = INIT;
			}
			if(isButtonPressed(BT_OK)){
				status = MAN_RED_GREEN;
				led_on(WAY1, RED);
				led_on(WAY2, GREEN);
				setTimer(0, SETTING_TIMEOUT);

				sprintf(lcd_line1,"     RED   GREEN");
				sprintf(lcd_line2,"GREEN   RED     ");
				lcd_send();
			}else if(isButtonPressed(BT_MODE)){
				status = SEL_RED;
				led_on(WAY1, RED);
				led_on(WAY2, RED);
//				updateBuffer7SEG(3, 3);
				setTimer(0, SELECT_TIMEOUT);

				sprintf(lcd_line1," AUTO>RED  GREEN");
				sprintf(lcd_line2," MANU AMBER     ");
				lcd_send();
			}

			break;
		case SEL_RED:
			if(isFlagTimer(0)){
				status = INIT;
			}
			if(isButtonPressed(BT_OK)){
				temp_duration = red_duration;
				status = SET_RED;
				led_on(WAY1, RED);
				led_on(WAY2, RED);
				setTimer(0, SETTING_TIMEOUT);
//				updateBuffer7SEG(3, red_duration);
				sprintf(lcd_line1,"Setting: RED    ");
				sprintf(lcd_line2,"Duration: %d%d    ", red_duration/10, red_duration%10);
				lcd_send();
			}else if(isButtonPressed(BT_MODE)){
				status = SEL_AMBER;
				led_on(WAY1, AMBER);
				led_on(WAY2, AMBER);
//				updateBuffer7SEG(4, 4);
				setTimer(0, SELECT_TIMEOUT);

				sprintf(lcd_line1," AUTO RED  GREEN");
				sprintf(lcd_line2," MANU>AMBER     ");
				lcd_send();
			}
			break;
		case SEL_AMBER:
			if(isFlagTimer(0)){
				status = INIT;
			}
			if(isButtonPressed(BT_OK)){
				temp_duration = amber_duration;
				status = SET_AMBER;
				led_on(WAY1, AMBER);
				led_on(WAY2, AMBER);
				setTimer(0, SETTING_TIMEOUT);
//				updateBuffer7SEG(4, amber_duration);
				sprintf(lcd_line1,"Setting: AMBER  ");
				sprintf(lcd_line2,"Duration: %d%d    ", amber_duration/10, amber_duration%10);
				lcd_send();
			}else if(isButtonPressed(BT_MODE)){
				status = SEL_GREEN;
				led_on(WAY1, GREEN);
				led_on(WAY2, GREEN);
//				updateBuffer7SEG(5, 5);
				setTimer(0, SELECT_TIMEOUT);
				sprintf(lcd_line1," AUTO RED >GREEN");
				sprintf(lcd_line2," MANU AMBER     ");
				lcd_send();
			}
			break;
		case SEL_GREEN:
			if(isFlagTimer(0)){
				status = INIT;
			}
			if(isButtonPressed(BT_OK)){
				temp_duration = green_duration;
				status = SET_GREEN;
				led_on(WAY1, GREEN);
				led_on(WAY2, GREEN);
				setTimer(0, SETTING_TIMEOUT);
//				updateBuffer7SEG(5, green_duration);
				sprintf(lcd_line1,"Setting: GREEN  ");
				sprintf(lcd_line2,"Duration: %d%d    ", green_duration/10, green_duration%10);
				lcd_send();
			}else if(isButtonPressed(BT_MODE)){
				status = INIT;
			}

			break;
		default:
			break;
	}
}
