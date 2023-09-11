#ifndef RTC_CLOCK_H
#define RTC_CLOCK_H
#include "main.h"

#define RTC_I2C_ADDR 	(0x68<<1)
#define RTC_REG_SECOND 	0x00
#define RTC_REG_MINUTE 	0x01
#define RTC_REG_HOUR  	0x02
#define RTC_REG_DOW    	0x03
#define RTC_REG_DATE   	0x04
#define RTC_REG_MONTH  	0x05
#define RTC_REG_YEAR   	0x06
#define RTC_REG_CONTROL 	0x07
#define RTC_REG_UTC_HR	0x08
#define RTC_REG_UTC_MIN	0x09

extern I2C_HandleTypeDef *_RTC_i2c;

void RTC_Init(I2C_HandleTypeDef *hi2c);

struct datetime{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t dayotw;
	uint8_t day;
	uint8_t month;
	uint8_t year;
};

void RTC_SetAll(struct datetime *mdatetime);
void RTC_SetDate(uint8_t date);
void RTC_SetMonth(uint8_t month);
void RTC_SetYear(uint16_t year);
void RTC_SetDayOfWeek(uint8_t dayotw);
void RTC_SetHour(uint8_t hour);
void RTC_SetMinute(uint8_t minute);
void RTC_SetSecond(uint8_t second);

void RTC_GetAll(struct datetime *mdatetime);
uint8_t RTC_GetSecond(void);
uint8_t RTC_GetMinute(void);
uint8_t RTC_GetHour(void);
uint8_t RTC_GetDayOfWeek(void);
uint8_t RTC_GetDate(void);
uint8_t RTC_GetMonth(void);
uint16_t RTC_GetYear(void);

uint8_t RTC_DecodeBCD(uint8_t buffer);
uint8_t RTC_EncodeBCD(uint8_t time);

#endif
