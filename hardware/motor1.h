#ifndef __MOTOR1_H
#define __MOTOR1_H

#include "main.h"
void motor1_init(void);
void setpwm1_left(int16_t pwm);
void setpwm1_right(int8_t pwm);
void motor1_test(int8_t pwm_left,int8_t pwm_right);




#endif
