#include "W25Q128.h"

//初始化
void W25Q128_Init(void)
{
    SPI_Init(); 
}

//开启写使能
void W25Q128_WriteEnable(void){
    SPI_Start();
    SPI_SwapByte(0x06);//发送写使能指令
    SPI_Stop();    
}

//关闭写使能
void W25Q128_WriteDisable(void){
    SPI_Start();
    SPI_SwapByte(0x04); //发送写禁止指令
    SPI_Stop();
}
//等待状态不为忙(busy)
void W25Q128_WaitForNotBusy(void);