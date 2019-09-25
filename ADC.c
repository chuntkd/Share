/*
 * ADC.c
 *
 * Created: 2019-09-20 오후 2:18:00
 *  Author: kccistc
 */ 
#include "ADC.h"

void ADC_init(void)
{
	ADMUX |= (0<< REFS1) | (1<< REFS0); // AVCC사용
	ADCSRA |= 0x07; // 분주비 128 : 125KHz , 50k ~ 200k 권장
	ADCSRA |= (1<<ADEN); // ADC 활성화
	ADCSRA |= (0<<ADFR); // Freerun 활성화, single 모드 (0) 권장
	
	//ADMUX = ((ADMUX & 0xE0) | channel);
	//ADCSRA |= (1<< ADSC); // ADC 시작
}

int read_ADC(uint8_t channel)
{
	ADMUX = ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1<< ADSC); // ADC 시작
	while(!(ADCSRA & (1 << ADIF)));
	
	return ADC;
}