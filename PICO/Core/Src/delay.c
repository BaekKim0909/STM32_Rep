#include "delay.h"
void delay_us(uint16_t us)
{
    uint16_t start = TIM14->CNT;
    while ((uint16_t)(TIM14->CNT - start) < us);
}
void TIM14_Init(void)
{
    // 1. ʹ�� TIM14 ʱ��
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

    // 2. ��λ TIM14
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM14RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM14RST;

    // 3. ����Ԥ��Ƶ�����ü���Ƶ��Ϊ 1 MHz (1us ��һ��)
    // ���� APB1 ��ʱ��ʱ���� 48 MHz
    TIM14->PSC = 48 - 1; // 48 ��Ƶ -> 1 MHz

    // 4. �Զ���װֵ�����ֵ��
    TIM14->ARR = 0xFFFF;

    // 5. ����������
    TIM14->CR1 |= TIM_CR1_CEN;
}

