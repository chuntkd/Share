/*
 * Buzzer.h
 *
 * Created: 2019-09-16 오후 2:06:09
 *  Author: kccistc
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define  BUZZER_DDR DDRB
#define  BUZZER	7

void BuzzerInit();
void Buzzer(uint16_t hz);
void Buzzer_PowerOn();






#endif /* BUZZER_H_ */