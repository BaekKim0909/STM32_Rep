#ifndef _DMA_H
#define _DMA_H
#include "stm32f1xx.h"

//初始化
void DMA1_Init(void);

//数据传输
void DMA1_Transmit(uint32_t srcAddr,uint32_t destAddr,uint16_t dataLen);

#endif