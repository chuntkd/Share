/*
 * Clock.h
 *
 * Created: 2019-09-06 오후 5:45:22
 *  Author: kccistc
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"
#include "button.h"
#include "util.h"
#include "CLCD.h"
#include "Buzzer.h"

enum{StopWatch,Alarm} Clock_Mode;
enum{Reset,Stop,Start} Stop_Watch_State;
enum{Minute,Second} Alarm_Set_State;
	



uint16_t Time();

uint8_t Get_StopWatch_State();
void Set_StopWatch_State(uint8_t StopWatchState);
uint8_t Get_Mode();
void Set_Mode(uint8_t ClockMode);

void Set_Alarm_State(uint8_t AlarmState);
uint8_t Get_Alarm_State();

void Set_Alarm_Minute(uint8_t Alarm_Minute);
uint8_t Get_Alarm_Set_Minute();
void Set_Alarm_Second(uint8_t Alarm_Second);
uint8_t Get_Alarm_Set_Second();

void StopWatch_Display();
void Alarm_Display();

void DisplayStopWatch(uint8_t StopwatchState);
void DisplayAlram(uint8_t StopwatchState);


void Clock_Action();
void LCD_Clock();
void Alarm_Buzzer();

#endif /* CLOCK_H_ */