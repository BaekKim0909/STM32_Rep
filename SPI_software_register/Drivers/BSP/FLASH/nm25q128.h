#ifndef _NM25Q128_H
#define _NM25Q128_H
#include "spi.h"

//初始化
void NM25Q128_Init(void);

//读取ID
void NM25Q128_ReadID(uint8_t* ManufactureID,uint16_t* DeviceId);
//开启写使能
void NM25Q128_WriteEnbale(void);
//关闭写使能
void NM25Q128_WriteDisable(void);
//等待状态不为忙
void NM25Q128_WaitNotBusy(void);
//擦除段(sector)，地址只需要块号和段号
void NM25Q128_EraseSector(uint8_t block,uint8_t sector);
//写入(页写)
void NM25Q128_PageWrite(uint8_t block,uint8_t sector,uint8_t page,uint8_t* data,uint16_t length);
//读取
void NM25Q128_PageRead(uint8_t block,uint8_t sector,uint8_t page,uint8_t innerAddr,uint8_t* buffer,uint16_t length);
#endif
