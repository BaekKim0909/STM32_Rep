#include "W25Q128.h"

//��ʼ��
void W25Q128_Init(void)
{
    SPI_Init(); 
}

//����дʹ��
void W25Q128_WriteEnable(void){
    SPI_Start();
    SPI_SwapByte(0x06);//����дʹ��ָ��
    SPI_Stop();    
}

//�ر�дʹ��
void W25Q128_WriteDisable(void){
    SPI_Start();
    SPI_SwapByte(0x04); //����д��ָֹ��
    SPI_Stop();
}
//�ȴ�״̬��Ϊæ(busy)
void W25Q128_WaitForNotBusy(void);