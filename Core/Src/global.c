/*
 * global.c
 *
 *  Created on: Sep 25, 2024
 *      Author: hachi
 */


#include "global.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

uint8_t status;

uint8_t counters[2];
uint8_t red_duration, amber_duration, green_duration;
uint8_t temp_duration;
char lcd_line1[17];
char lcd_line2[17];
char uart_buffer[50];
uint8_t temp;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == USART2) {
		if(temp=='1') setButton(BT_MODE);
		else if(temp =='2') setButton(BT_SET);
		else if(temp =='3') setButton(BT_OK);
		else if(temp =='4') NVIC_SystemReset();
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}
void setup(){
  lcd_init();
  HAL_UART_Receive_IT(&huart2, &temp, 1);
  setTimer(0, 1000);
  setTimer(0, 2000);
  setTimer(1, 1000);
  setTimer(2, 1000);
  red_duration = 10;
  amber_duration = 2;
  green_duration = 8;
  status = INIT;
}
void lcd_send(){
	lcd_goto_XY(1, 0);
	lcd_send_string(lcd_line1);
	lcd_goto_XY(2, 0);
	lcd_send_string(lcd_line2);
	sprintf(uart_buffer,"%s,%s,%d#",lcd_line1,lcd_line2,status);
	HAL_UART_Transmit(&huart2, (uint8_t *) uart_buffer, strlen(uart_buffer), 1000);
}
void setCounter(uint8_t index, uint8_t value){
	setTimer(0, 1000);
	counters[index] = value;
	sprintf(lcd_line1,"     %d%d      <%d%d",counters[0]/10,counters[0]%10,counters[1]/10,counters[1]%10);
	sprintf(lcd_line2,"%d%d>      %d%d     ",counters[1]/10,counters[1]%10,counters[0]/10,counters[0]%10);
	lcd_send();

}
void counterRun(){
	if(isFlagTimer(0)){
		setTimer(0, 1000);
		counters[0]--;
		counters[1]--;
//		updateBuffer7SEG(counters[0], counters[1]);
		sprintf(lcd_line1,"     %d%d      <%d%d",counters[0]/10,counters[0]%10,counters[1]/10,counters[1]%10);
		sprintf(lcd_line2,"%d%d>      %d%d     ",counters[1]/10,counters[1]%10,counters[0]/10,counters[0]%10);
		lcd_send();
	}
}

void increaseDuration(uint8_t index){
	if(index == 0){
	}else if(index == 1){
		amber_duration++;
		if(amber_duration >= red_duration) amber_duration = red_duration - green_duration;
//		updateBuffer7SEG(4, amber_duration);
	}else if(index == 2){
		green_duration++;
		if(green_duration >= red_duration) green_duration = red_duration - amber_duration;
//		updateBuffer7SEG(5, green_duration);
	}
}
void led_on(uint8_t way, uint8_t led){
	if(way == WAY1){
		switch (led) {
			case RED:
				HAL_GPIO_WritePin(TLM0_A_GPIO_Port, TLM0_A_Pin, SET);
				HAL_GPIO_WritePin(TLM0_B_GPIO_Port, TLM0_B_Pin, SET);
				HAL_GPIO_WritePin(TLM1_A_GPIO_Port, TLM1_A_Pin, SET);
				HAL_GPIO_WritePin(TLM1_B_GPIO_Port, TLM1_B_Pin, SET);
				break;
			case AMBER:
				HAL_GPIO_WritePin(TLM0_A_GPIO_Port, TLM0_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM0_B_GPIO_Port, TLM0_B_Pin, SET);
				HAL_GPIO_WritePin(TLM1_A_GPIO_Port, TLM1_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM1_B_GPIO_Port, TLM1_B_Pin, SET);
				break;
			case GREEN:
				HAL_GPIO_WritePin(TLM0_A_GPIO_Port, TLM0_A_Pin, SET);
				HAL_GPIO_WritePin(TLM0_B_GPIO_Port, TLM0_B_Pin, RESET);
				HAL_GPIO_WritePin(TLM1_A_GPIO_Port, TLM1_A_Pin, SET);
				HAL_GPIO_WritePin(TLM1_B_GPIO_Port, TLM1_B_Pin, RESET);
				break;
			default:
				HAL_GPIO_WritePin(TLM0_A_GPIO_Port, TLM0_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM0_B_GPIO_Port, TLM0_B_Pin, RESET);
				HAL_GPIO_WritePin(TLM1_A_GPIO_Port, TLM1_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM1_B_GPIO_Port, TLM1_B_Pin, RESET);
				break;
		}
	}
	if(way == WAY2){
		switch (led) {
			case RED:
				HAL_GPIO_WritePin(TLM2_A_GPIO_Port, TLM2_A_Pin, SET);
				HAL_GPIO_WritePin(TLM2_B_GPIO_Port, TLM2_B_Pin, SET);
				HAL_GPIO_WritePin(TLM3_A_GPIO_Port, TLM3_A_Pin, SET);
				HAL_GPIO_WritePin(TLM3_B_GPIO_Port, TLM3_B_Pin, SET);
				break;
			case AMBER:
				HAL_GPIO_WritePin(TLM2_A_GPIO_Port, TLM2_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM2_B_GPIO_Port, TLM2_B_Pin, SET);
				HAL_GPIO_WritePin(TLM3_A_GPIO_Port, TLM3_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM3_B_GPIO_Port, TLM3_B_Pin, SET);
				break;
			case GREEN:
				HAL_GPIO_WritePin(TLM2_A_GPIO_Port, TLM2_A_Pin, SET);
				HAL_GPIO_WritePin(TLM2_B_GPIO_Port, TLM2_B_Pin, RESET);
				HAL_GPIO_WritePin(TLM3_A_GPIO_Port, TLM3_A_Pin, SET);
				HAL_GPIO_WritePin(TLM3_B_GPIO_Port, TLM3_B_Pin, RESET);
				break;
			default:
				HAL_GPIO_WritePin(TLM2_A_GPIO_Port, TLM2_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM2_B_GPIO_Port, TLM2_B_Pin, RESET);
				HAL_GPIO_WritePin(TLM3_A_GPIO_Port, TLM3_A_Pin, RESET);
				HAL_GPIO_WritePin(TLM3_B_GPIO_Port, TLM3_B_Pin, RESET);
				break;
		}
	}
}

