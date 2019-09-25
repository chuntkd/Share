/*
* Washing_Machine.c
*
* Created: 2019-09-20 오전 8:42:05
* Author : kccistc
*/

#include "main.h"

ISR(TIMER0_OVF_vect)
{
	Time();
}

int main(void)
{
	TCCR0 |= (1<<CS02);
	TIMSK |= (1<<TOIE0);
	TCNT0 = 256-250-1;
	UART0_init();
	Button_Init();
	LCD_Init();
	BuzzerInit();
	ADC_init();
	uint8_t read =0;
	char msg[20];
	sei();
	while (1)
	{
		/*read = read_ADC(0);
		_delay_ms(1000);
		sprintf(msg,"%d\n",read);
		UART0_printf_string(msg)*/;

		Mode_Change();
		switch(Machine_Mode)
		{
			
			uint8_t Dis[100] = {0};
			case Auto:
			Auto_Mode_Action(Auto_Mode);
			break;
			case Manual:
			Manual_Mode_Action(Manual_Mode);
			break;
			case Start:
			Display_LaundryTime(Laundry_Mode);
			break;
			case Stop:
			sprintf(Dis, "------ STOP ------"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Dis);
			break;
			case Emer:
			sprintf(Dis, "Please Close Door");
			LCD_goto_XY(1,0);
			LCD_Write_string(Dis);
			break;
			
			
		}
		
	}
}

