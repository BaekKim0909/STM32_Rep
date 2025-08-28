#ifndef _TOUCH_H
#define _TOUCH_H
#include "stm32f0xx_hal.h"
#include "main.h"
#include "lcd.h"
#include "delay.h"
#include <stdlib.h>
//Touch 接口定义
//片选
#define TP_CS_Low()     HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,GPIO_PIN_RESET)
#define TP_CS_High()    HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,GPIO_PIN_SET)

#define TP_MOSI_Low()   HAL_GPIO_WritePin(TP_MOSI_GPIO_Port,TP_MOSI_Pin,GPIO_PIN_RESET)
#define TP_MOSI_High()  HAL_GPIO_WritePin(TP_MOSI_GPIO_Port,TP_MOSI_Pin,GPIO_PIN_SET)
//时钟
#define TP_SCK_Low()    HAL_GPIO_WritePin(TP_SCK_GPIO_Port,TP_SCK_Pin,GPIO_PIN_RESET)
#define TP_SCK_High()   HAL_GPIO_WritePin(TP_SCK_GPIO_Port,TP_SCK_Pin,GPIO_PIN_SET)

#define TP_MISO_State   HAL_GPIO_ReadPin(TP_MISO_GPIO_Port,TP_MISO_Pin)
#define TP_IRQ_State   HAL_GPIO_ReadPin(TP_IRQ_GPIO_Port,TP_IRQ_Pin)


#define TP_PRES_DOWN    0x8000      /* 触屏被按下 */
#define TP_CATH_PRES    0x4000      /* 有按键按下了 */
#define CT_MAX_TOUCH    10          /* 电容屏支持的点数,固定为5点 */
/* 触摸屏控制器 */
typedef struct
{
    uint8_t (*init)(void);      /* 初始化触摸屏控制器 */
    uint8_t (*scan)(uint8_t);   /* 扫描触摸屏.0,屏幕扫描;1,物理坐标; */
    void (*adjust)(void);       /* 触摸屏校准 */
    uint16_t x[CT_MAX_TOUCH];   /* 当前坐标 */
    uint16_t y[CT_MAX_TOUCH];   /* 电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
                                 * x[9],y[9]存储第一次按下时的坐标.
                                 */

    uint16_t sta;               /* 笔的状态
                                 * b15:按下1/松开0;
                                 * b14:0,没有按键按下;1,有按键按下.
                                 * b13~b10:保留
                                 * b9~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
                                 */

    /* 5点校准触摸屏校准参数(电容屏不需要校准) */
    float xfac;                 /* 5点校准法x方向比例因子 */
    float yfac;                 /* 5点校准法y方向比例因子 */
    short xc;                   /* 中心X坐标物理值(AD值) */
    short yc;                   /* 中心Y坐标物理值(AD值) */

    /* 新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
     * b0:0, 竖屏(适合左右为X坐标,上下为Y坐标的TP)
     *    1, 横屏(适合左右为Y坐标,上下为X坐标的TP)
     * b1~6: 保留.
     * b7:0, 电阻屏
     *    1, 电容屏
     */
    uint8_t touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev;        /* 触屏控制器在touch.c里面定义 */




//触摸屏初始化
uint8_t Touch_Init(void);
//触摸屏校准
void Touch_Adjust(void);
//触摸按键扫描
uint8_t Touch_Sacn(uint8_t mode);
//MCU向触摸屏IC写1Byte数据
void TP_Write_Byte(uint8_t data);
//MCU向XTP2046发送命令，XTP2046返回数据
uint16_t TP_Read_AD(uint8_t cmd);
//读取一个坐标值(x或者y)
uint16_t TP_Read_XoY(uint8_t cmd);
//读取x, y坐标
void TP_Read_XY(uint16_t *x, uint16_t *y);
//连续读取2次触摸IC数据, 并滤波
uint8_t TP_Read_XY2(uint16_t *x, uint16_t *y);
// 画一个校准用的触摸点(十字架)
void TP_Draw_Touch_Point(uint16_t x, uint16_t y, uint16_t color);
//画一个大点(2*2的点)
void TP_Draw_Big_Point(uint16_t x, uint16_t y, uint16_t color);
//提示校准结果(各个参数)
void TP_Adjust_Info_Show(uint16_t xy[5][2], double px, double py);

#endif


