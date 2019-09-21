/*
 * keypad.c
 *
 * Created: 2019-09-20 오후 3:15:37
 *  Author: kccistc
 */ 
#include "keypad.h"



void KeyPadinit()
{
	KEYPAD_DDR = 0x0f;
	KEYPAD_PORT = 0xff; // 내부 pullup 동작
}

uint8_t Get_ButtonState(uint8_t row, uint8_t col)
{
	static uint8_t  prevState[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
	uint8_t curState;
		
	KEYPAD_COL_PORT |= 0x0f;
	KEYPAD_COL_PORT &= ~(1<<col);
	//_delay_us(1);
	for (int delay = 0; delay<20; delay++);

	curState = (KEYPAD_ROW_PIN & (1<<(row+4))) >> (row+4);
	if ((curState == 0) && ((prevState[(4 * row) + col +1]) == 1))
	{
		prevState[(4 * row) + col +1] = curState;
		return 0;
	}
	
	if ((curState == 1) && ((prevState[(4 * row) + col +1]) == 0))
	{
		prevState[(4 * row) + col +1] = curState;
		return ((4 * row) + col +1);
	}
	return 0;
}
/*
uint8_t Get_Cal_ButtonState(uint8_t row, uint8_t col)
{
	static uint8_t prevState[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
	uint8_t curState;
	
	KEYPAD_COL_PORT |= 0x0f;
	KEYPAD_COL_PORT &= ~(1<<(col+3));
	//_delay_us(1);
	for (int delay = 0; delay<20; delay++);

	curState = (KEYPAD_ROW_PIN & (1<<(row+4))) >> (row+4);
	if ((curState == 0) && ((prevState[(4 * row) + col ]) == 1))
	{
		prevState[(4 * row) + col ] = curState;
		return 0;
	}
	
	if ((curState == 1) && ((prevState[(4 * row) + col ]) == 0))
	{
		prevState[(4 * row) + col] = curState;
		return row+1;
	}
	return 0;
}

uint8_t Get_Reset_ButtonState(uint8_t row, uint8_t col)
{
	static uint8_t prevState[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	uint8_t curState;
	
	KEYPAD_COL_PORT |= 0x0f;
	KEYPAD_COL_PORT &= ~(1<<col);
	//_delay_us(1);
	for (int delay = 0; delay<20; delay++);

	curState = (KEYPAD_ROW_PIN & (1<<(row+7))) >> (row+7);
	if ((curState == 0) && ((prevState[(4 * row) + col ]) == 1))
	{
		prevState[(4 * row) + col ] = curState;
		return 0;
	}
	
	if ((curState == 1) && ((prevState[(4 * row) + col ]) == 0))
	{
		prevState[(4 * row) + col] = curState;
		return col+1;
	}
	return 0;
}

uint8_t Keypad_Cal_Scan()
{
	uint8_t ScanData = 0;
	
	for (uint8_t row =0; row<4; row++)
	{
		for (uint8_t col=0; col<1; col++)
		{
			ScanData = Get_Cal_ButtonState(row,col);
			if (ScanData)
			{
				return ScanData;
			}
			
			else if (ScanData == 1)
			{
				return '-';
			}
			else if (ScanData == 2)
			{
				return '*';
			}
			else
			{
				return '/';
			}
			
		}
	}
	return 0;
}
*/
uint8_t Keypad_Scan()
{
	uint8_t ScanData = 0;
	
	for (uint8_t row =0; row<4; row++)
	{
		for (uint8_t col=0; col<4; col++)
		{
			ScanData = Get_ButtonState(row,col);
			if (ScanData)
			{
				return ScanData;
			}
		}
	}
	return 0;
}
/*
uint8_t Keypad_Reset_Scan()
{
	uint8_t ScanData = 0;
	
	for (uint8_t row =0; row<1; row++)
	{
		for (uint8_t col=0; col<3; col++)
		{
			ScanData = Get_Reset_ButtonState(row,col);
				if (ScanData)
				{
					return ScanData;
				}
				else if (ScanData == 1)
				{
					return '0';
				}
				else if (ScanData == 2)
				{
					return '=';
				}
				
		}
	}
	return 0;
}*/

uint8_t Change_Number(uint8_t * num)
{
	switch(*num)
	{
		case 4:
		return "+";
		case 5:
		return 4;
		case 6:
		return 5;
		case 7:
		return 6;
		case 8:
		return "-";
		case 9:
		return 7;
		case 10:
		return 8;
		case 11:
		return 9;
		case 12:
		return "*";
		case 16:
		return "/";
		case 13:
		return "#";
		case 14:
		return "0";
		case 15:
		return "=";
	}
}

