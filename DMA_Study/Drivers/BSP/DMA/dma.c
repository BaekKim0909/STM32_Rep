#include "dma.h"
//初始化
void DMA1_Init(void){
    //1.开启时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.1 设置 启动MEM2MEM 模式
    DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM;

    //2.2 设置存储器数据宽度和外设数据宽度为8bit
    DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE;

    DMA1_Channel1->CCR |= DMA_CCR_MINC;
    DMA1_Channel1->CCR |= DMA_CCR_PINC;

}

//数据传输
void DMA1_Transmit(uint32_t srcAddr,uint32_t destAddr,uint16_t dataLen);
