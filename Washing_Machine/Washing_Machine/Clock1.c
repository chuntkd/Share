/*
* Clock.c
*
* Created: 2019-09-06 오후 5:45:12
*  Author: kccistc
*/
#include "Clock1.h"

static uint8_t Run_Number = 0;



static volatile uint8_t ss = 0, mm =0 , hh =0;
static volatile uint32_t millis = 0  ;
static volatile uint16_t timecount =0  ;
static uint8_t Laundry_time = 0; 
uint16_t Time()  // 시간 카운트 함수
{
	
	Inc_Millis(); // 1ms 측정
	if (Get_Machine_Mode() == Start)
	{
		timecount++; // 시, 분, 초를 측정하기 위한 count
		if (timecount >= 1000)
		{
			timecount = 0;
			Laundry_time--;
			
		}
	}
}

void Set_Laundry_Mode_State(uint8_t LaundryMode)
{
	Laundry_Mode = LaundryMode;
}

uint8_t Get_Laundry_Mode_State()
{
	return Laundry_Mode;
}


void Display_LaundryTime(uint8_t state)
{
	char Remaining_Time[100] = {0};
		
	switch(state)
	{
		case Ready:
		Laundry_time = Get_Wash_Time();
		Set_Laundry_Mode_State(W);
		break;
		
		case W:
		if (Laundry_time <10)
		{
			
			sprintf(Remaining_Time, "----- WASH -----"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Remaining_Time);
			Run_Number = Laundry_time;
			sprintf(Remaining_Time, "Wash : %02d",Run_Number); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Remaining_Time);
			
		}
		else
		{
			sprintf(Remaining_Time, "----- WASH -----"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Remaining_Time);
			Run_Number = Laundry_time;
			sprintf(Remaining_Time, "Wash : %d",Run_Number); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Remaining_Time);
		}
		
		
		if (Laundry_time == 0)
		{
			Set_Laundry_Mode_State(R);
			Laundry_time = Get_Rinse_Time();
		}
		break;
		
		case R:
		if (Laundry_time <10)
		{
			
			sprintf(Remaining_Time, "---- RINSE ----"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Remaining_Time);
			Run_Number = Laundry_time;
			sprintf(Remaining_Time, "Rinse : %02d",Run_Number); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Remaining_Time);
			
		}
		else
		{
			sprintf(Remaining_Time, "---- RINSE ----"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Remaining_Time);
			Run_Number = Laundry_time;
			sprintf(Remaining_Time, "Rinse : %d",Run_Number); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Remaining_Time);
		}
		
		
		if (Laundry_time == 0)
		{
			Set_Laundry_Mode_State(D);
			Laundry_time = Get_Dry_TIme();
		}
		break;
		case D:
		if (Laundry_time <10)
		{
			
			sprintf(Remaining_Time, "--- SPIN-DRY ---"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Remaining_Time);
			Run_Number = Laundry_time;
			sprintf(Remaining_Time, "Spin-dry : %02d",Run_Number); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Remaining_Time);
			
		}
		else
		{
			sprintf(Remaining_Time, "--- SPIN-DRY ---"); // 알람 설정 값 출력
			LCD_goto_XY(0,0);
			LCD_Write_string(Remaining_Time);
			Run_Number = Laundry_time;
			sprintf(Remaining_Time, "Spin-dry : %d",Run_Number); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Remaining_Time);
		}
		
		
		if (Laundry_time == 0)
		{
			LCD_Clear();
			Set_Laundry_Mode_State(End);
		}
		break;
		
		case End:
		sprintf(Remaining_Time, "----- END ------"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Remaining_Time);
		sprintf(Remaining_Time, "Take Off Laundry"); // 알람 설정 값 출력
		LCD_goto_XY(1,0);
		LCD_Write_string(Remaining_Time);
		if (Get_Start_Stop_ButtonState())
		{
			LCD_Clear();
			Set_Machine_Mode(Auto);
			Set_Laundry_Mode_State(Ready);
		}
		break;
	}
	
}


