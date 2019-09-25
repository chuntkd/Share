/*
* button.c
*
* Created: 2019-09-03 오전 10:34:03
* Author : rhoblack@naver.com
*/

#include "button.h"

static uint8_t Mode_Button_Num = 0;
static uint8_t Start_Stop_Button_Number = 0;

void Button_Init()
{
	BUTTON_MODE_DDR &= ~(1<<MODE_BUTTON); // AUTO 모드
	BUTTON_STATE_DDR &= ~(1<<STATE_BUTTON); // Manual 모드
	BUTTON_START_STOP_DDR &= ~(1<<START_STOP_BUTTON); // START/STOP
	BUTTON_MANUAL_TIMEUP_DDR &= ~(1<<MANUAL_TIMEUP_BUTTON); // 알람 설정 숫자 UP
	BUTTON_RESET_DDR &= ~(1<<RESET_BUTTON); // 알람 설정 숫자 DOWN*/
}

uint8_t Get_Mode_ButtonState()
{
	static uint8_t prevModeButtonState = 1; // 
	
	return Get_ButtonState(MODE_BUTTON, &prevModeButtonState); // 원래 메모리 값을 기억해서 변경하기 위해서 포인터로 버튼 상태를 포인터로 지정
	
}

uint8_t Get_State_ButtonState() // Manual 모드 
{
	static uint8_t prevStartStopButtonState = 1; 
	
	return Get_ButtonState(STATE_BUTTON, &prevStartStopButtonState); 
}

uint8_t Get_Manual_Timeup_ButtonState() // 스탑워치 RESET
{
	static uint8_t prevResetButtonState = 1; 
	
	return Get_ButtonState(MANUAL_TIMEUP_BUTTON, &prevResetButtonState); 
}

uint8_t Get_Start_Stop_ButtonState() // 알람 설정 숫자 UP
{
	static uint8_t prevUPButtonState = 1; 
	
	return Get_ButtonState(START_STOP_BUTTON, &prevUPButtonState); 
}


uint8_t Get_Reset_Button_State() // 알람 설정 숫자 DOWN
{
	static uint8_t prevDownButtonState = 1; 
	
	return Get_ButtonState(RESET_BUTTON, &prevDownButtonState); 
}

uint8_t Get_ButtonState(uint8_t button, uint8_t *prevButtonState) // 범용버튼 번호, 범용버튼 상태 
{
	uint8_t curButtonState = 1; // 현재 버튼 상태 = 1
	static uint32_t prevTime=0;  // 이전 시간 = 0 (처음만)
	uint32_t curTime; // 현재시간
	
	curButtonState = (BUTTON_PIN & (1<<button)) >> button; // 버튼이 입력을 받는다 
	if ( (curButtonState == 0) && (*prevButtonState == 1) ) // 버튼이 눌렸을때
	{
		*prevButtonState = curButtonState; 
		prevTime = Get_Millis();// millisCount;
		return 1;
	}
	else if ( (curButtonState == 1) && (*prevButtonState == 0) ) // 버튼을 때고있을때
	{
		curTime = Get_Millis();// millisCount; 
		if (curTime - prevTime > DEBOUNCE) // 20ms가 경과하면
		{
			*prevButtonState = curButtonState; 
			return 0; // 버튼이 떨어질때 동작
		}
		return 0;
	}
	
	return 0;
}


void Mode_Change()
{
	if (Get_Mode_ButtonState())
	{
		Mode_Button_Num++;
		LCD_Clear();
	}
	
	if (Get_Start_Stop_ButtonState())
	{
		Start_Stop_Button_Number++;
		LCD_Clear();
	}
	if (Mode_Button_Num == 1)
	{
		Set_Machine_Mode(Manual);
	}
	else if (Mode_Button_Num == 2)
	{
		Set_Machine_Mode(Auto);
		Mode_Button_Num = 0;
	}
	
	if (Start_Stop_Button_Number == 1)
	{
		Set_Machine_Mode(Start);
		Mode_Button_Num = 0;
	}
	else if (Start_Stop_Button_Number == 2)
	{
		Set_Machine_Mode(Stop);
		Start_Stop_Button_Number = 0;
		if (Get_Laundry_Mode_State() == End)
		{
			Mode_Button_Num = 0;
			Set_Machine_Mode(Auto);
			Set_Auto_Mode_State(STANDARD);
		}
	}
	if (Get_Reset_Button_State())
	{
		uint8_t Reset = 0;
		LCD_Clear();
		Set_Machine_Mode(Auto);
		Set_Auto_Mode_State(STANDARD);
		Start_Stop_Button_Number = 0;
		Mode_Button_Num = 0;
		Set_Laundry_Mode_State(Ready);
		Set_Wash_Time(Reset);
		Set_Rinse_Time(Reset);
		Set_Dry_Time(Reset);
		
		
	}
	
}

