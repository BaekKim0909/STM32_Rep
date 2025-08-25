#ifndef _ADC_H
#define _ADC_H

#include "stm32f1xx.h"

//初始化
void ADC1_Init(void);

//开启转换
void ADC1_StartConvert(void);

//返回转换后的模拟电压
double ADC1_ReadV(void);


#endif
