#include "lcd.h"
//初始化LCD
void LCD_Init(void){
    FSMC_Init();
    LCD_RegConfig();
    LCD_BGON();

}

//开启背光
void LCD_BGON(void){
    //PB0 输出高电平，点亮背光LED
    GPIOB->ODR |= GPIO_PIN_0;
}
void LCD_BGOFF(void){
    //PB0 输出低电平，关闭背光LED
    GPIOB->ODR &= ~GPIO_PIN_0;
}

//初始化LCD寄存器
void LCD_RegConfig(void){
    lcd_ex_st7789_reginit();
    //lcd_ex_ili9341_reginit();
}

//写命令
void LCD_WriteCmd(uint16_t cmd){
    *LCD_ADDR_CMD =cmd;

}
//写数据
void LCD_WriteData(uint16_t data){
    *LCD_ADDR_DATA = data;
}
//读数据
uint16_t LCD_ReadData(void){
    return *LCD_ADDR_DATA;
}

//2. 具体的命令操作
uint32_t LCD_ReadId(void){

    uint32_t lcd_id = 0;
    LCD_WriteCmd(0x04);

    LCD_ReadData();
    lcd_id |= ((LCD_ReadData() & 0xff) << 16);
    lcd_id |= ((LCD_ReadData() & 0xff) << 8);
    lcd_id |= ((LCD_ReadData() & 0xff) << 0);
    return lcd_id;
}
//设置区域范围，给定起始点的坐标(行列号),以及区域的宽高
void LCD_SetArea(uint16_t x,uint16_t y,uint16_t w,uint16_t h){
    //1. 设置列范围
    LCD_WriteCmd(0x2A);
    //1.1 设置开始列
    //先给高八位
    LCD_WriteData((x >> 8) & 0xFF);
    //再给低八位
    LCD_WriteData(x & 0xFF);
    //1.2 设置结束列
    //先给高八位
    LCD_WriteData(((x + w - 1) >> 8) & 0xFF);
    //再给低八位
    LCD_WriteData((x + w - 1) & 0xFF);

    //2.设置行范围
    LCD_WriteCmd(0x2B);
    //1.1 设置开始行
    //先给高八位
    LCD_WriteData((y >> 8) & 0xFF);
    //再给低八位
    LCD_WriteData(y & 0xFF);
    //1.2 设置结束行
    //先给高八位
    LCD_WriteData(((y + h - 1) >> 8) & 0xFF);
    //再给低八位
    LCD_WriteData((y + h - 1) & 0xFF);

    //
}

void LCD_ClrarAll(uint16_t color){
    //1. 设置区域范围为全屏
    LCD_SetArea(0,0,LCD_WIDTH,LCD_HEIGHT);

    //2. 向对应区域范围发送数据
    LCD_WriteCmd(0x2C);

    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    {
        LCD_WriteData(color);
    }
    
}

















void lcd_ex_st7789_reginit(void)
{
    LCD_WriteCmd(0x11);

    delay_ms(120); 

    LCD_WriteCmd(0x36);
    LCD_WriteData(0x00);


    LCD_WriteCmd(0x3A);
    LCD_WriteData(0X05);

    LCD_WriteCmd(0xB2);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x33);
    LCD_WriteData(0x33);

    LCD_WriteCmd(0xB7);
    LCD_WriteData(0x35);

    LCD_WriteCmd(0xBB); /* vcom */
    LCD_WriteData(0x32);  /* 30 */

    LCD_WriteCmd(0xC0);
    LCD_WriteData(0x0C);

    LCD_WriteCmd(0xC2);
    LCD_WriteData(0x01);

    LCD_WriteCmd(0xC3); /* vrh */
    LCD_WriteData(0x10);  /* 17 0D */

    LCD_WriteCmd(0xC4); /* vdv */
    LCD_WriteData(0x20);  /* 20 */

    LCD_WriteCmd(0xC6);
    LCD_WriteData(0x0f);

    LCD_WriteCmd(0xD0);
    LCD_WriteData(0xA4); 
    LCD_WriteData(0xA1); 

    LCD_WriteCmd(0xE0); /* Set Gamma  */
    LCD_WriteData(0xd0);
    LCD_WriteData(0x00);
    LCD_WriteData(0x02);
    LCD_WriteData(0x07);
    LCD_WriteData(0x0a);
    LCD_WriteData(0x28);
    LCD_WriteData(0x32);
    LCD_WriteData(0X44);
    LCD_WriteData(0x42);
    LCD_WriteData(0x06);
    LCD_WriteData(0x0e);
    LCD_WriteData(0x12);
    LCD_WriteData(0x14);
    LCD_WriteData(0x17);


    LCD_WriteCmd(0XE1);  /* Set Gamma */
    LCD_WriteData(0xd0);
    LCD_WriteData(0x00);
    LCD_WriteData(0x02);
    LCD_WriteData(0x07);
    LCD_WriteData(0x0a);
    LCD_WriteData(0x28);
    LCD_WriteData(0x31);
    LCD_WriteData(0x54);
    LCD_WriteData(0x47);
    LCD_WriteData(0x0e);
    LCD_WriteData(0x1c);
    LCD_WriteData(0x17);
    LCD_WriteData(0x1b); 
    LCD_WriteData(0x1e);


    LCD_WriteCmd(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0xef);

    LCD_WriteCmd(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x3f);

    LCD_WriteCmd(0x29); /* display on */
}

