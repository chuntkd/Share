/*
* Calculator.c
*
* Created: 2019-09-21 오후 12:15:18
* Author : kccistc
*/
#include "main.h"

volatile Queue KeyQue;

ISR(TIMER0_OVF_vect)
{
	uint8_t Key_Data = 0;/*Key_Cal_Data =0, Key_Reset_Data =0;*/
	if (Key_Data = Keypad_Scan())
	{
		Enqueue(&KeyQue, Key_Data);
	}
	/*
	if (Key_Cal_Data =  Keypad_Cal_Scan())
	{
		Enqueue(&KeyQue, Key_Cal_Data);
	}
	if (Key_Reset_Data =  Keypad_Reset_Scan())
	{
		Enqueue(&KeyQue, Key_Reset_Data);
	} */

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
	
	uint8_t KeyPadData ;
	uint8_t word[20];
	uint8_t cal[100];
	sei();
	
	while (1)
	{
		
		if (!QIsEmpty(&KeyQue))
		{
			KeyPadData = Dequeue(&KeyQue);
			if (KeyPadData>3)
			{
				KeyPadData = Change_Number(&KeyPadData);
			}
			
			*word = KeyPadData;
			
			sprintf(cal, "KeyPad : %s",word);
			LCD_goto_XY(0,0);
			LCD_Write_string(cal);
		}
		
	}
	return 0;
}

