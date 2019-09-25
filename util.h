/*
 * util.h
 *
 * Created: 2019-09-03 오후 12:59:28
 *  Author: rhoblack@naver.com
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

uint32_t Get_Millis(); // millis 설정
void Inc_Millis(); // milliscount 추가 함수 
uint8_t Delay(uint32_t timeDelay); // Delay 시간 함수


#endif /* UTIL_H_ */