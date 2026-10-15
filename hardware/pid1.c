#include "pid1.h"
#include "motor1.h"
#include <math.h>

void pid1_Init(PID1_TypeDef *pid, float Kp, float Ki, float Kd)
{
	pid->Actual   = 0.0f;
	pid->Target   = 0.0f;
	pid->Error0   = 0.0f;
	pid->Error1   = 0.0f;
	pid->Error2   = 0.0f;
	pid->Out      = 0.0f;
	pid->Kp       = Kp;
	pid->Ki       = Ki;
	pid->Kd       = Kd;
}

float PID1_Calc(PID1_TypeDef *pid, float actual_speed, int16_t target_speed)
{
	pid->Actual = actual_speed;
	pid->Target = (float)target_speed;

	pid->Error2 = pid->Error1;
	pid->Error1 = pid->Error0;
	pid->Error0 = pid->Target - pid->Actual;

	float delta_u = pid->Kp*(pid->Error0-pid->Error1)
				  + pid->Ki*pid->Error0
				  + pid->Kd*(pid->Error0-2*pid->Error1+pid->Error2);

	if(delta_u > 12.0f)  delta_u = 12.0f;
	if(delta_u < -112.0f) delta_u = -12.0f;

	pid->Out += delta_u;
	if(pid->Out > 100.0f) pid->Out = 100.0f;
if(pid->Out <  -100.0f) pid->Out = -100.0f;

	return pid->Out;
}
