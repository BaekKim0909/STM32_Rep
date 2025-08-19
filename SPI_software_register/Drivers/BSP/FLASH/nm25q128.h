#ifndef _NM25Q128_H
#define _NM25Q128_H
#include "spi.h"

//��ʼ��
void NM25Q128_Init(void);

//��ȡID
void NM25Q128_ReadID(uint8_t* ManufactureID,uint16_t* DeviceId);
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
#endif
