/*
 * I2C_Master.h
 *
 * Created: 2019-09-24 오전 11:28:47
 *  Author: kccistc
 */ 


#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_
#include <avr/io.h>

#define I2C_DDR		DDRD
#define I2C_SCL		0
#define I2C_SDA		1

#define I2C_WRITE	0
#define I2C_READ	1

void I2C_Init();
void I2C_TxByte(uint8_t deviceAddr, uint8_t data);
void I2C_RxBuffer(uint8_t deviceAddr, uint8_t regAddr, uint8_t *data,uint8_t length);
void I2C_TxBuffer(uint8_t deviceAddr, uint8_t regAddr, uint8_t *data,uint8_t length);


#endif /* I2C_MASTER_H_ */