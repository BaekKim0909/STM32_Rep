#include "spi.h"
//初始化
void SPI_Init(void){
    //1.开启时钟
    //开启GPIOB的时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    //开启SPI2的时钟
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

    //2.GPIO工作模式
    //25Q128的CS:PB12 通用推挽输出 MODE:11 CNF:00
    GPIOB->CRH |= GPIO_CRH_MODE12;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;

    // CLK:PB13  MOSI:PB15 复用推挽输出  MODE:11 CNF:10
    GPIOB->CRH |= GPIO_CRH_MODE13;
    GPIOB->CRH &= ~GPIO_CRH_CNF13;
    GPIOB->CRH |= GPIO_CRH_CNF13_1;

    GPIOB->CRH |= GPIO_CRH_MODE15;
    GPIOB->CRH &= ~GPIO_CRH_CNF15;
    GPIOB->CRH |= GPIO_CRH_CNF15_1;

    //MISO:PB14 浮空输入 MODE:00  CNF:01
    GPIOB->CRH &= ~GPIO_CRH_MODE14;
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_1;

    //3.SPI相关配置
    //3.1 配置STM32为主设备
    SPI2->CR1 |= SPI_CR1_MSTR;

    //3.2 使用软件片选信号
    SPI2->CR1 |= SPI_CR1_SSM;
    SPI2->CR1 |= SPI_CR1_SSI;

    //3.3 配置工作模式
    SPI2->CR1 &= ~SPI_CR1_CPOL;//时钟极性 为0
    SPI2->CR1 &= ~SPI_CR1_CPHA;//时钟相位 为0

    //3.4 配置时钟分频系数
    SPI2->CR1 &= ~SPI_CR1_BR;

    //3.5 设置数据帧格式
    SPI2->CR1 &= ~SPI_CR1_DFF;

    //3.6 配置高位先行
    SPI2->CR1 &= ~SPI_CR1_LSBFIRST;

    //3.7 SPI模块使能
    SPI2->CR1 |= SPI_CR1_SPE;


}

//数据传输的开始和结束
void SPI_Start(void){
    CS_LOW;
}
void SPI_Stop(void){
    CS_HIGH;
}
//4.主从设备交换一个字节的数据
uint8_t SPI_SwapByte(uint8_t TransmitByte){
    //4.1 将要发送的数据byte 写入发送缓冲区
    //4.1.1 等待发送缓冲区为空
    while ( (SPI2->SR & SPI_SR_TXE) == 0)
    {
        /* code */
    }
    //4.1.2 将发送的字节写入DR寄存器
    SPI2->DR = TransmitByte;

    //4.2 读取MISO发来的数据
    //4.2.1 等待接收缓冲区为非空
    while ((SPI2->SR & SPI_SR_RXNE) == 0)
    {
        /* code */
    }
    //4.2.2 从接收缓冲区读取数据，返回
    return (uint8_t)(SPI2->DR & 0xFF); 
}
