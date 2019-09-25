/*
* util.c
*
* Created: 2019-09-03 오후 12:49:40
*  Author: rhoblack@naver.com
*/

#include "util.h"

static uint32_t millisCount=0; 

uint32_t Get_Millis() 
{
	return millisCount;  // milliscount로 반환
}

void Inc_Millis() 
{
	millisCount++; // milliscount 추가 (1ms)
}

uint8_t Delay(uint32_t timeDelay) // Delay 부여
{
	static uint8_t delayStartFlag = 0; //delay 초기 상태 설정 (한번만)
	static uint32_t prevTime = 0; // 이전 시간 설정
	uint32_t curTime = 0; //현재 시간 설정
	
	curTime = Get_Millis(); //현재 시간 == millcount
	
	if (delayStartFlag == 0)  // delay 시작지점
	{
		delayStartFlag = 1;  
		prevTime = curTime; // 현재 시간 = 이전시간 ==> 시간 초기화 
	}
	else if (curTime - prevTime > timeDelay) // curtime - prevtime 이 설정한 시간이 되면
	{
		delayStartFlag = 0; //  
		return 1; // 출력
		
	}
	return 0;
}