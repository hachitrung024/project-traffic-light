/*
 * global.h
 *
 *  Created on: Sep 25, 2024
 *      Author: hachi
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

enum {
	INIT,
	SEL_AUTO,SEL_MAN,SEL_RED,SEL_AMBER,SEL_GREEN,
	AUTO_RED_GREEN,AUTO_RED_AMBER,AUTO_GREEN_RED,AUTO_AMBER_RED,
	MAN_RED_GREEN,MAN_RED_AMBER,MAN_GREEN_RED,MAN_AMBER_RED,
	SET_RED,SET_AMBER,SET_GREEN
}states;

enum{
	WAY1, WAY2,
	RED, AMBER, GREEN
}leds;

#define LED_ON	GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET

#define BT_MODE				0
#define BT_SET				1
#define BT_OK				2

#define SELECT_TIMEOUT	20000
#define MANUAL_TIMEOUT	30000
#define SETTING_TIMEOUT 25000
#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "i2c-lcd.h"
#include "stdio.h"
#include "string.h"
extern uint8_t status;
extern uint8_t counters[2];
extern uint8_t red_duration;
extern uint8_t amber_duration;
extern uint8_t green_duration;
extern uint8_t temp_duration;
extern char lcd_line1[17];
extern char lcd_line2[17];

void setup();
void setCounter(uint8_t index, uint8_t value);
void counterRun();
void increaseDuration(uint8_t index);
void led_on(uint8_t way, uint8_t led);
void lcd_send();
#endif /* INC_GLOBAL_H_ */
