#ifndef _ADC_H
#define _ADC_H

#include "stm32f1xx.h"

//��ʼ��
void ADC1_Init(void);

//����ת��
void ADC1_StartConvert(void);

//����ת�����ģ���ѹ
double ADC1_ReadV(void);


#endif
