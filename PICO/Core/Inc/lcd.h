#ifndef _LCD_H
#define _LCD_H
#include "stm32f0xx_hal.h"
#include "main.h"
// LCD参数定义
#define LCD_WIDTH 240
#define LCD_HEIGHT 320
// LCD端口定义
#define LCD_RES_Low() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET)
#define LCD_RES_High() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)

#define LCD_BG_Low() HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)
#define LCD_BG_High() HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)

#define LCD_DC_Low() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_DC_High() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)

#define LCD_CS_Low() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_High() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

#define LCD_MOSI_Low() HAL_GPIO_WritePin(MOSI_LCD_GPIO_Port, MOSI_LCD_Pin, GPIO_PIN_RESET)
#define LCD_MOSI_High() HAL_GPIO_WritePin(MOSI_LCD_GPIO_Port, MOSI_LCD_Pin, GPIO_PIN_SET)

#define LCD_SCK_Low() HAL_GPIO_WritePin(SCK_LCD_GPIO_Port, SCK_LCD_Pin, GPIO_PIN_RESET)
#define LCD_SCK_High() HAL_GPIO_WritePin(SCK_LCD_GPIO_Port, SCK_LCD_Pin, GPIO_PIN_SET)

#define LCD_BACKGROUNDCOLOR  0xFFFF
void LCD_Init(void);
void LCD_BGON(void);
void LCD_BGOFF(void);
// 软件模拟SPI发送一个字节
void LCD_SPI_WriteByte(uint8_t data);
// 写命令(8bit)
void LCD_WR_REG(uint8_t cmd);
// 写数据(8bit)
void LCD_WR_DATA(uint8_t data);
// 写一个像素
void LCD_WriteRam(uint16_t color);
// 写大量像素的准备
void LCD_WriteRam_Prepare(void);
// 设置区域范围
void LCD_SetArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
// 初始化LCD寄存器
void LCD_RegConfig(void);
//设置光标位置
void LCD_SET_Cursor(uint16_t x, uint16_t y);
// 清屏
void LCD_Clear(uint16_t color);
//在指定区域内填充单个颜色
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
// 在指定区域内填充指定颜色块
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);
//画点
void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t color);
// 展示一个字符
void LCD_Show_Char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
// 展示字符串
void LCD_Show_String(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);

uint32_t LCD_POW(uint8_t m, uint8_t n);
// 显示数字
void LCD_Show_Num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color);
// 画线
void LCD_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
//画圆
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

#endif
