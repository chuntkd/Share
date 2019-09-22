/*
* Mode.c
*
* Created: 2019-09-22 오후 5:32:06
*  Author: chunt
*/
#include "Mode.h"

static uint8_t Wash_Time = 0;
static uint8_t Rinse_Time = 0;
static uint8_t Dry_Time = 0;

void Set_Auto_Mode_State(uint8_t AutoMode)
{
	Auto_Mode = AutoMode;
}

uint8_t Get_Auto_Mode_State()
{
	return Auto_Mode;
}


void Set_Manual_Mode_State(uint8_t ManualMode)
{
	Manual_Mode = ManualMode;
}


uint8_t Get_Manual_Mode_State()
{
	return Manual_Mode;
}

void Set_Machine_Mode(uint8_t MachineMode)
{
	Machine_Mode = MachineMode;
}

uint8_t Get_Machine_Mode()
{
	return Machine_Mode;
}

void Set_Wash_Time(uint8_t time)
{
	Wash_Time = time;
}

uint8_t Get_Wash_Time()
{
	return Wash_Time * 10;
}

void Set_Rinse_Time(uint8_t time)
{
	Rinse_Time = time;
}

uint8_t Get_Rinse_Time()
{
	return Rinse_Time * 10;
}

void Set_Dry_Time(uint8_t time)
{
	Dry_Time = time;
}

uint8_t Get_Dry_TIme()
{
	return Dry_Time * 5;
}
void Auto_Mode_Action(uint8_t State)
{
	uint8_t Auto_word[100] = {0};
	if (Get_State_ButtonState())
	{
		
		if (Get_Auto_Mode_State() == STANDARD)
		{
			Set_Auto_Mode_State(QUICK);
			LCD_Clear();
		}
		else if (Get_Auto_Mode_State() == QUICK)
		{
			Set_Auto_Mode_State(WOOL);
			LCD_Clear();
		}
		else
		{
			Set_Auto_Mode_State(STANDARD);
			LCD_Clear();
		}
	}
	switch(State)
	{
		case STANDARD:
		
		sprintf(Auto_word, "Mode : Standard"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Auto_word);
		sprintf(Auto_word, "W:3 R:3 D:3"); // 알람 설정 값 출력
		LCD_goto_XY(1,0);
		LCD_Write_string(Auto_word);
		Set_Wash_Time(3);
		Set_Rinse_Time(3);
		Set_Dry_Time(3);
		
		break;
		
		case QUICK:
		
		sprintf(Auto_word, "Mode : Quick"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Auto_word);
		sprintf(Auto_word, "W:2 R:2 D:2"); // 알람 설정 값 출력
		LCD_goto_XY(1,0);
		LCD_Write_string(Auto_word);
		Set_Wash_Time(2);
		Set_Rinse_Time(2);
		Set_Dry_Time(2);
		
		break;
		
		case WOOL:
		
		sprintf(Auto_word, "Mode : Wool"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Auto_word);
		sprintf(Auto_word, "W:3 R:3 D:1"); // 알람 설정 값 출력
		LCD_goto_XY(1,0);
		LCD_Write_string(Auto_word);
		Set_Wash_Time(3);
		Set_Rinse_Time(3);
		Set_Dry_Time(1);
	
		break;
	}
}

void Manual_Mode_Action(uint8_t State)
{
	uint8_t Manual_word[100] = {0};
	static uint8_t Wash_Num = 0;
	static uint8_t Rinse_Num = 0;
	static uint8_t Dry_Num = 0;

	if (Get_State_ButtonState())
	{
		LCD_Clear();
		if (Get_Manual_Mode_State() == WASH)
		{
			Set_Manual_Mode_State(RINSE);
		}
		else if (Get_Manual_Mode_State() == RINSE)
		{
			Set_Manual_Mode_State(SPIN_DRY);
		}
		else
		{
			Set_Manual_Mode_State(WASH);
		}
	}
	switch(State)
	{
		case WASH:
		
		sprintf(Manual_word, "Mode : Wash Set"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Manual_word);
		if (Get_Manual_Timeup_ButtonState())
		{
			Wash_Num++;
			if (Wash_Num > 3)
			{
				Wash_Num = 0;
			}
		
			sprintf(Manual_word, "Wash Time : %02d",Wash_Num); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Manual_word);
			Set_Wash_Time(Wash_Num);
		}
		
		break;
		
		case RINSE:
		
		sprintf(Manual_word, "Mode : Rinse Set"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Manual_word);
		if (Get_Manual_Timeup_ButtonState())
		{
			Rinse_Num++;
			if (Rinse_Num > 3)
			{
				Rinse_Num = 0;
			}
			sprintf(Manual_word, "Rinse Time : %02d",Rinse_Num); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Manual_word);
			Set_Rinse_Time(Rinse_Num);
			
		}
		
		
		break;
		
		case SPIN_DRY:
		
		sprintf(Manual_word, "Mode : Spin-dry Set"); // 알람 설정 값 출력
		LCD_goto_XY(0,0);
		LCD_Write_string(Manual_word);
		if (Get_Manual_Timeup_ButtonState())
		{
			Dry_Num++;
			if (Dry_Num > 3)
			{
				Dry_Num = 0;
			}
			sprintf(Manual_word, "Dry Time : %02d",Dry_Num); // 알람 설정 값 출력
			LCD_goto_XY(1,0);
			LCD_Write_string(Manual_word);
			Set_Dry_Time(Dry_Num);
			
		}
	
		break;
	}
}