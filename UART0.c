/*
 * UART0.c
 *
 * Created: 2019-09-05 오전 11:39:06
 *  Author: kccistc
 */ 
#include "UART0.h"


void UART0_init(void)
{
	UBRR0H = 0; // 9,600 보율로 설정
	UBRR0L = 207;
	UCSR0A |= _BV(U2X1); // 2배속 모드
	// 비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR0C |= 0x06;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0); // 수신 , 송신 , 수신 인터럽트 
}

void UART0_transmit(char data)
{
	while(!(UCSR0A & (1<<UDRE0))); // 송신 가능 대기
	UDR0 = data; // 데이터 전송 ( 중요 )
}

unsigned char UART0_receive(void)
{
	while(!(UCSR0A & (1<<RXC0))); // 데이터 수신 대기 , 값이 들어오지 않으면 무한 루프
	return UDR0; // 들어온 값을 읽는다 
}

void UART0_printf_string(char *str)
{
	for(int i=0;str[i];i++) // str[i]가 0이면 계속 실행 
	UART0_transmit(str[i]); // i 는 주소에 있는 값
}

uint8_t UART0_isRxD()
{
	return (UCSR0A & (1<<RXC0));
}