#ifndef _SPI_H
#define _SPI_H
#include "stm32f1xx.h"

//�궨��  ��ͬ��������ߵ͵�ƽ
#define CS_HIGH (GPIOB->ODR |= GPIO_ODR_ODR12)
#define CS_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR12)

#define CLK_HIGH (GPIOB->ODR |= GPIO_ODR_ODR13)
#define CLK_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR13)

#define MOSI_HIGH (GPIOB->ODR |= GPIO_ODR_ODR15)
#define MOSI_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR15)

//��ȡMISO�����ź�
#define MISO_READ HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)

//SPI��׼�ӳ�ʱ��
#define SPI_DELAY HAL_Delay(5)

//��ʼ��
void SPI_Init(void);

//���ݴ���Ŀ�ʼ�ͽ���
void SPI_Start(void);
void SPI_Stop(void);
//�����豸����һ���ֽڵ�����
uint8_t SPI_SwapByte(uint8_t byte);
#endif
