#include "key.h"
#include "delay.h"
#include "led.h"
void Key_Init(void){
    //1.����ʱ��  KEY_UP������ӦPA0
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    //2. ����GPIO����ģʽ��������   ������CNF��10������MOD:00
    GPIOA->CRL &= ~GPIO_CRL_MODE0;

    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    GPIOA->CRL &= ~GPIO_CRL_CNF0_0;
    //��������
    GPIOA->ODR &= ~GPIO_ODR_ODR0;


    //3.����AFIO ���Ÿ���ѡ��
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;

    //4.����EXTI

    //����EXTI0�����ж�
    EXTI->IMR |= EXTI_IMR_MR0;
    //���������ش���(��Ϊ�������������룬Ĭ��Ϊ0������KEY_UP�� PA0����1  ����������)
    EXTI->RTSR |= EXTI_RTSR_TR0;


    //5.NVIC����
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI0_IRQn,3);
    NVIC_EnableIRQ(EXTI0_IRQn);

}

//�жϷ�����
void EXTI0_IRQHandler(void){
    //1.����жϹ����־λ
    EXTI->PR |= EXTI_PR_PR0;
    //2.����
    delay_ms(20);

    //�ж������Ȼ���ָߵ�ƽ���ͷ�תLED0
    if(GPIOA->IDR & GPIO_IDR_IDR0 !=0){
        LED0_TOGGLE();
        LED1_TOGGLE();
    }

}
