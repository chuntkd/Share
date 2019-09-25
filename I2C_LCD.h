/*
 * CLCD_4bit.h
 *
 * Created: 2019-09-11 오후 3:20:13
 *  Author: kccistc
 */ 


#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C_Master.h"

#define LCD_DATA_DDR	DDRC
#define LCD_DATA_PORT	PORTC
#define LCD_RS_DDR		DDRC
#define LCD_RS_PORT		PORTC
#define LCD_ENABLE_DDR	DDRC
#define LCD_ENABLE_PORT	PORTC

#define LCD_RS			0
#define LCD_RW			1
#define LCD_ENABLE		2
#define LCD_BACKLIGHT	3

#define LCD_SLA			0x27

#define COMMAND_CLEAR_DISPLAY	0x01
#define COMMAND_8_BIT_MODE		0X38
#define COMMAND_4_BIT_MODE		0X28
#define COMMAND_DISPLAY_ON		0X0C
#define COMMAND_DISPLAY_OFF		0X08
#define COMMAND_ENTRY_MODE		0X06

void LCD_pulse_enable();
void LCD_WriteCommand(uint8_t cmdData);
void LCD_WriteCommandInit(uint8_t cmdData);
void LCD_WriteData(uint8_t data);
void LCD_Clear();
void LCD_Init();
void LCD_Write_string(char *string);
void LCD_goto_XY(uint8_t row, uint8_t col);


#endif /* I2C_LCD_H_ */