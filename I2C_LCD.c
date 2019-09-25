/*
 * CLCD_4bit.c
 *
 * Created: 2019-09-11 오후 3:19:39
 *  Author: kccistc
 */ 
#include "I2C_LCD.h"

static uint8_t I2CData = 0;

void LCD_pulse_enable()
{
	I2CData |= (1<<LCD_ENABLE);
	I2C_TxByte(LCD_SLA, I2CData);
	_delay_ms(1);
	I2CData &= ~(1<<LCD_ENABLE);
	I2C_TxByte(LCD_SLA, I2CData);
	_delay_ms(1);
}

void LCD_WriteCommand(uint8_t cmdData)
{
	I2CData &= ~(1<<LCD_RS);
	I2CData = (I2CData & 0x0f) | (cmdData & 0xf0);
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
	
	I2CData = (I2CData & 0x0f) | ((cmdData & 0x0f)<<4);
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
}

void LCD_WriteCommandInit(uint8_t cmdData)
{
	I2CData &= ~(1<<LCD_RS);
	I2CData = (I2CData & 0x0f) | (cmdData & 0xf0);
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
}

void LCD_WriteData(uint8_t data)
{
	I2CData |= (1<<LCD_RS);
	I2CData = (I2CData & 0x0f) | (data & 0xf0);
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
	
	I2CData = (I2CData & 0x0f) | ((data & 0x0f)<<4);
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();	
}

void LCD_Clear()
{
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_BackLightOn()
{
	I2CData |= (1<<LCD_BACKLIGHT);
	I2C_TxByte(LCD_SLA, I2CData);
}

void LCD_BackLightOff()
{
	I2CData &= ~(1<<LCD_BACKLIGHT);
	I2C_TxByte(LCD_SLA, I2CData);
}

void LCD_Init()
{
	I2C_Init();
	_delay_ms(20);
	LCD_WriteCommandInit(0x30);
	_delay_ms(5);
	LCD_WriteCommandInit(0x30);
	_delay_us(200);
	LCD_WriteCommandInit(0x30);
	LCD_WriteCommandInit(COMMAND_4_BIT_MODE);
	LCD_WriteCommand(COMMAND_4_BIT_MODE);
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);
	LCD_BackLightOn();
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
	
}

void LCD_Write_string(char *string)
{
	for (uint8_t i=0; i<string[i]; i++)
	{
		LCD_WriteData(string[i]);
	}
}

void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_WriteCommand(command);
}
