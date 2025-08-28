#ifndef _TOUCH_H
#define _TOUCH_H
#include "stm32f0xx_hal.h"
#include "main.h"
#include "lcd.h"
#include "delay.h"
#include <stdlib.h>
//Touch �ӿڶ���
//Ƭѡ
#define TP_CS_Low()     HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,GPIO_PIN_RESET)
#define TP_CS_High()    HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,GPIO_PIN_SET)

#define TP_MOSI_Low()   HAL_GPIO_WritePin(TP_MOSI_GPIO_Port,TP_MOSI_Pin,GPIO_PIN_RESET)
#define TP_MOSI_High()  HAL_GPIO_WritePin(TP_MOSI_GPIO_Port,TP_MOSI_Pin,GPIO_PIN_SET)
//ʱ��
#define TP_SCK_Low()    HAL_GPIO_WritePin(TP_SCK_GPIO_Port,TP_SCK_Pin,GPIO_PIN_RESET)
#define TP_SCK_High()   HAL_GPIO_WritePin(TP_SCK_GPIO_Port,TP_SCK_Pin,GPIO_PIN_SET)

#define TP_MISO_State   HAL_GPIO_ReadPin(TP_MISO_GPIO_Port,TP_MISO_Pin)
#define TP_IRQ_State   HAL_GPIO_ReadPin(TP_IRQ_GPIO_Port,TP_IRQ_Pin)


#define TP_PRES_DOWN    0x8000      /* ���������� */
#define TP_CATH_PRES    0x4000      /* �а��������� */
#define CT_MAX_TOUCH    10          /* ������֧�ֵĵ���,�̶�Ϊ5�� */
/* ������������ */
typedef struct
{
    uint8_t (*init)(void);      /* ��ʼ�������������� */
    uint8_t (*scan)(uint8_t);   /* ɨ�败����.0,��Ļɨ��;1,��������; */
    void (*adjust)(void);       /* ������У׼ */
    uint16_t x[CT_MAX_TOUCH];   /* ��ǰ���� */
    uint16_t y[CT_MAX_TOUCH];   /* �����������10������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
                                 * x[9],y[9]�洢��һ�ΰ���ʱ������.
                                 */

    uint16_t sta;               /* �ʵ�״̬
                                 * b15:����1/�ɿ�0;
                                 * b14:0,û�а�������;1,�а�������.
                                 * b13~b10:����
                                 * b9~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
                                 */

    /* 5��У׼������У׼����(����������ҪУ׼) */
    float xfac;                 /* 5��У׼��x����������� */
    float yfac;                 /* 5��У׼��y����������� */
    short xc;                   /* ����X��������ֵ(ADֵ) */
    short yc;                   /* ����Y��������ֵ(ADֵ) */

    /* �����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
     * b0:0, ����(�ʺ�����ΪX����,����ΪY�����TP)
     *    1, ����(�ʺ�����ΪY����,����ΪX�����TP)
     * b1~6: ����.
     * b7:0, ������
     *    1, ������
     */
    uint8_t touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev;        /* ������������touch.c���涨�� */




//��������ʼ��
uint8_t Touch_Init(void);
//������У׼
void Touch_Adjust(void);
//��������ɨ��
uint8_t Touch_Sacn(uint8_t mode);
//MCU������ICд1Byte����
void TP_Write_Byte(uint8_t data);
//MCU��XTP2046�������XTP2046��������
uint16_t TP_Read_AD(uint8_t cmd);
//��ȡһ������ֵ(x����y)
uint16_t TP_Read_XoY(uint8_t cmd);
//��ȡx, y����
void TP_Read_XY(uint16_t *x, uint16_t *y);
//������ȡ2�δ���IC����, ���˲�
uint8_t TP_Read_XY2(uint16_t *x, uint16_t *y);
// ��һ��У׼�õĴ�����(ʮ�ּ�)
void TP_Draw_Touch_Point(uint16_t x, uint16_t y, uint16_t color);
//��һ�����(2*2�ĵ�)
void TP_Draw_Big_Point(uint16_t x, uint16_t y, uint16_t color);
//��ʾУ׼���(��������)
void TP_Adjust_Info_Show(uint16_t xy[5][2], double px, double py);

#endif


