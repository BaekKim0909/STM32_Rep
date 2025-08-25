#include "dma.h"
//��ʼ��
void DMA1_Init(void){
    //1.����ʱ��
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.1 ���� ����MEM2MEM ģʽ
    DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM;
    //�������ݴ��ͷ���
    DMA1_Channel1->CCR &= ~DMA_CCR_DIR;
    //2.2 ���ô洢�����ݿ�Ⱥ��������ݿ��Ϊ8bit
    DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE;
    //2.3 ���ô洢�������� ��ַ����ģʽλ����
    DMA1_Channel1->CCR |= DMA_CCR_MINC;
    DMA1_Channel1->CCR |= DMA_CCR_PINC;

    //2.4�������ݴ�������ж�
    DMA1_Channel1->CCR |= DMA_CCR_TCIE;
    
    //3.����NVIC�ж�
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn,2);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

//���ݴ���
void DMA1_Transmit(uint32_t srcAddr,uint32_t destAddr,uint16_t dataLen){
    //1.���������ַ
    DMA1_Channel1->CPAR = srcAddr;
    
    //2.���ô洢����ַ
    DMA1_Channel1->CMAR = destAddr;

    //3.���ô����������(���ݳ���)
    DMA1_Channel1->CNDTR = dataLen;

    //4.����ͨ��,��ʼ��������
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}

//�жϷ������
void DMA1_Channel1_IRQHandler(){
    //�ж��жϱ�־λ
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        //����жϱ�־λ
        DMA1->IFCR |= DMA_IFCR_CTCIF1;
        //�ر�DMAͨ��
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;
        
        //��־λ��1
        IsFinsihed = 1;
    }
    
}
