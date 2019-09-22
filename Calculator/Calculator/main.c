/*
* Calculator.c
*
* Created: 2019-09-21 오후 12:15:18
* Author : kccistc
*/
#include "main.h"

volatile Queue KeyQue;
uint8_t calcul[4] = {'+','-','*','/'};
uint8_t KeyCalData = 0;

uint8_t Key_Num1 =0 ;
uint8_t Key_Num2 =0 ;
uint8_t Result ;


void Cal_Result(uint8_t cal)
{
	uint8_t Result_num[100] = {0,};

	switch(cal)
	{
		case 0:
		Result = Key_Num1 + Key_Num2;
		sprintf(Result_num, "Result : %d",Result);
		LCD_goto_XY(1,0);
		LCD_Write_string(Result_num);
		break;
		case 1:
		Result = Key_Num1 - Key_Num2;
		sprintf(Result_num, "Result : %d",Result);
		LCD_goto_XY(1,0);
		LCD_Write_string(Result_num);
		break;
		case 2:
		Result = Key_Num1 * Key_Num2;
		sprintf(Result_num, "Result : %d",Result);
		LCD_goto_XY(1,0);
		LCD_Write_string(Result_num);
		break;
		case 3:
		Result = Key_Num1 /Key_Num2;
		sprintf(Result_num, "Result : %d",Result);
		LCD_goto_XY(1,0);
		LCD_Write_string(Result_num);
		break;
	}
}

ISR(TIMER0_OVF_vect)
{
	uint8_t Key_Data = 0,Key_Cal_Data =0, Key_Reset_Data =0;
	if (Key_Data = Keypad_Scan())
	{
		Enqueue(&KeyQue, Key_Data);
	}
	

	if (Key_Cal_Data =  Keypad_Cal_Scan())
	{
		Enqueue(&KeyQue, Key_Cal_Data);
	}
	if (Key_Reset_Data =  Keypad_Reset_Scan())
	{
		Enqueue(&KeyQue, Key_Reset_Data);
	}

}

int main(void)
{
	TCCR0 |= (1<<CS02);
	TIMSK |= (1<<TOIE0);
	TCNT0 |= 5;
	ADC_init();
	KeyPadinit();
	LCD_Init();
	QueueInit(&KeyQue);
	
	uint8_t KeyPadData = 0;
	uint8_t num[100] = {0,};
	static uint8_t key_num_in = 0;
	static uint8_t key_cal_in = 0;
	uint8_t cal[100] = {0,};


	sei();
	
	while (1)
	{
		
		
		if (!QIsEmpty(&KeyQue))
		{
			KeyPadData = Dequeue(&KeyQue);
			
			
			if (KeyPadData <11)
			{
				if (KeyPadData == 10)
				{
					KeyPadData = 0;
				}
				
				if (key_num_in == 1 && key_cal_in == 1)
				{
					
					sprintf(num, "%d",KeyPadData);
					LCD_goto_XY(0,9);
					LCD_Write_string(num);
					Key_Num2 = KeyPadData;
					key_num_in = 0;
					key_cal_in = 0;
				}
				else
				{
										
					LCD_Clear();
					sprintf(num, "Cal: %d",KeyPadData);
					LCD_goto_XY(0,0);
					LCD_Write_string(num);
					Key_Num1 = KeyPadData;
					key_num_in = 1;
					
				}
				
				
			}
			
			if (KeyPadData >12 && key_num_in == 1)
			{
				KeyCalData = KeyPadData - 13;
				sprintf(cal, "%c",calcul[KeyCalData]);
				LCD_goto_XY(0,7);
				LCD_Write_string(cal);
				key_cal_in = 1;
				key_num_in = 1;
			}
			else if (KeyPadData == 11)
			{
				LCD_Clear();
				key_num_in =0;
				key_cal_in = 0;
			}
			
			else if (KeyPadData == 12)
			{
				
				Cal_Result(KeyCalData);
			}
			
			
			
		}
		
	}
	return 0;
}

