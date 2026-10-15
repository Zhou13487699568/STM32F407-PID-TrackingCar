#ifndef __TRACK_SENSOR_H
#define __TRACK_SENSOR_H

#include "main.h"

extern float rho;
extern float track_Kp;
extern float track_Kd;
extern uint8_t track_offline_flag;

void Track_Sensor_Init(void);
void Sensor_UpdateRho(void);
float Track_PD_Calc(float target_rho, float actual_rho);

// 单路读取函数（调试打印用）
uint16_t L1_Get(void);
uint16_t L2_Get(void);
uint16_t L3_Get(void);
uint16_t L4_Get(void);
uint16_t L5_Get(void);
uint16_t L6_Get(void);
uint16_t L7_Get(void);
uint16_t L8_Get(void);

#endif

