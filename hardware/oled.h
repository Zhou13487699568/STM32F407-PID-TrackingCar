#ifndef __OLED_H
#define __OLED_H

#include "main.h"
#include "i2c.h"

#define OLED_ADDR   0x3C

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size);
void OLED_ShowNum(uint8_t x, uint8_t y, int num, uint8_t len, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, char *str, uint8_t size);

// 显示小车数据
void OLED_ShowCarData(int16_t speed_l, int16_t speed_r, int pwm_l, int pwm_r, float kp, float ki, float kd);

#endif

