/*
* Clock.c
*
* Created: 2019-09-06 오후 5:45:12
*  Author: kccistc
*/
#include "Clock1.h"

static uint16_t Run_Number = 0;


static uint16_t StopWatch_Number = 0;
static volatile uint8_t ss = 0, mm =0 , hh =0;
static volatile uint32_t millis = 0  ;
static volatile uint16_t timecount =0 , StopWatch_Count= 0 ;
static uint8_t Alarm_Set_Minute = 0 , Alarm_Set_Second = 0;
static uint16_t Alarm_minute = 0; // 알람 Minute 초기화
static uint16_t Alarm_second = 0; // 알람 Second 초기화
uint16_t Time()  // 시간 카운트 함수
{
	timecount++; // 시, 분, 초를 측정하기 위한 count
	Inc_Millis(); // 1ms 측정
	if (Get_StopWatch_State() == Start) // 스탑워치가 동작하면
	{
		StopWatch_Count ++;  // 스탑워치용 카운트 추가
		if (StopWatch_Count >= 10)
		{
			StopWatch_Count = 0;
			StopWatch_Number ++; //0.01초 측정 (스탑워치 출력값)
			if (StopWatch_Number >= 9999) //99.99초가 되면 초기화
			{
				StopWatch_Number = 0;
				
			}
		}
	}

	if (timecount >= 1000) //1초 측정
	{
		timecount = 0;
		ss++; //1초 추가
		if (ss>=60) // 1분 측정
		{
			ss = 0;
			mm ++;
		}
		if (mm >=60) // 1시간 측정
		{
			mm=0;
			hh++;
		}
		if (hh>=24) // 24시간이 되면 초기화
		{
			hh=0;
		}
		
	}
	
}


void Set_StopWatch_State(uint8_t StopWatchState) // 스탑워치 단계 설정
{
	Stop_Watch_State = StopWatchState;
}


uint8_t Get_StopWatch_State() // 스탑워치 상태  불러오기
{
	return Stop_Watch_State;
}

void Set_Mode(uint8_t ClockMode) // 시계 모드 설정
{
	Clock_Mode = ClockMode;
}

uint8_t Get_Mode() // 시계 모드 불러오기
{
	return Clock_Mode;
}


void Set_Alarm_State(uint8_t AlarmState) // 알람 분/초 상태 설정
{
	Alarm_Set_State = AlarmState;
}

uint8_t Get_Alarm_State() // 알람 분/초 상태 불러오기
{
	return Alarm_Set_State;
}

void Set_Alarm_Minute(uint8_t Alarm_Minute) // 알람 설정 Minute 저장
{
	Alarm_Set_Minute = Alarm_Minute;
}

uint8_t Get_Alarm_Set_Minute() // 알람 설정 Minute 불러오기
{
	return Alarm_Set_Minute;
}

void Set_Alarm_Second(uint8_t Alarm_Second) // 알람 설정 Second 저장
{
	Alarm_Set_Second = Alarm_Second;
}

uint8_t Get_Alarm_Set_Second() // 알람 설정 Second 불러오기
{
	return Alarm_Set_Second;
}
void LCD_Clock() // 현재 시간 LCD 출력
{
	char buff_Clock[20] = {0};
	
	sprintf(buff_Clock, "Time : %02d:%02d:%02d", hh,mm,ss );
	LCD_goto_XY(0,0);
	LCD_Write_string(buff_Clock);
}


void StopWatch_Display() // 스탑워치 LCD 출력
{
	char buff_Stop_Watch[20] = {0};
	sprintf(buff_Stop_Watch, "Stop : %d%d : %d%d",Run_Number/1000 , Run_Number/100%10 ,Run_Number/10%10 ,Run_Number%10); // 스탑워치 값 출력
	LCD_goto_XY(1,0);
	LCD_Write_string(buff_Stop_Watch);
}

void Alarm_Display() // 알람 LCD 출력
{
	char buff_Alarm[20] = {0};
	sprintf(buff_Alarm, "ALAM : %d%d : %d%d",Alarm_minute/10%10 , Alarm_minute%10 ,Alarm_second/10%10 ,Alarm_second%10); // 알람 설정 값 출력
	LCD_goto_XY(1,0);
	LCD_Write_string(buff_Alarm);
}

