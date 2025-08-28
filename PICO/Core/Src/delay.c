#include "delay.h"
void delay_us(uint16_t us)
{
    uint16_t start = TIM14->CNT;
    while ((uint16_t)(TIM14->CNT - start) < us);
}
void TIM14_Init(void)
{
    // 1. 使能 TIM14 时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

    // 2. 复位 TIM14
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM14RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM14RST;

    // 3. 设置预分频器，让计数频率为 1 MHz (1us 计一次)
    // 假设 APB1 定时器时钟是 48 MHz
    TIM14->PSC = 48 - 1; // 48 分频 -> 1 MHz

    // 4. 自动重装值（最大值）
    TIM14->ARR = 0xFFFF;

    // 5. 启动计数器
    TIM14->CR1 |= TIM_CR1_CEN;
}

