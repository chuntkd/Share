/*
* button.c
*
* Created: 2019-09-03 오전 10:34:03
* Author : rhoblack@naver.com
*/

#include "button.h"

static uint8_t Mode_Button_Number = 0;
void Button_Init()
{
	BUTTON_MODE_DDR &= ~(1<<MODE_BUTTON); // 모드 변경 버튼 입력 설정
	BUTTON_START_STOP_DDR &= ~(1<<START_STOP_BUTTON); // 스탑워치 START/STOP
	BUTTON_RESET_DDR &= ~(1<<RESET_BUTTON); // 스탑워치 RESET
	BUTTON_UP_DDR &= ~(1<<UP_BUTTON); // 알람 설정 숫자 UP
	BUTTON_DOWN_DDR &= ~(1<<DOWN_BUTTON); // 알람 설정 숫자 DOWN
}

uint8_t Get_ClockMode_ButtonState()
{
	static uint8_t prevModeButtonState = 1; // 
	
	return Get_ButtonState(MODE_BUTTON, &prevModeButtonState); // 원래 메모리 값을 기억해서 변경하기 위해서 포인터로 버튼 상태를 포인터로 지정
	
}

uint8_t Get_Start_Stop_ButtonState() // 스탑워치 START/STOP
{
	static uint8_t prevStartStopButtonState = 1; 
	
	return Get_ButtonState(START_STOP_BUTTON, &prevStartStopButtonState); 
}

uint8_t Get_Reset_ButtonState() // 스탑워치 RESET
{
	static uint8_t prevResetButtonState = 1; 
	
	return Get_ButtonState(RESET_BUTTON, &prevResetButtonState); 
}

uint8_t Get_UP_ButtonState() // 알람 설정 숫자 UP
{
	static uint8_t prevUPButtonState = 1; 
	
	return Get_ButtonState(UP_BUTTON, &prevUPButtonState); 
}

uint8_t Get_Down_ButtonState() // 알람 설정 숫자 DOWN
{
	static uint8_t prevDownButtonState = 1; 
	
	return Get_ButtonState(DOWN_BUTTON, &prevDownButtonState); 
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
		return 0;
	}
	else if ( (curButtonState == 1) && (*prevButtonState == 0) ) // 버튼을 때고있을때
	{
		curTime = Get_Millis();// millisCount; 
		if (curTime - prevTime > DEBOUNCE) // 20ms가 경과하면
		{
			*prevButtonState = curButtonState; 
			return 1; // 버튼이 떨어질때 동작
		}
		return 0;
	}
	
	return 0;
}

void Mode_Button_Action() // 모드 변경, 분/초 변경 버튼 동작
{
	if (Get_ClockMode_ButtonState()) // 버튼 입력
	{
		Mode_Button_Number ++; 
	}
	
	if (Mode_Button_Number == 1) // 버튼이 첫번째로  눌리면
	{
		Set_Mode(Alarm); // 모드를 알람으로 바꿈
		Set_Alarm_State(Minute); // 알람 설정(분)
	}
	if (Mode_Button_Number == 2) // 버튼이 두번째 눌리면
	{
		Set_Alarm_State(Second); // 알람 설정(초)
	}
	if (Mode_Button_Number == 3) // 버튼이 세번째 눌리면
	{
		Set_Mode(StopWatch); // 스탑워치 모드로 변경
		Set_StopWatch_State(Reset); // 스탑워치 상태(리셋)변경
		Mode_Button_Number = 0; // 버튼 입력 초기화
	}

}
