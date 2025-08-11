#ifndef _W25Q128_H
#define _W25Q128_H
#include "SPI.h"

//初始化
void W25Q128_Init(void);

//读取ID

//开启写使能
void W25Q128_WriteEnable(void);

//关闭写使能
void W25Q128_WriteDisable(void);

//等待状态不为忙(busy)
void W25Q128_WaitForNotBusy(void);

//擦除段
void W25Q128_EraseSector(uint32_t* sector_address);

//写入
void W25Q128_WritePage(uint8_t block,uint8_t sector, uint8_t page,uint8_t* data, uint16_t length);
//读取
/*
    param1
*/
void W25Q128_Read(uint8_t block,uint8_t sector, uint8_t page,uint8_t innerAddr,uint8_t* buffer, uint16_t length);
#endif