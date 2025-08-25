#ifndef _LCD_H
#define _LCD_H
#include "stm32f1xx.h"
#include "fsmc.h"
#include "delay.h"
//宏定义
#define SRAM_BANK1_4 0x6c000000
//只通过FSMC_A10 地址线控制命令 当A10=0时，表示写命令，所以地址是：0x6C00 0000。
#define LCD_ADDR_CMD (uint16_t*)SRAM_BANK1_4
//当A10=1时，表示写数据
#define LCD_ADDR_DATA (uint16_t*)(SRAM_BANK1_4 + (1<<11))

//定义LCD的宽高
#define LCD_WIDTH 240
#define LCD_HEIGHT 320

//基本控制操作

//初始化LCD
void LCD_Init(void);

//开启背光
void LCD_BGON(void);
//关闭背光
void LCD_BGOFF(void);

//初始化LCD寄存器 ILI9341 初始化
void LCD_RegConfig(void);
void lcd_ex_st7789_reginit(void);
//写命令
void LCD_WriteCmd(uint16_t cmd);
//写数据
void LCD_WriteData(uint16_t cmd);
//读数据
uint16_t LCD_ReadData(void);

uint32_t LCD_ReadId(void);

void LCD_ClrarAll(uint16_t color);
//
void lcd_ex_ili9341_reginit(void);
#endif
