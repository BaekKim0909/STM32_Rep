#ifndef _LCD_H
#define _LCD_H
#include "stm32f0xx_hal.h"
#include "spi.h"
#include "main.h"
//LCD参数定义
#define LCD_WIDTH 240
#define LCD_HEIGHT 320
//LCD端口定义
#define LCD_RES_Low() HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_RESET)
#define LCD_RES_High() HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_SET)

#define LCD_BG_Low() HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET)
#define LCD_BG_High() HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET)

#define LCD_DC_Low() HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)
#define LCD_DC_High() HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)





void LCD_Init(void);
void LCD_BGON(void);
void LCD_BGOFF(void);
//写命令(8bit)
void LCD_WR_REG(uint8_t cmd);
//写数据(8bit)
void LCD_WR_DATA(uint8_t data);
//写一个像素
void LCD_WriteRam(uint16_t color);
//设置区域范围
void LCD_SetArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
//初始化LCD寄存器
void LCD_RegConfig(void);
//清屏
void LCD_Clear(uint16_t color);
#endif
