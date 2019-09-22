/*
 * keypad.h
 *
 * Created: 2019-09-20 오후 3:15:49
 *  Author: kccistc
 */ 

#define F_CPU 16000000UL
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include <avr/io.h>
#include <util/delay.h>
#include "CLCD.h"

#define  KEYPAD_DDR DDRA
#define  KEYPAD_PORT PORTA
#define  KEYPAD_COL_PORT PORTA
#define  KEYPAD_ROW_PIN PINA


void KeyPadinit();

uint8_t Get_ButtonState(uint8_t row, uint8_t col);

uint8_t Get_Cal_ButtonState(uint8_t row, uint8_t col);
uint8_t Get_Reset_ButtonState(uint8_t row, uint8_t col);

uint8_t Keypad_Cal_Scan();

uint8_t Keypad_Reset_Scan();
uint8_t Keypad_Scan();
uint8_t Change_Number(uint8_t  num);



#endif /* KEYPAD_H_ */