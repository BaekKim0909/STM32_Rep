#ifndef _SPI_H
#define _SPI_H
#include "stm32f103xe.h"
#include "delay.h"
//宏定义，不同引脚输出高低电平
//F_CS W25Q128的片选信号 PB12
#define CS_HIGH  (GPIOB->ODR |= GPIO_ODR_ODR12) 
#define CS_LOW   (GPIOB->ODR &= ~GPIO_ODR_ODR12)

//SCK PB13
#define SCK_HIGH (GPIOB->ODR |= GPIO_ODR_ODR13)
#define SCK_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR13)

//MOSI PB15
#define MOSI_HIGH (GPIOB->ODR |= GPIO_ODR_ODR15)
#define MOSI_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR15)

//读取MISO引脚信号 PB14
#define MISO_READ (GPIOB->IDR & GPIO_IDR_IDR14)

//SPI标准延迟时间
#define SPI_DELAY delay_us(5)

 //SPI初始化函数
void SPI_Init(void);

//数据传输的开始和结束
void SPI_Start(void);
void SPI_Stop(void);

//主从设备交换一个字节的数据
uint8_t SPI_SwapByte(uint8_t data);


#endif