void lcd_ex_ili9341_reginit(void)
{
    LCD_WriteCmd(0xCF);
    LCD_WriteData(0x00);
    LCD_WriteData(0xC1);
    LCD_WriteData(0X30);
    LCD_WriteCmd(0xED);
    LCD_WriteData(0x64);
    LCD_WriteData(0x03);
    LCD_WriteData(0X12);
    LCD_WriteData(0X81);
    LCD_WriteCmd(0xE8);
    LCD_WriteData(0x85);
    LCD_WriteData(0x10);
    LCD_WriteData(0x7A);
    LCD_WriteCmd(0xCB);
    LCD_WriteData(0x39);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x34);
    LCD_WriteData(0x02);
    LCD_WriteCmd(0xF7);
    LCD_WriteData(0x20);
    LCD_WriteCmd(0xEA);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteCmd(0xC0); /* Power control */
    LCD_WriteData(0x1B);  /* VRH[5:0] */
    LCD_WriteCmd(0xC1); /* Power control */
    LCD_WriteData(0x01);  /* SAP[2:0];BT[3:0] */
    LCD_WriteCmd(0xC5); /* VCM control */
    LCD_WriteData(0x30);  /* 3F */
    LCD_WriteData(0x30);  /* 3C */
    LCD_WriteCmd(0xC7); /* VCM control2 */
    LCD_WriteData(0XB7);
    LCD_WriteCmd(0x36); /*  Memory Access Control */
    LCD_WriteData(0x48);
    LCD_WriteCmd(0x3A);
    LCD_WriteData(0x55);
    LCD_WriteCmd(0xB1);
    LCD_WriteData(0x00);
    LCD_WriteData(0x1A);
    LCD_WriteCmd(0xB6); /*  Display Function Control */
    LCD_WriteData(0x0A);
    LCD_WriteData(0xA2);
    LCD_WriteCmd(0xF2); /*  3Gamma Function Disable */
    LCD_WriteData(0x00);
    LCD_WriteCmd(0x26); /* Gamma curve selected */
    LCD_WriteData(0x01);
    LCD_WriteCmd(0xE0); /* Set Gamma */
    LCD_WriteData(0x0F);
    LCD_WriteData(0x2A);
    LCD_WriteData(0x28);
    LCD_WriteData(0x08);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x08);
    LCD_WriteData(0x54);
    LCD_WriteData(0XA9);
    LCD_WriteData(0x43);
    LCD_WriteData(0x0A);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteCmd(0XE1);    /* Set Gamma */
    LCD_WriteData(0x00);
    LCD_WriteData(0x15);
    LCD_WriteData(0x17);
    LCD_WriteData(0x07);
    LCD_WriteData(0x11);
    LCD_WriteData(0x06);
    LCD_WriteData(0x2B);
    LCD_WriteData(0x56);
    LCD_WriteData(0x3C);
    LCD_WriteData(0x05);
    LCD_WriteData(0x10);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x3F);
    LCD_WriteData(0x3F);
    LCD_WriteData(0x0F);
    LCD_WriteCmd(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x3f);
    LCD_WriteCmd(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0xef);
    LCD_WriteCmd(0x11); /* Exit Sleep */
    delay_ms(120);
    LCD_WriteCmd(0x29); /* display on */
 }
