/*
 * CLCD.c
 *
 * Created: 2019-09-11 오후 3:21:25
 *  Author: kccistc
 */ 

#include "CLCD.h"

char buff_Signal_State[20] = {0};

void LCD_Pulse_Enable()
{
	LCD_ENABLE_PORT |= (1<<LCD_ENABLE); // E ==> HIGH
	_delay_ms(1);
	LCD_ENABLE_PORT &= ~(1<<LCD_ENABLE); // E ==> LOW
	_delay_ms(1);
}

void LCD_WriteCommand(uint8_t cmdData) // 동작 명령어
{
	LCD_RS_PORT &= ~(1<<LCD_RS);
	LCD_DATA_PORT = (LCD_RS_PORT & 0X0f) | (cmdData & 0xf0); // Command 상위 4bit 입력
	LCD_Pulse_Enable();
	LCD_DATA_PORT = (LCD_RS_PORT & 0X0f) | ((cmdData & 0x0f)<<4); // Command 하위 4bit 입력
	LCD_Pulse_Enable();
}

void LCD_WriteData(uint8_t data) // 데이터 출력
{
	LCD_RS_PORT |= (1<<LCD_RS);
	LCD_DATA_PORT = (LCD_RS_PORT & 0X0f) | (data & 0xf0); // Data 상위 4bit
	LCD_Pulse_Enable();
	LCD_DATA_PORT = (LCD_RS_PORT & 0X0f) | ((data & 0x0f)<<4); // Data 하위 4bit
	LCD_Pulse_Enable();
}


void LCD_WriteCommand_Init(uint8_t cmdData) // 초기화 동작 명령어
{
	LCD_RS_PORT &= ~(1<<LCD_RS);
	LCD_DATA_PORT = (LCD_RS_PORT & 0X0f) | (cmdData & 0xf0); // Command 상위 4bit
	LCD_Pulse_Enable();
}


void LCD_Clear(void)
{
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY); 
	_delay_ms(2);
}

void LCD_Init() // LCD 기본 설정
{
	LCD_DATA_DDR = 0xff;
	LCD_RS_DDR |= (1<<LCD_RS);
	LCD_ENABLE_DDR |= (1<<LCD_ENABLE);
	
	_delay_ms(20);
	
	LCD_WriteCommand_Init(0x30);
	_delay_ms(5);
	LCD_WriteCommand_Init(0x30);
	_delay_ms(200);
	LCD_WriteCommand_Init(0x30);
	LCD_WriteCommand_Init(COMMAND_4_BIT_MODE); // Function Set (N: 디스플레이 행 수(N:0 ==> 1행, N:1 ==> 2행), F: 글자 크기), 설치된 LCD : N:1,F:0
	LCD_WriteCommand(DISPLAY_OFF); // Display off
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY); // Display Clear
	LCD_WriteCommand(COMMAND_ENTRY_MODE); // Entry mode set
	LCD_WriteCommand(DISPLAY_ON); // Display on
}


void LCD_Write_string(char *string)
{
	uint8_t i;
	for(i=0;string[i]; i++) //종료 문자를 만날 때까지
	LCD_WriteData(string[i]); // 문자 단위 출력
}

void LCD_goto_XY(uint8_t row, uint8_t col) // 데이터 행렬 배정
{
	col %= 16; // 최대 16글자
	row %= 2; // 2행
	
	// 첫째 라인 시작 주소는 0x00, 둘째 라인 시작 주소는 0x40
	uint8_t address = (0x40 * row) +col;
	uint8_t command = 0x80 +address;
	
	LCD_WriteCommand(command); // 커서 이동
}


