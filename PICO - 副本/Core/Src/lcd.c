#include "lcd.h"
void LCD_Init()
{
    LCD_RES_High();
    HAL_Delay(1);
    LCD_RES_Low();
    HAL_Delay(10);
    LCD_RES_High();
    HAL_Delay(120);
    LCD_RegConfig();
    LCD_BGON();
}
void LCD_BGON(void)
{
    LCD_BG_High();
}
void LCD_BGOFF(void)
{
    LCD_BG_Low();
}
// 写命令(8bit)
void LCD_WR_REG(uint8_t cmd)
{
    SPI2_Start(); // CS=0
    LCD_DC_Low(); // DC=0  表示写命令
    HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);
    SPI2_Stop(); // CS=1
}
// 写数据(8bit)
void LCD_WR_DATA(uint8_t data)
{
    SPI2_Start();
    LCD_DC_High(); // DC=1 表示写数据
    HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);
    SPI2_Stop();
}
//写一个像素
void LCD_WriteRam(uint16_t color){
    uint8_t buf[2];
    buf[0] = (color >> 8) & 0xFF;//高字节
    buf[1] = color & 0xFF;//低字节
    SPI2_Start();
    LCD_DC_High(); // DC=1 表示写数据
    HAL_SPI_Transmit(&hspi2, buf, 2, HAL_MAX_DELAY);
    SPI2_Stop();
}
//设置区域范围
void LCD_SetArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
    //1. 设置列范围
    LCD_WR_REG(0x2A);
    //1.1 起始列
    LCD_WR_DATA((x >> 8) & 0xFF);
    LCD_WR_DATA(x & 0xFF);
    //1.2 结束列
    LCD_WR_DATA(((x + width - 1) >> 8) & 0xFF);
    LCD_WR_DATA((x + width - 1) & 0xFF);

    //2. 设置行范围
    LCD_WR_REG(0x2B);
    //2.1 起始行
    LCD_WR_DATA((y >> 8) & 0xFF);
    LCD_WR_DATA(y & 0xFF);
    //2.2结束行
    LCD_WR_DATA(((y + height - 1) >> 8) & 0xFF);
    LCD_WR_DATA((y + height - 1) & 0xFF);
}
//清屏
void LCD_Clear(uint16_t color){
    LCD_SetArea(0,0,LCD_WIDTH,LCD_HEIGHT);
    LCD_WR_REG(0x2C);
    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    {
        /* code */
        LCD_WriteRam(color);
    }
    
}
// 9341
void LCD_RegConfig(void)
{
    //************* Start Initial Sequence **********//
    LCD_WR_REG(0xCF);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xC1);
    LCD_WR_DATA(0x30);

    LCD_WR_REG(0xED);
    LCD_WR_DATA(0x64);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x81);

    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x85);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x7A);

    LCD_WR_REG(0xCB);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x34);
    LCD_WR_DATA(0x02);

    LCD_WR_REG(0xF7);
    LCD_WR_DATA(0x20);

    LCD_WR_REG(0xEA);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xC0);  // Power control
    LCD_WR_DATA(0x21); // VRH[5:0]

    LCD_WR_REG(0xC1);  // Power control
    LCD_WR_DATA(0x11); // SAP[2:0];BT[3:0]

    LCD_WR_REG(0xC5); // VCM control
    LCD_WR_DATA(0x31);
    LCD_WR_DATA(0x3C);

    LCD_WR_REG(0xC7); // VCM control2
    LCD_WR_DATA(0x9f);

    LCD_WR_REG(0x36); // Memory Access Control
    LCD_WR_DATA(0x08);

    LCD_WR_REG(0x3A); // Memory Access Control
    LCD_WR_DATA(0x55);

    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x1B);

    LCD_WR_REG(0xB6); // Display Function Control
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0xA2);

    LCD_WR_REG(0xF2); // 3Gamma Function Disable
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0x26); // Gamma curve selected
    LCD_WR_DATA(0x01);

    LCD_WR_REG(0xE0); // Set Gamma
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x20);
    LCD_WR_DATA(0x1d);
    LCD_WR_DATA(0x0b);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x0a);
    LCD_WR_DATA(0x49);
    LCD_WR_DATA(0xa9);
    LCD_WR_DATA(0x3b);
    LCD_WR_DATA(0x0a);
    LCD_WR_DATA(0x15);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x0c);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0XE1); // Set Gamma
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x1f);
    LCD_WR_DATA(0x22);
    LCD_WR_DATA(0x04);
    LCD_WR_DATA(0x0f);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x36);
    LCD_WR_DATA(0x46);
    LCD_WR_DATA(0x46);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x0b);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x33);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x0F);

    LCD_WR_REG(0x11); // Sleep out
    HAL_Delay(120);
    LCD_WR_REG(0x29); // Display on
}
