#include "nm25q128.h"
//��ʼ��
void NM25Q128_Init(void){
    SPI_Init();
}

//��ȡID
void NM25Q128_ReadID(uint8_t* ManufactureID,uint16_t* DeviceId){
    SPI_Start();
    //1.����ָ�� Read Electronic manufacturer & Device ID
    SPI_SwapByte(0x90); // ָ��
    SPI_SwapByte(0x00); // ��ַ��
    SPI_SwapByte(0x00); // ��ַ��
    SPI_SwapByte(0x00); // ��ַ��
    SPI_SwapByte(0xFF); // Dummy
    //2.��ȡ������ID(Ϊ�˶�ȡ���ݣ���ʲô����Ҫ)
    *ManufactureID = SPI_SwapByte(0xFF);

    *DeviceId |= (SPI_SwapByte(0xFF)<<8);
    *DeviceId |= SPI_SwapByte(0xFF);

    SPI_Stop();
}
//����дʹ��
void NM25Q128_WriteEnbale(void);
//�ر�дʹ��
void NM25Q128_WriteDisable(void);
//�ȴ�״̬��Ϊæ
void NM25Q128_WaitNotBusy(void);
//������(sector)����ַֻ��Ҫ��źͶκ�
void NM25Q128_EraseSector(uint8_t block,uint8_t sector);
//д��(ҳд)
void NM25Q128_PageWrite(uint8_t block,uint8_t sector,uint8_t page,uint8_t* data,uint16_t length);
//��ȡ
void NM25Q128_PageRead(uint8_t block,uint8_t sector,uint8_t page,uint8_t innerAddr,uint8_t* buffer,uint16_t length);
