#ifndef _DMA_H
#define _DMA_H
#include "stm32f1xx.h"

//��ʼ��
void DMA1_Init(void);

//���ݴ���
void DMA1_Transmit(uint32_t srcAddr,uint32_t destAddr,uint16_t dataLen);

#endif