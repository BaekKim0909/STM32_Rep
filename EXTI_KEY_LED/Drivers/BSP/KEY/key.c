#include "key.h"
#include "delay.h"
#include "led.h"
void Key_Init(void){
    //1.配置时钟  KEY_UP按键对应PA0
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    //2. 配置GPIO工作模式下拉输入   上下拉CNF：10；输入MOD:00
    GPIOA->CRL &= ~GPIO_CRL_MODE0;

    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    GPIOA->CRL &= ~GPIO_CRL_CNF0_0;
    //配置下拉
    GPIOA->ODR &= ~GPIO_ODR_ODR0;


    //3.配置AFIO 引脚复用选择
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;

    //4.配置EXTI

    //开启EXTI0线上中断
    EXTI->IMR |= EXTI_IMR_MR0;
    //设置上升沿触发(因为配置了下拉输入，默认为0，按下KEY_UP后 PA0输入1  产生上升沿)
    EXTI->RTSR |= EXTI_RTSR_TR0;


    //5.NVIC配置
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI0_IRQn,3);
    NVIC_EnableIRQ(EXTI0_IRQn);

}

//中断服务函数
void EXTI0_IRQHandler(void){
    //1.清除中断挂起标志位
    EXTI->PR |= EXTI_PR_PR0;
    //2.消抖
    delay_ms(20);

    //判断如果依然保持高电平，就反转LED0
    if(GPIOA->IDR & GPIO_IDR_IDR0 !=0){
        LED0_TOGGLE();
        LED1_TOGGLE();
    }

}
