#include "spi.h"
//��ʼ��
void SPI_Init(void){
    //1.����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    //2.GPIO����ģʽ
    //CS:PB12 CLK:PB13  MOSI:PB15 ͨ��������� MODE:11 CNF:00
    GPIOB->CRH |= GPIO_CRH_MODE12;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;

    GPIOB->CRH |= GPIO_CRH_MODE13;
    GPIOB->CRH &= ~GPIO_CRH_CNF13;

    GPIOB->CRH |= GPIO_CRH_MODE15;
    GPIOB->CRH &= ~GPIO_CRH_CNF15;

    //MISO:PB14 �������� MODE:00  CNF:01
    GPIOB->CRH &= ~GPIO_CRH_MODE14;
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_1;

    //3.ѡ��SPI�Ĺ���ģʽ0�� SCK����0  Ƭѡ�ź�Ĭ�ϲ�����
    CLK_LOW;
    CS_HIGH;
    //4.��ʱ
    SPI_DELAY;
}

//���ݴ���Ŀ�ʼ�ͽ���
void SPI_Start(void){
    CS_LOW;
}
void SPI_Stop(void){
    CS_HIGH;
}
//�����豸����һ���ֽڵ�����
uint8_t SPI_SwapByte(uint8_t byte){
    //�������������յ����ֽ�
    uint8_t receive_byte =0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        //1.��׼��Ҫ���͵����ݣ��͵�MOSI��
        if (byte & 0x80)
        {
            /* code */
            MOSI_HIGH;
        }else{
            MOSI_LOW;
        }
        //����һλ
        byte <<= 1;

        //2.����ʱ���źţ��γɵ�һ��������
        CLK_HIGH;
        SPI_DELAY;

        //3.��MISO�ϲ���FLASH����������
        //������
        receive_byte <<= 1;
        if (MISO_READ == GPIO_PIN_SET)
        {
            receive_byte |= 0x01;
        }
        //4.����ʱ�ӣ�Ϊ��һ�����ݴ�����׼��
        CLK_LOW;
        SPI_DELAY;
        
    }
    return receive_byte;
}
