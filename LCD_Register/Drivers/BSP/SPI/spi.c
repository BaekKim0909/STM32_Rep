#include "spi.h"
//��ʼ��
void SPI_Init(void){
    //1.����ʱ��
    //����GPIOB��ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    //����SPI2��ʱ��
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

    //2.GPIO����ģʽ
    //25Q128��CS:PB12 ͨ��������� MODE:11 CNF:00
    GPIOB->CRH |= GPIO_CRH_MODE12;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;

    // CLK:PB13  MOSI:PB15 �����������  MODE:11 CNF:10
    GPIOB->CRH |= GPIO_CRH_MODE13;
    GPIOB->CRH &= ~GPIO_CRH_CNF13;
    GPIOB->CRH |= GPIO_CRH_CNF13_1;

    GPIOB->CRH |= GPIO_CRH_MODE15;
    GPIOB->CRH &= ~GPIO_CRH_CNF15;
    GPIOB->CRH |= GPIO_CRH_CNF15_1;

    //MISO:PB14 �������� MODE:00  CNF:01
    GPIOB->CRH &= ~GPIO_CRH_MODE14;
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_1;

    //3.SPI�������
    //3.1 ����STM32Ϊ���豸
    SPI2->CR1 |= SPI_CR1_MSTR;

    //3.2 ʹ�����Ƭѡ�ź�
    SPI2->CR1 |= SPI_CR1_SSM;
    SPI2->CR1 |= SPI_CR1_SSI;

    //3.3 ���ù���ģʽ
    SPI2->CR1 &= ~SPI_CR1_CPOL;//ʱ�Ӽ��� Ϊ0
    SPI2->CR1 &= ~SPI_CR1_CPHA;//ʱ����λ Ϊ0

    //3.4 ����ʱ�ӷ�Ƶϵ��
    SPI2->CR1 &= ~SPI_CR1_BR;

    //3.5 ��������֡��ʽ
    SPI2->CR1 &= ~SPI_CR1_DFF;

    //3.6 ���ø�λ����
    SPI2->CR1 &= ~SPI_CR1_LSBFIRST;

    //3.7 SPIģ��ʹ��
    SPI2->CR1 |= SPI_CR1_SPE;


}

//���ݴ���Ŀ�ʼ�ͽ���
void SPI_Start(void){
    CS_LOW;
}
void SPI_Stop(void){
    CS_HIGH;
}
//4.�����豸����һ���ֽڵ�����
uint8_t SPI_SwapByte(uint8_t TransmitByte){
    //4.1 ��Ҫ���͵�����byte д�뷢�ͻ�����
    //4.1.1 �ȴ����ͻ�����Ϊ��
    while ( (SPI2->SR & SPI_SR_TXE) == 0)
    {
        /* code */
    }
    //4.1.2 �����͵��ֽ�д��DR�Ĵ���
    SPI2->DR = TransmitByte;

    //4.2 ��ȡMISO����������
    //4.2.1 �ȴ����ջ�����Ϊ�ǿ�
    while ((SPI2->SR & SPI_SR_RXNE) == 0)
    {
        /* code */
    }
    //4.2.2 �ӽ��ջ�������ȡ���ݣ�����
    return (uint8_t)(SPI2->DR & 0xFF); 
}
