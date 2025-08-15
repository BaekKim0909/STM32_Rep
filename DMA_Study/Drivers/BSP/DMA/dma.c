#include "dma.h"
//��ʼ��
void DMA1_Init(void){
    //1.����ʱ��
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.1 ���� ����MEM2MEM ģʽ
    DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM;

    //2.2 ���ô洢�����ݿ�Ⱥ��������ݿ��Ϊ8bit
    DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE;

    DMA1_Channel1->CCR |= DMA_CCR_MINC;
    DMA1_Channel1->CCR |= DMA_CCR_PINC;

}

//���ݴ���
void DMA1_Transmit(uint32_t srcAddr,uint32_t destAddr,uint16_t dataLen);