void DisplayStopWatch(uint8_t StopwatchState) // 스탑워치 출력
{
	
	
	if(Get_Mode() == StopWatch)
	{
		if (Get_Start_Stop_ButtonState()) // 버튼 입력
		{
			
			if (Get_StopWatch_State() == Stop)  // 단계가 Stop 이면
			{
				Set_StopWatch_State(Start); // Start으로 변환
			}
			else
			{
				Set_StopWatch_State(Stop); // Stop 으로 변환
			}
			
		}
		if (Get_Reset_ButtonState()) // 리셋 버튼 입력
		{
			Set_StopWatch_State(Reset); // Reset으로 변환
		}
	}
	
	switch(StopwatchState) // 스탑워치 동작
	{
		static uint16_t curnumber = 0; // 현재 시간 저장 초기화
		
		case Reset:  // Reset 상태 동작
		curnumber = 0; // 현재 시간 저장 값 초기화
		StopWatch_Number = 0; // 스탑워치 출력값 초기화
		Set_StopWatch_State(Stop); // Stop 상태로 변경
		break;
		
		case Stop: // Stop 상태 동작
		Run_Number = curnumber; // 스탑워치 표시값 = 현재 시간 저장값
		
		StopWatch_Display();
		break;
		
		case  Start: // Start 상태 동작
		Run_Number = StopWatch_Number ; // 스탑워치 표시값 = 스탑워치 출력값(0.01초 측정값)
		StopWatch_Display();
		curnumber = Run_Number; // 현재 시간 저장
		break;
	}
}

void DisplayAlram(uint8_t Alarm_Set_State) // 알람 화면 출력
{
	

	switch(Alarm_Set_State) // 알람 설정 동작
	{
		
		case Minute: // Minute 설정
		if (Get_UP_ButtonState()) // 증가 버튼 입력
		{
			
			if (Alarm_minute > 59) 
			{
				Alarm_minute = 0;
			}
			else
			{
				Alarm_minute++; // Minute 증가
			}
		
		}
		if (Get_Down_ButtonState()) // 감소 버튼 입력
		{
			
			if (Alarm_minute == 0)
			{
				Alarm_minute = 59;
			}
			else
			{
				Alarm_minute--; // Minute 감소
			}
		}
		Alarm_Display();
		Set_Alarm_Minute(Alarm_minute); // 알람 설정 Minute 저장
		break;
		
		case  Second: // Second 설정
		if (Get_UP_ButtonState()) // 증가 버튼 입력
		{
			if (Alarm_second > 59)
			{
				Alarm_second = 0;
			}
			else
			{
				Alarm_second++; // Second 증가
			}
		}
		if (Get_Down_ButtonState()) // 감소 버튼 입력
		{
			if (Alarm_second == 0)
			{
				Alarm_second = 59;
			}
			else
			{
				Alarm_second --; // Second 감소
			}
		}
		Alarm_Display();
		Set_Alarm_Second(Alarm_second); // 알람 설정 Second 저장
		break;
	}
}

void Clock_Action() // 스탑워치 / 알람 설정 동작 
{
	switch(Clock_Mode)
	{
		case StopWatch:
		DisplayStopWatch(Stop_Watch_State); // 스탑워치 동작
		break;
		case Alarm:
		DisplayAlram(Alarm_Set_State); // 알람 설정 동작
		break;
	}
	
}

void Alarm_Buzzer()
{
	if ((Get_Alarm_Set_Minute() == mm) && (Get_Alarm_Set_Second() == ss) && !(mm==0 && ss == 0)) // 알람 설정 시간과 현재시간이 같아지면 
	{
		Buzzer(65);
		_delay_ms(100);
		
		Buzzer(73);
		_delay_ms(100);
		
		Buzzer(82);
		_delay_ms(100); // 부저 울림
		
		Buzzer(0);  // 부저 종료
	}
}





