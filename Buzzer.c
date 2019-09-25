/*
 * Buzzer.c
 *
 * Created: 2019-09-16 오후 2:05:57
 *  Author: kccistc
 */ 
#include "Buzzer.h"

void BuzzerInit()
{
	TCCR2 |= (0<<CS22) | (1<<CS21) | (1<<CS20);  // 분주비 64
	TCCR2 |= (1<<WGM21) | (0<<WGM20); // CTC
	BUZZER_DDR |= (1<<BUZZER); // Buzzer 출력 설정
}

void Buzzer(uint16_t hz)
{
	
	if (hz==0) 
	{
		TCCR2 &= ~((1<<COM21) | (1<<COM20)); // 0Hz에서는 출력x
	}
	else
	{
		TCCR2 |= (0<<COM21) | (1<<COM20); // 0Hz가 아니면 출력
		OCR2 = (uint8_t)(125000.0/hz) ; 
	}
}

void Buzzer_PowerOn() // 전원이 들어오면 소리 출력
{
	Buzzer(650);
	_delay_ms(500);
	
	Buzzer(587);
	_delay_ms(500);
	
	Buzzer(523);
	_delay_ms(500);
	
	Buzzer(587);
	_delay_ms(500);
	
	Buzzer(650);
	_delay_ms(500);
	
	Buzzer(650);
	_delay_ms(500);
	
	Buzzer(650);
	_delay_ms(500);
	Buzzer(0);
	
}
