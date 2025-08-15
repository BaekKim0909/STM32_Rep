#include "dma.h"
//初始化
void DMA1_Init(void){
    //1.开启时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.1 设置 启动MEM2MEM 模式
    DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM;
    //设置数据传送方向
    DMA1_Channel1->CCR &= ~DMA_CCR_DIR;
    //2.2 设置存储器数据宽度和外设数据宽度为8bit
    DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE;
    //2.3 设置存储器和外设 地址增量模式位自增
    DMA1_Channel1->CCR |= DMA_CCR_MINC;
    DMA1_Channel1->CCR |= DMA_CCR_PINC;

    //2.4开启数据传输完成中断
    DMA1_Channel1->CCR |= DMA_CCR_TCIE;
    
    //3.配置NVIC中断
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn,2);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

//数据传输
void DMA1_Transmit(uint32_t srcAddr,uint32_t destAddr,uint16_t dataLen){
    //1.设置外设地址
    DMA1_Channel1->CPAR = srcAddr;
    
    //2.设置存储器地址
    DMA1_Channel1->CMAR = destAddr;

    //3.设置传输的数据量(数据长度)
    DMA1_Channel1->CNDTR = dataLen;

    //4.开启通道,开始传输数据
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}

//中断服务程序
void DMA1_Channel1_IRQHandler(){
    //判断中断标志位
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        //清除中断标志位
        DMA1->IFCR |= DMA_IFCR_CTCIF1;
        //关闭DMA通道
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;
        
        //标志位置1
        IsFinsihed = 1;
    }
    
}
