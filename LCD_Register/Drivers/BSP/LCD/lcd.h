#ifndef _LCD_H
#define _LCD_H
#include "stm32f1xx.h"
#include "fsmc.h"
#include "delay.h"
//�궨��
#define SRAM_BANK1_4 0x6c000000
//ֻͨ��FSMC_A10 ��ַ�߿������� ��A10=0ʱ����ʾд������Ե�ַ�ǣ�0x6C00 0000��
#define LCD_ADDR_CMD (uint16_t*)SRAM_BANK1_4
//��A10=1ʱ����ʾд����
#define LCD_ADDR_DATA (uint16_t*)(SRAM_BANK1_4 + (1<<11))

//����LCD�Ŀ��
#define LCD_WIDTH 240
#define LCD_HEIGHT 320

//�������Ʋ���

//��ʼ��LCD
void LCD_Init(void);

//��������
void LCD_BGON(void);
//�رձ���
void LCD_BGOFF(void);

//��ʼ��LCD�Ĵ��� ILI9341 ��ʼ��
void LCD_RegConfig(void);
void lcd_ex_st7789_reginit(void);
//д����
void LCD_WriteCmd(uint16_t cmd);
//д����
void LCD_WriteData(uint16_t cmd);
//������
uint16_t LCD_ReadData(void);

uint32_t LCD_ReadId(void);

void LCD_ClrarAll(uint16_t color);
//
void lcd_ex_ili9341_reginit(void);
#endif
