#include "adc.h"

//初始化
void ADC1_Init(void){
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    //2.分频 APB2上频率72MHZ 要求ADC的输入时钟不得超过14MHz 分频后 72/6 =12M
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    //2.GPIO工作模式 PA1模拟输入 CNF:00 MODE:00
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    //3.ADC配置 使用ADC1通道1
    //3.1 工作模式：禁用扫描模式
    ADC1->CR1 &= ~ADC_CR1_SCAN;

    //3.2 启用连续扫描模式
    ADC1->CR2 |= ADC_CR2_CONT;

    //3.3数据右对齐(默认)
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    //3.4设置通道1的采样时间 000 采样周期:1.5周期
    ADC1->SMPR2 &= ~ADC_SMPR2_SMP1;

    //3.5规则组通道序列配置
    //3.5.1 规则组通道中的通道个数 1
    ADC1->SQR1 &= ~ADC_SQR1_L;

    //3.5.2 添加到规则序列的第一位
    //先清0
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    //将通道1编号(1)写入SQ1
    ADC1->SQR3 |= 1<<0;

    //3.6选择软件触发AD转换
    //启用外部事件启动
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
    //设置SWSTART软件触发
    ADC1->CR2 |=ADC_CR2_EXTSEL;
}

//开启转换
void ADC1_StartConvert(void){
    //1.上电唤醒
    ADC1->CR2 |= ADC_CR2_ADON;
    //2.执行AD校准
    ADC1->CR2 |= ADC_CR2_CAL;
    //等待校准完成
    while ((ADC1->CR2 & ADC_CR2_CAL) == 1)
    {
    }

    //3.启动转换
    ADC1->CR2 |= ADC_CR2_SWSTART;
    //等待转换完成
    while ((ADC1->SR & ADC_SR_EOC) == 0)
    {
        /* code */
    }
    
    
}

//返回转换后的模拟电压
double ADC1_ReadV(void){
    return ADC1->DR*3.3 /4095;
}
