/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-17
 * @brief       跑马灯 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
    //PE5 输出0
    GPIOE->ODR &= ~GPIO_ODR_ODR5;

    while (1)
    {
        
    }
}
















