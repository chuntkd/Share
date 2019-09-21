/*
 * button.h
 *
 * Created: 2019-09-03 오후 12:45:08
 *  Author: rhoblack@naver.com
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU	16000000UL
#include <avr/io.h>
#include "util.h"
#include "Clock1.h"


#define BUTTON_DDR	DDRA // 버튼 입력 설정
#define BUTTON_PIN	PINA // 버튼 입력 

#define BUTTON_AUTO_MODE_DDR	DDRA 
#define BUTTON_AUTO_MODE_PIN	PINA 
#define AUTO_MODE_BUTTON		0 

#define BUTTON_MANUAL_MODE_DDR	DDRA 
#define BUTTON_MANUAL_MODE_PIN	PINA 
#define MANUAL_MODE_BUTTON		1

#define BUTTON_MANUAL_TIMEUP_DDR	DDRA 
#define BUTTON_UP_PIN	PINA 
#define UP_BUTTON		1

#define BUTTON_RESET_DDR	DDRA 
#define BUTTON_RESET_PIN	PINA 
#define RESET_BUTTON		2

#define BUTTON_DOWN_DDR	DDRA 
#define BUTTON_DOWN_PIN	PINA 
#define DOWN_BUTTON		2

#define DEBOUNCE	20 // debounce time

void Button_Init(); // 버튼 설정
uint8_t Get_ClockMode_ButtonState();
uint8_t Get_Start_Stop_ButtonState(); 
uint8_t Get_Reset_ButtonState();
uint8_t Get_UP_ButtonState();
uint8_t Get_Down_ButtonState();
uint8_t Get_ButtonState(uint8_t button, uint8_t *prevButtonState); // 버튼 동작
void Mode_Button_Action();

#endif /* BUTTON_H_ */