#ifndef __PID1_H
#define __PID1_H
#include "main.h"

typedef struct
{
    float Target;
    float Actual;
    float Error0;
    float Error1;
    float Error2;
    float Kp,Ki,Kd;
    float Out;
} PID1_TypeDef;

void pid1_Init(PID1_TypeDef *pid, float Kp, float Ki, float Kd);
// 入参：实际速度 + 目标速度
float PID1_Calc(PID1_TypeDef *pid, float actual_speed, int16_t target_speed);

#endif
