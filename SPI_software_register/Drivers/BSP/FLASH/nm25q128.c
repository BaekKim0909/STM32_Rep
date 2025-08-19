#include "nm25q128.h"
//初始化
void NM25Q128_Init(void){
    SPI_Init();
}

//读取ID
void NM25Q128_ReadID(uint8_t* ManufactureID,uint16_t* DeviceId){
    SPI_Start();
    //1.发送指令 Read Electronic manufacturer & Device ID
    SPI_SwapByte(0x90); // 指令
    SPI_SwapByte(0x00); // 地址高
    SPI_SwapByte(0x00); // 地址中
    SPI_SwapByte(0x00); // 地址低
    SPI_SwapByte(0xFF); // Dummy
    //2.获取制造商ID(为了读取数据，发什么不重要)
    *ManufactureID = SPI_SwapByte(0xFF);

    *DeviceId |= (SPI_SwapByte(0xFF)<<8);
    *DeviceId |= SPI_SwapByte(0xFF);

    SPI_Stop();
}
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
