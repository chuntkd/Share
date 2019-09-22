/*
 * Mode.h
 *
 * Created: 2019-09-22 오후 5:31:48
 *  Author: chunt
 */ 


#ifndef MODE_H_
#define MODE_H_

#include <avr/io.h>
#include "button.h"
#include "CLCD.h"
#include "Clock1.h"

enum{Auto,Manual,Start,Stop} Machine_Mode;
enum{STANDARD,QUICK,WOOL} Auto_Mode;
enum{WASH,RINSE,SPIN_DRY} Manual_Mode;
	


void Set_Auto_Mode_State(uint8_t AutoMode);
void Set_Manual_Mode_State(uint8_t ManualMode);
void Set_Machine_Mode(uint8_t MachineMode);

uint8_t Get_Manual_Mode_State();
uint8_t Get_Auto_Mode_State();
uint8_t Get_Machine_Mode();

void Set_Wash_Time(uint8_t time);
void Set_Rinse_Time(uint8_t time);
void Set_Dry_Time(uint8_t time);

uint8_t Get_Wash_Time();
uint8_t Get_Rinse_Time();
uint8_t Get_Dry_TIme();

void Auto_Mode_Action(uint8_t State);
void Manual_Mode_Action(uint8_t State);

#endif /* MODE_H_ */