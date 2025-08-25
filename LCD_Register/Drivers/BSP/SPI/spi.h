#ifndef _SPI_H
#define _SPI_H
#include "stm32f1xx.h"

//宏定义  不同引脚输出高低电平
#define CS_HIGH (GPIOB->ODR |= GPIO_ODR_ODR12)
#define CS_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR12)

#define CLK_HIGH (GPIOB->ODR |= GPIO_ODR_ODR13)
#define CLK_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR13)

#define MOSI_HIGH (GPIOB->ODR |= GPIO_ODR_ODR15)
#define MOSI_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR15)

//读取MISO引脚信号
#define MISO_READ HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)

//SPI标准延迟时间
#define SPI_DELAY HAL_Delay(5)

//初始化
void SPI_Init(void);

//数据传输的开始和结束
void SPI_Start(void);
void SPI_Stop(void);
//主从设备交换一个字节的数据
uint8_t SPI_SwapByte(uint8_t byte);
#endif
