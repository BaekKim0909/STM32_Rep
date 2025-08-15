/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       ����ͨ�� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./stm32f1xx_it.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "dma.h"


//����ȫ�ֱ�������ʾ���ݴ������
uint8_t IsFinsihed = 0;


//����ȫ�ֳ������ݣ���������FLASH��
const uint8_t source[] = {10,20,30,40};
//�����������������RAM��
uint8_t dest[4] = {0};




int main(void)
{
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��Ϊ72Mhz */
    delay_init(72);                         /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    //��ʼ��DMA1
    DMA1_Init();
    //��������
    DMA1_Transmit((uint32_t)source,(uint32_t)dest,sizeof(source)/sizeof(source[0]));
    while (1)
    {
        
        if (IsFinsihed)
        {
            /* code */
            //��ӡ�����֤
            printf("source's Address:%p,dest's Address:%p \n",source,dest);
            for (uint8_t i = 0; i < sizeof(dest)/sizeof(dest[0]); i++)
            {
                printf("%d\t",dest[i]);
            }
            
            delay_ms(1000);
        }
        
    }
}



