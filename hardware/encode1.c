// encode1.c 定义全局变量
#include "encode1.h"
#include "main.h"
#include "tim.h"


uint16_t encode1_get(TIM_HandleTypeDef *htim)
{
	int16_t temp;
	temp = __HAL_TIM_GetCounter(htim);
	__HAL_TIM_SetCounter(htim, 0);
	return temp;
}