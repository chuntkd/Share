/*
 * main.h
 *
 * Created: 2019-09-21 오후 12:17:20
 *  Author: kccistc
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "CLCD.h"
#include "circularQueue.h"
#include "ADC.h"


void Cal_Result(uint8_t cal);
/*uint8_t Change_Number(uint8_t  num);*/

#endif /* MAIN_H_ */