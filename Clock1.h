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
#include "I2C_LCD.h"
#include "Buzzer.h"



enum{Ready,W,R,D,End} Laundry_Mode;




uint16_t Time();

void Set_Laundry_Mode_State(uint8_t LaundryMode);

uint8_t Get_Laundry_Mode_State();

void Display_Auto_LaundryTime(uint8_t state);
#endif /* CLOCK_H_ */