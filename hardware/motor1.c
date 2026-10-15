#include "motor1.h"
#include "tim.h"
#include "oled.h"
void motor1_init()
{
HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
}


void setpwm1_left(int16_t pwm)
{
	if(pwm>0)
	{
	if(pwm>100) pwm=100;
		HAL_GPIO_WritePin(AIN1_left_GPIO_Port, AIN1_left_Pin, GPIO_PIN_SET);//改变电机旋转方向就改变电机极性set变成Reset
        HAL_GPIO_WritePin(AIN2_right_GPIO_Port, AIN2_right_Pin, GPIO_PIN_RESET);
		
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
	}
	else{
	  HAL_GPIO_WritePin(AIN1_left_GPIO_Port, AIN1_left_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AIN2_right_GPIO_Port, AIN2_right_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -pwm);
	}
}



void setpwm1_right(int8_t pwm)
{

    if(pwm >=0)
    {
        HAL_GPIO_WritePin(BIN2_left_GPIO_Port, BIN2_left_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIN2_right_GPIO_Port, BIN2_right_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
    }
    else 
    {
        HAL_GPIO_WritePin(BIN2_left_GPIO_Port, BIN2_left_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIN2_right_GPIO_Port, BIN2_right_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, -pwm);
    }
  
}


void motor1_test(int8_t pwm_left,int8_t pwm_right)
{
	setpwm1_left(30);
	OLED_ShowString(0,0,"pwmleft:%d",3);
	
	setpwm1_right(30);
	OLED_ShowString(1,0,"pwmleft:%d",3);
	
}

