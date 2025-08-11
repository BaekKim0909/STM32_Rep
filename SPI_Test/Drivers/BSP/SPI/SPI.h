#ifndef _SPI_H
#define _SPI_H
#include "stm32f103xe.h"
#include "delay.h"
//�궨�壬��ͬ��������ߵ͵�ƽ
//F_CS W25Q128��Ƭѡ�ź� PB12
#define CS_HIGH  (GPIOB->ODR |= GPIO_ODR_ODR12) 
#define CS_LOW   (GPIOB->ODR &= ~GPIO_ODR_ODR12)

//SCK PB13
#define SCK_HIGH (GPIOB->ODR |= GPIO_ODR_ODR13)
#define SCK_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR13)

//MOSI PB15
#define MOSI_HIGH (GPIOB->ODR |= GPIO_ODR_ODR15)
#define MOSI_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR15)

//��ȡMISO�����ź� PB14
#define MISO_READ (GPIOB->IDR & GPIO_IDR_IDR14)

//SPI��׼�ӳ�ʱ��
#define SPI_DELAY delay_us(5)

 //SPI��ʼ������
void SPI_Init(void);

//���ݴ���Ŀ�ʼ�ͽ���
void SPI_Start(void);
void SPI_Stop(void);

//�����豸����һ���ֽڵ�����
uint8_t SPI_SwapByte(uint8_t data);


#endif