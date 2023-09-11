#include "main.h"
#include "rtc_clock.h"

I2C_HandleTypeDef *_RTC_i2c;

void RTC_Init(I2C_HandleTypeDef *hi2c){
    _RTC_i2c = hi2c;
}

void RTC_SetAll(struct datetime *mdatetime){
    RTC_SetSecond(mdatetime->second);
    RTC_SetMinute(mdatetime->minute);
    RTC_SetHour(mdatetime->hour);
    RTC_SetDayOfWeek(mdatetime->dayotw);
    RTC_SetDate(mdatetime->day);
    RTC_SetMonth(mdatetime->month);
    RTC_SetYear(mdatetime->year);
}

void RTC_SetSecond(uint8_t second){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(second), 1, HAL_MAX_DELAY);
}

void RTC_SetMinute(uint8_t minute){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(minute), 1, HAL_MAX_DELAY);
}

void RTC_SetHour(uint8_t hour){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(hour), 1, HAL_MAX_DELAY);
}

void RTC_SetDayOfWeek(uint8_t dayotw){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(dayotw), 1, HAL_MAX_DELAY);
}

void RTC_SetDate(uint8_t date){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(date), 1, HAL_MAX_DELAY);
}

void RTC_SetMonth(uint8_t month){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(month), 1, HAL_MAX_DELAY);
}

void RTC_SetYear(uint16_t year){
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_EncodeBCD(year), 1, HAL_MAX_DELAY);
}

void RTC_GetAll(struct datetime *mdatetime) {
    mdatetime->second = RTC_GetSecond();
    mdatetime->minute = RTC_GetMinute();
    mdatetime->hour = RTC_GetHour();
    mdatetime->dayotw = RTC_GetDayOfWeek();
    mdatetime->day = RTC_GetDate();
    mdatetime->month = RTC_GetMonth();
    mdatetime->year = RTC_GetYear();
}

uint8_t RTC_GetSecond(void){
    uint8_t second;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_SECOND, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_SECOND, 1, &second, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(second);
}

uint8_t RTC_GetMinute(void){
    uint8_t minute;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_MINUTE, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_MINUTE, 1, &minute, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(minute);
}

uint8_t RTC_GetHour(void){
    uint8_t hour;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_HOUR, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_HOUR, 1, &hour, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(hour);
}

uint8_t RTC_GetDayOfWeek(void){
    uint8_t dayotw;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_DOW, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_DOW, 1, &dayotw, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(dayotw);
}

uint8_t RTC_GetDate(void){
    uint8_t date;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_DATE, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_DATE, 1, &date, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(date);
}

uint8_t RTC_GetMonth(void){
    uint8_t month;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_MONTH, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_MONTH, 1, &month, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(month);
}

uint16_t RTC_GetYear(void){
    uint8_t year;
    HAL_I2C_Master_Transmit(_RTC_i2c, RTC_I2C_ADDR, RTC_REG_YEAR, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(_RTC_i2c, RTC_I2C_ADDR + 1, RTC_REG_YEAR, 1, &year, 1, HAL_MAX_DELAY);
    return RTC_DecodeBCD(year);
}

uint8_t RTC_DecodeBCD(uint8_t buffer){
    return ((buffer & 0xf0) >> 4) * 10 + (buffer & 0x0F);
}

uint8_t RTC_EncodeBCD(uint8_t time){
    return ((time / 10) << 4) + (time % 10);
}
