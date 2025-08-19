#include "adc.h"

//��ʼ��
void ADC1_Init(void){
    //1.����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    //2.��Ƶ APB2��Ƶ��72MHZ Ҫ��ADC������ʱ�Ӳ��ó���14MHz ��Ƶ�� 72/6 =12M
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    //2.GPIO����ģʽ PA1ģ������ CNF:00 MODE:00
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    //3.ADC���� ʹ��ADC1ͨ��1
    //3.1 ����ģʽ������ɨ��ģʽ
    ADC1->CR1 &= ~ADC_CR1_SCAN;

    //3.2 ��������ɨ��ģʽ
    ADC1->CR2 |= ADC_CR2_CONT;

    //3.3�����Ҷ���(Ĭ��)
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    //3.4����ͨ��1�Ĳ���ʱ�� 000 ��������:1.5����
    ADC1->SMPR2 &= ~ADC_SMPR2_SMP1;

    //3.5������ͨ����������
    //3.5.1 ������ͨ���е�ͨ������ 1
    ADC1->SQR1 &= ~ADC_SQR1_L;

    //3.5.2 ��ӵ��������еĵ�һλ
    //����0
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    //��ͨ��1���(1)д��SQ1
    ADC1->SQR3 |= 1<<0;

    //3.6ѡ���������ADת��
    //�����ⲿ�¼�����
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
    //����SWSTART�������
    ADC1->CR2 |=ADC_CR2_EXTSEL;
}

//����ת��
void ADC1_StartConvert(void){
    //1.�ϵ绽��
    ADC1->CR2 |= ADC_CR2_ADON;
    //2.ִ��ADУ׼
    ADC1->CR2 |= ADC_CR2_CAL;
    //�ȴ�У׼���
    while ((ADC1->CR2 & ADC_CR2_CAL) == 1)
    {
    }

    //3.����ת��
    ADC1->CR2 |= ADC_CR2_SWSTART;
    //�ȴ�ת�����
    while ((ADC1->SR & ADC_SR_EOC) == 0)
    {
        /* code */
    }
    
    
}

//����ת�����ģ���ѹ
double ADC1_ReadV(void){
    return ADC1->DR*3.3 /4095;
}
