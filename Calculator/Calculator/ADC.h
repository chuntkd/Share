/*
 * ADC.h
 *
 * Created: 2019-09-20 오후 2:18:08
 *  Author: kccistc
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>


void ADC_init(void);
int read_ADC(uint8_t channel);

#endif /* ADC_H_ */