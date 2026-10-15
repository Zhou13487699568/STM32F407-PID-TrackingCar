#include "track_sensor.h"

/**************** 全局变量定义 ****************/
float rho = 40.0f;
float track_Kp = 0.35f;
float track_Kd = 0.12f;
uint8_t track_offline_flag = 0;

static float last_track_err = 0.0f;
static uint8_t offline_cnt = 0;
#define OFFLINE_CHECK_CNT  3   // 脱线防抖：连续3次全白判定脱线

/**************** 底层单路读取（左→右 L1~L8） ****************/
// 0=黑线，1=白线
uint16_t L1_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0); }
uint16_t L2_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1); }
uint16_t L3_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2); }
uint16_t L4_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3); }
uint16_t L5_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4); }
uint16_t L6_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5); }
uint16_t L7_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6); }
uint16_t L8_Get(void) { return (uint16_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7); }

/**************** 更新rho偏移量 + 脱线检测 ****************/
void Sensor_UpdateRho(void)
{
    int8_t sum_weight = 0;
    uint8_t black_cnt = 0;
    float new_rho;

    // 八路对称权重：左四路负，右四路正
    if(L1_Get() == 0) { sum_weight -= 4; black_cnt++; }
    if(L2_Get() == 0) { sum_weight -= 3; black_cnt++; }
    if(L3_Get() == 0) { sum_weight -= 2; black_cnt++; }
    if(L4_Get() == 0) { sum_weight -= 1; black_cnt++; }
    if(L5_Get() == 0) { sum_weight += 1; black_cnt++; }
    if(L6_Get() == 0) { sum_weight += 2; black_cnt++; }
    if(L7_Get() == 0) { sum_weight += 3; black_cnt++; }
    if(L8_Get() == 0) { sum_weight += 4; black_cnt++; }

    // 全白脱线：防抖计数，避免短暂漏检误判
    if(black_cnt == 0)
    {
        offline_cnt++;
        if(offline_cnt >= OFFLINE_CHECK_CNT)
        {
            track_offline_flag = 1;
            rho = 40.0f;
        }
        return;
    }

    // 检测到黑线，清零脱线计数
    offline_cnt = 0;
    track_offline_flag = 0;

    // 加权映射到20~60范围，与原有参数体系完全兼容
    new_rho = 40.0f + (float)sum_weight / (float)black_cnt * 5.0f;

    // 一阶低通滤波：平滑转向，抑制蛇形抖动
    rho = 0.4f * new_rho + 0.6f * rho;
}

/**************** 循迹PD控制器 ****************/
float Track_PD_Calc(float target_rho, float actual_rho)
{
    float err = target_rho - actual_rho;
    float output = track_Kp * err + track_Kd * (err - last_track_err);
    last_track_err = err;

    // 固定差速限幅，防止转向过猛
    const float max_turn = 4.0f;
    if(output >  max_turn) output =  max_turn;
    if(output < -max_turn) output = -max_turn;

    return output;
}
