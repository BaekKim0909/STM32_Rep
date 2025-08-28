#ifndef _DELAY_H
#define _DELAY_H
#include "stm32f0xx_hal.h"

#include "main.h"
void TIM14_Init(void);
void delay_us(uint16_t us);
#endif
