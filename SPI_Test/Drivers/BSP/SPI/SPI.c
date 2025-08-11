#include "SPI.h"
 //SPI初始化函数
void SPI_Init(void){
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //使能GPIOB时钟

    //2.GPIO工作模式
    //CS:PB12 SCK:PB13 MOSI:PB15 通用推挽输出  CNF=00 MODE=11
    GPIOB->CRH &= ~GPIO_CRH_CNF12;
    GPIOB->CRH |= GPIO_CRH_MODE12;

    GPIOB->CRH &= ~GPIO_CRH_CNF13;
    GPIOB->CRH |= GPIO_CRH_MODE13;

    GPIOB->CRH &= ~GPIO_CRH_CNF15;
    GPIOB->CRH |= GPIO_CRH_MODE15;

    //MISO PB14 浮空输入 CNF=01 MODE=00
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_0;
    GPIOB->CRH &= ~GPIO_CRH_MODE14;

    //3.选择SPI的工作模式0 ：SCK空闲0
    SCK_LOW;  //SCK低电平空闲

    //4.片选不使能
    CS_HIGH;

    //5.延时等待
    SPI_DELAY; //延时5us
}

//数据传输的开始和结束
void SPI_Start(void){
    CS_LOW;  //片选使能
}
void SPI_Stop(void){
    CS_HIGH; //片选不使能
}

//主从设备交换一个字节的数据
uint8_t SPI_SwapByte(uint8_t translate_byte){
    //定义变量 保存接收到的字节
    uint8_t receive_byte = 0x00;

    //一次交换8位数据
    for(uint8_t i = 0; i<8; i++){
        //1.先准备要发送的数据(最高位)，送到MOSI上
        if(translate_byte & 0x80){
            MOSI_HIGH; //发送1
        }else{
            MOSI_LOW;  //发送0
        }
        //数据左移一位
        translate_byte <<= 1; 

        //2.拉高SCK，形成一个上升沿
        SCK_HIGH;
        SPI_DELAY;

        //3. 在MISO上采样 FLASH传来的数据
        receive_byte <<= 1; //接收数据左移一位
        if (MISO_READ)
        {
            receive_byte |= 0x01;
        }
        
        //4. 拉低时钟
        SCK_LOW;
        SPI_DELAY; 
    }

    return receive_byte;
}