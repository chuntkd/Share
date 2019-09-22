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
#include "Mode.h"
#include "CLCD.h"

#define BUTTON_DDR	DDRA // 버튼 입력 설정
#define BUTTON_PIN	PINA // 버튼 입력 

#define BUTTON_MODE_DDR	DDRA 
#define BUTTON_MODE_PIN	PINA 
#define MODE_BUTTON		0 

#define BUTTON_STATE_DDR	DDRA 
#define BUTTON_STATE_MODE_PIN	PINA 
#define STATE_BUTTON		1

#define BUTTON_MANUAL_TIMEUP_DDR	DDRA 
#define BUTTON_MANUAL_TIMEUP_PIN	PINA 
#define MANUAL_TIMEUP_BUTTON		2

#define BUTTON_START_STOP_DDR	DDRA
#define BUTTON_START_STOP_PIN	PINA
#define START_STOP_BUTTON		3

/*
#define BUTTON_START_STOP_DDR	DDRA 
#define BUTTON_START_STOP_PIN	PINA 
#define DOWN_BUTTON		4*/

#define DEBOUNCE	20 // debounce time

void Button_Init(); // 버튼 설정
uint8_t Get_Mode_ButtonState();
uint8_t Get_State_ButtonState(); 
uint8_t Get_Manual_Timeup_ButtonState();
uint8_t Get_Start_Stop_ButtonState();
/*uint8_t Get_Down_ButtonState()*/;
uint8_t Get_ButtonState(uint8_t button, uint8_t *prevButtonState); // 버튼 동작

/*
void Auto_Mode_Button_Action();
void Manual_Mode_Button_Action();*/
void Mode_Change();
void Start_Stop();

#endif /* BUTTON_H_ */