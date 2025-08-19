#include "spi.h"
//初始化
void SPI_Init(void){
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    //2.GPIO工作模式
    //CS:PB12 CLK:PB13  MOSI:PB15 通用推挽输出 MODE:11 CNF:00
    GPIOB->CRH |= GPIO_CRH_MODE12;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;

    GPIOB->CRH |= GPIO_CRH_MODE13;
    GPIOB->CRH &= ~GPIO_CRH_CNF13;

    GPIOB->CRH |= GPIO_CRH_MODE15;
    GPIOB->CRH &= ~GPIO_CRH_CNF15;

    //MISO:PB14 浮空输入 MODE:00  CNF:01
    GPIOB->CRH &= ~GPIO_CRH_MODE14;
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_1;

    //3.选择SPI的工作模式0： SCK空闲0  片选信号默认不启用
    CLK_LOW;
    CS_HIGH;
    //4.延时
    SPI_DELAY;
}

//数据传输的开始和结束
void SPI_Start(void){
    CS_LOW;
}
void SPI_Stop(void){
    CS_HIGH;
}
//主从设备交换一个字节的数据
uint8_t SPI_SwapByte(uint8_t byte){
    //定义变量保存接收到的字节
    uint8_t receive_byte =0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        //1.先准备要发送的数据，送到MOSI上
        if (byte & 0x80)
        {
            /* code */
            MOSI_HIGH;
        }else{
            MOSI_LOW;
        }
        //左移一位
        byte <<= 1;

        //2.拉高时钟信号，形成第一个上升沿
        CLK_HIGH;
        SPI_DELAY;

        //3.在MISO上采样FLASH传来的数据
        //先左移
        receive_byte <<= 1;
        if (MISO_READ == GPIO_PIN_SET)
        {
            receive_byte |= 0x01;
        }
        //4.拉低时钟，为下一次数据传输做准备
        CLK_LOW;
        SPI_DELAY;
        
    }
    return receive_byte;
}
