/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-17
 * @brief       ����� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


int main(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;

    GPIOB->CRL &= ~GPIO_CRL_CNF5;
    GPIOB->CRL |= GPIO_CRL_MODE5;

    GPIOE->CRL &= ~GPIO_CRL_CNF5;
    GPIOE->CRL |= GPIO_CRL_MODE5;

    GPIOB->ODR &= ~GPIO_ODR_ODR5;
    //PE5 ���0
    GPIOE->ODR &= ~GPIO_ODR_ODR5;

    while (1)
    {
        
    }
}
















