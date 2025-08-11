#include "SPI.h"
 //SPI��ʼ������
void SPI_Init(void){
    //1.����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //ʹ��GPIOBʱ��

    //2.GPIO����ģʽ
    //CS:PB12 SCK:PB13 MOSI:PB15 ͨ���������  CNF=00 MODE=11
    GPIOB->CRH &= ~GPIO_CRH_CNF12;
    GPIOB->CRH |= GPIO_CRH_MODE12;

    GPIOB->CRH &= ~GPIO_CRH_CNF13;
    GPIOB->CRH |= GPIO_CRH_MODE13;

    GPIOB->CRH &= ~GPIO_CRH_CNF15;
    GPIOB->CRH |= GPIO_CRH_MODE15;

    //MISO PB14 �������� CNF=01 MODE=00
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_0;
    GPIOB->CRH &= ~GPIO_CRH_MODE14;

    //3.ѡ��SPI�Ĺ���ģʽ0 ��SCK����0
    SCK_LOW;  //SCK�͵�ƽ����

    //4.Ƭѡ��ʹ��
    CS_HIGH;

    //5.��ʱ�ȴ�
    SPI_DELAY; //��ʱ5us
}

//���ݴ���Ŀ�ʼ�ͽ���
void SPI_Start(void){
    CS_LOW;  //Ƭѡʹ��
}
void SPI_Stop(void){
    CS_HIGH; //Ƭѡ��ʹ��
}

//�����豸����һ���ֽڵ�����
uint8_t SPI_SwapByte(uint8_t translate_byte){
    //������� ������յ����ֽ�
    uint8_t receive_byte = 0x00;

    //һ�ν���8λ����
    for(uint8_t i = 0; i<8; i++){
        //1.��׼��Ҫ���͵�����(���λ)���͵�MOSI��
        if(translate_byte & 0x80){
            MOSI_HIGH; //����1
        }else{
            MOSI_LOW;  //����0
        }
        //��������һλ
        translate_byte <<= 1; 

        //2.����SCK���γ�һ��������
        SCK_HIGH;
        SPI_DELAY;

        //3. ��MISO�ϲ��� FLASH����������
        receive_byte <<= 1; //������������һλ
        if (MISO_READ)
        {
            receive_byte |= 0x01;
        }
        
        //4. ����ʱ��
        SCK_LOW;
        SPI_DELAY; 
    }

    return receive_byte;
}