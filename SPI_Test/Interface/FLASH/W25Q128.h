#ifndef _W25Q128_H
#define _W25Q128_H
#include "SPI.h"

//��ʼ��
void W25Q128_Init(void);

//��ȡID

//����дʹ��
void W25Q128_WriteEnable(void);

//�ر�дʹ��
void W25Q128_WriteDisable(void);

//�ȴ�״̬��Ϊæ(busy)
void W25Q128_WaitForNotBusy(void);

//������
void W25Q128_EraseSector(uint32_t* sector_address);

//д��
void W25Q128_WritePage(uint8_t block,uint8_t sector, uint8_t page,uint8_t* data, uint16_t length);
//��ȡ
/*
    param1
*/
void W25Q128_Read(uint8_t block,uint8_t sector, uint8_t page,uint8_t innerAddr,uint8_t* buffer, uint16_t length);
#endif