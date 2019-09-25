/*
 * UART0.h
 *
 * Created: 2019-09-05 오전 11:39:18
 *  Author: kccistc
 */ 


#ifndef UART0_H_
#define UART0_H_

#define F_CPU 16000000UL
#include <avr/io.h>

void UART0_init(void);
void UART0_transmit(char data);
unsigned char UART0_receive(void);
void UART0_printf_string(char *str);
uint8_t UART0_isRxD();

#endif /* UART0_H_ */