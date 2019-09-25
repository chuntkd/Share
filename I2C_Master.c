/*
 * I2C_Master.c
 *
 * Created: 2019-09-24 오전 11:28:33
 *  Author: kccistc
 */ 
#include "I2C_Master.h"

static void I2C_Start();
static void I2C_RepeatedStart();
static void I2C_TxDeviceAddr(uint8_t SLA_W);
static void I2C_TxData(uint8_t data);
static void I2C_Stop();
static void I2C_RxAck(uint8_t *data);
static void I2C_RxNAck(uint8_t *data);


void I2C_Init()
{
	I2C_DDR |= (1<<I2C_SCL) | (1<<I2C_SDA);
	TWBR = 72;// 100kHz
}

void I2C_Start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2C_RepeatedStart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2C_RxAck(uint8_t *data)
{
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	*data = TWDR; // 포인터 변수 이므로 뭔본데이터에 직접적으로 데이터를 입력한다.
} 

void I2C_RxNAck(uint8_t *data)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	*data = TWDR; // 포인터 변수 이므로 뭔본데이터에 직접적으로 데이터를 입력한다.
}

void I2C_TxDeviceAddr(uint8_t SLA_W)
{
	TWDR = SLA_W;
	TWCR = (1<<TWINT) |	(1<<TWEN);
	while (!(TWCR & (1<<TWINT))); // Wait for TWINT flag set.
}

void I2C_TxData(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) |	(1<<TWEN);
	while (!(TWCR & (1<<TWINT))); // Wait for TWINT flag set.
}

void I2C_Stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void I2C_TxByte(uint8_t deviceAddr, uint8_t data)
{
	I2C_Start();
	I2C_TxDeviceAddr( (deviceAddr << 1) | I2C_WRITE);
	I2C_TxData(data);
	I2C_Stop();
}


void I2C_TxBuffer(uint8_t deviceAddr, uint8_t regAddr, uint8_t *data,uint8_t length)
{
	I2C_Start();
	I2C_TxDeviceAddr((deviceAddr << 1) | I2C_WRITE);
	I2C_TxData(regAddr);
	for (uint8_t i = 0; i<length; i++)
	{
		I2C_TxData(data[i]); // I2C_TxData(*(data+1));
	}
	I2C_Stop();
}

void I2C_RxBuffer(uint8_t deviceAddr, uint8_t regAddr, uint8_t *data,uint8_t length)
{
	I2C_Start();
	I2C_TxDeviceAddr((deviceAddr << 1) | I2C_WRITE);
	I2C_TxData(regAddr);
	I2C_RepeatedStart();
	I2C_TxDeviceAddr((deviceAddr << 1) | I2C_READ);
	for (uint8_t i = 0; i<length; i++)
	{
		if (i < length -1)
		{
			I2C_RxAck(&data[i]); 
		}
		else
		{
			I2C_RxNAck(&data[i]); 
		}
	}
	I2C_Stop();
}

void I2C_RxByte(uint8_t deviceAddr, uint8_t data)
{
	I2C_Start();
	I2C_TxDeviceAddr( (deviceAddr << 1) | I2C_READ);
	I2C_TxData(data);
	I2C_Stop();
}
