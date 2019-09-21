/*
 * CLCD.h
 *
 * Created: 2019-09-11 오후 3:20:58
 *  Author: kccistc
 */ 


#ifndef CLCD_H_
#define CLCD_H_
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "util.h"
#define LCD_DATA_DDR DDRD
#define LCD_DATA_PORT PORTD
#define LCD_RS_DDR DDRD
#define LCD_RS_PORT PORTD
#define LCD_ENABLE_DDR DDRD
#define LCD_ENABLE_PORT PORTD
#define LCD_RS		0
#define LCD_ENABLE  1

#define COMMAND_CLEAR_DISPLAY 0x01 //화면 지우는 명령어
#define COMMAND_4_BIT_MODE  0x28 // 4bit 사용 선언
#define DISPLAY_ON 0x0c
#define DISPLAY_OFF 0x08
#define COMMAND_ENTRY_MODE 0x06

void LCD_Pulse_Enable();
void LCD_WriteCommand(uint8_t cmdData); // 동작 명령어
void LCD_WriteData(uint8_t data); // 데이터 출력
void LCD_WriteCommand(uint8_t cmdData); // 동작 명령어
void LCD_WriteCommand_Init(uint8_t cmdData); // 동작 명령어
void LCD_Clear(void);
void LCD_Init();
void LCD_Write_string(char *string);
void LCD_goto_XY(uint8_t row, uint8_t col);
void LCD_State(uint8_t *eTrafficState);

#endif /* CLCD_H_ */