#include "touch.h"

_m_tp_dev tp_dev =
    {
        Touch_Init,
        Touch_Sacn,
        Touch_Adjust,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
};

// MCU向触摸屏IC写1Byte数据
void TP_Write_Byte(uint8_t data)
{
    for (uint8_t count = 0; count < 8; count++)
    {
        if (data & 0x80) /* 发送1 */
        {
            TP_MOSI_High();
        }
        else /* 发送0 */
        {
            TP_MOSI_Low();
        }

        data <<= 1;

        TP_SCK_Low();
        delay_us(1);
        // HAL_Delay(1);
        TP_SCK_High(); /* 上升沿有效 */
    }
}

// 从触摸屏IC读取adc值
uint16_t TP_Read_AD(uint8_t cmd)
{
    uint16_t num = 0;

    TP_SCK_Low();  /* 先拉低时钟 */
    TP_MOSI_Low(); /* 拉低数据线 */
    TP_CS_Low();   /* 选中触摸屏IC */

    TP_Write_Byte(cmd); /* 发送命令字 */
    delay_us(6);       /* ADS7846的转换时间最长为6us */
    //HAL_Delay(1);

    TP_SCK_Low();
    delay_us(1);
    //HAL_Delay(1);

    TP_SCK_High(); /* 给1个时钟，清除BUSY */
    delay_us(1);
    //HAL_Delay(1);

    TP_SCK_Low();

    for (uint8_t count = 0; count < 16; count++) /* 读出16位数据,只有高12位有效 */
    {
        num <<= 1;
        TP_SCK_Low(); /* 下降沿有效 */
        delay_us(1);
        //HAL_Delay(1);

        TP_SCK_High();

        if (TP_MISO_State)
            num++;
    }

    num >>= 4;    /* 只有高12位有效. */
    TP_CS_High(); /* 释放片选 */
    return num;
    /* --------------------------------------------*/
    // uint16_t r_data = 0;
    // // 开始状态
    // TP_SCK_Low();
    // TP_MOSI_Low();
    // TP_CS_Low();

    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     /* code */
    //     TP_SCK_Low();
    //     if (cmd & 0x80)
    //     {
    //         /* code */
    //         TP_MOSI_High();
    //     }
    //     else
    //     {
    //         TP_MOSI_Low();
    //     }
    //     delay_us(1);

    //     TP_SCK_High();
    //     delay_us(1);

    //     cmd <<= 1;
    // }

    // TP_SCK_Low();
    // delay_us(1);
    // TP_SCK_High();
    // delay_us(1);

    // for (uint8_t i = 0; i < 16; i++)
    // {
    //     /* code */
    //     TP_SCK_Low();
    //     delay_us(1);
    //     TP_SCK_High();

    //     r_data <<= 1;
    //     r_data |= TP_MISO_State;
    //     delay_us(1);
    // }

    // TP_SCK_Low();
    // TP_CS_High();

    // return (r_data >>= 4);
    

}
// 初始化
uint8_t Touch_Init(void)
{
    LCD_Clear(0xFFFF); /* 清屏 */
    Touch_Adjust();    /* 屏幕校准 */
    return 1;
}

// 触摸屏校准
void Touch_Adjust(void)
{
    uint16_t pxy[5][2]; /* 物理坐标缓存值 */
    uint8_t cnt = 0;
    short s1, s2, s3, s4; /* 4个点的坐标差值 */
    double px, py;        /* X,Y轴物理坐标比例,用于判定是否校准成功 */
    uint16_t outtime = 0;
    cnt = 0;
    LCD_Clear(0xFFFF);                                                                                                                                                         /* 清屏 */
    LCD_Show_String(40, 40, 160, 100, 16, "Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.", 0xF800); /* 显示提示信息 */
    TP_Draw_Touch_Point(20, 20, 0xF800);                                                                                                                                       /* 画点1 */
    tp_dev.sta = 0;                                                                                                                                                            /* 消除触发信号 */

    while (1) /* 如果连续10秒钟没有按下,则自动退出 */
    {
        tp_dev.scan(1);                            /* 扫描物理坐标 */
        if ((tp_dev.sta & 0xc000) == TP_CATH_PRES) /* 按键按下了一次(此时按键松开了.) */
        {
            outtime = 0;
            tp_dev.sta &= ~TP_CATH_PRES; /* 标记按键已经被处理过了. */

            pxy[cnt][0] = tp_dev.x[0]; /* 保存X物理坐标 */
            pxy[cnt][1] = tp_dev.y[0]; /* 保存Y物理坐标 */
            cnt++;

            switch (cnt)
            {
            case 1:
                TP_Draw_Touch_Point(20, 20, 0xFFFF);             /* 清除点1 */
                TP_Draw_Touch_Point(LCD_WIDTH - 20, 20, 0xF800); /* 画点2 */
                break;

            case 2:
                TP_Draw_Touch_Point(LCD_WIDTH - 20, 20, 0xFFFF);  /* 清除点2 */
                TP_Draw_Touch_Point(20, LCD_HEIGHT - 20, 0xF800); /* 画点3 */
                break;

            case 3:
                TP_Draw_Touch_Point(20, LCD_HEIGHT - 20, 0xFFFF);             /* 清除点3 */
                TP_Draw_Touch_Point(LCD_WIDTH - 20, LCD_HEIGHT - 20, 0xF800); /* 画点4 */
                break;

            case 4:
                LCD_Clear(0xFFFF);                                          /* 画第五个点了, 直接清屏 */
                TP_Draw_Touch_Point(LCD_WIDTH / 2, LCD_HEIGHT / 2, 0xF800); /* 画点5 */
                break;

            case 5:                         /* 全部5个点已经得到 */
                s1 = pxy[1][0] - pxy[0][0]; /* 第2个点和第1个点的X轴物理坐标差值(AD值) */
                s3 = pxy[3][0] - pxy[2][0]; /* 第4个点和第3个点的X轴物理坐标差值(AD值) */
                s2 = pxy[3][1] - pxy[1][1]; /* 第4个点和第2个点的Y轴物理坐标差值(AD值) */
                s4 = pxy[2][1] - pxy[0][1]; /* 第3个点和第1个点的Y轴物理坐标差值(AD值) */

                px = (double)s1 / s3; /* X轴比例因子 */
                py = (double)s2 / s4; /* Y轴比例因子 */

                if (px < 0)
                    px = -px; /* 负数改正数 */
                if (py < 0)
                    py = -py; /* 负数改正数 */

                if (px < 0.95 || px > 1.05 || py < 0.95 || py > 1.05 ||                     /* 比例不合格 */
                    abs(s1) > 4095 || abs(s2) > 4095 || abs(s3) > 4095 || abs(s4) > 4095 || /* 差值不合格, 大于坐标范围 */
                    abs(s1) == 0 || abs(s2) == 0 || abs(s3) == 0 || abs(s4) == 0            /* 差值不合格, 等于0 */
                )
                {
                    cnt = 0;
                    TP_Draw_Touch_Point(LCD_WIDTH / 2, LCD_HEIGHT / 2, 0xFFFF); /* 清除点5 */
                    TP_Draw_Touch_Point(20, 20, 0xF800);                        /* 重新画点1 */
                    TP_Adjust_Info_Show(pxy, px, py);                           /* 显示当前信息,方便找问题 */
                    continue;
                }

                tp_dev.xfac = (float)(s1 + s3) / (2 * (LCD_WIDTH - 40));
                tp_dev.yfac = (float)(s2 + s4) / (2 * (LCD_HEIGHT - 40));

                tp_dev.xc = pxy[4][0]; /* X轴,物理中心坐标 */
                tp_dev.yc = pxy[4][1]; /* Y轴,物理中心坐标 */

                LCD_Clear(0xFFFF);                                                                      /* 清屏 */
                LCD_Show_String(35, 110, LCD_WIDTH, LCD_HEIGHT, 16, "Touch Screen Adjust OK!", 0x001F); /* 校正完成 */
                HAL_Delay(1000);

                LCD_Clear(0xFFFF); /* 清屏 */
                return;            /* 校正完成 */
            }
        }
        HAL_Delay(10);
        outtime++;
    }
}

/* 电阻触摸驱动芯片 数据采集 滤波用参数 */
#define TP_READ_TIMES 5 /* 读取次数 */
#define TP_LOST_VAL 1   /* 丢弃值 */

/**
 * @brief       读取一个坐标值(x或者y)
 * @note        连续读取TP_READ_TIMES次数据,对这些数据升序排列,
 *              然后去掉最低和最高TP_LOST_VAL个数, 取平均值
 *              设置时需满足: TP_READ_TIMES > 2*TP_LOST_VAL 的条件
 * @param       cmd : 指令
 *              0XD0: 读取X轴坐标(@竖屏状态,横屏状态和Y对调.)
 *              0X90: 读取Y轴坐标(@竖屏状态,横屏状态和X对调.)
 * @retval      读取到的数据(滤波后的), ADC值(12bit)
 */

uint16_t TP_Read_XoY(uint8_t cmd)
{
    uint16_t buf[TP_READ_TIMES];
    uint16_t sum = 0;

    for (uint16_t i = 0; i < TP_READ_TIMES; i++) /* 先读取TP_READ_TIMES次数据 */
    {
        buf[i] = TP_Read_AD(cmd);
    }

    /* 升序排序 */
    for (uint16_t i = 0; i < TP_READ_TIMES - 1; i++)
    {
        for (uint16_t j = i + 1; j < TP_READ_TIMES; j++)
        {
            if (buf[i] > buf[j])
            {
                uint16_t temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    /* 去掉两端的丢弃值 */
    for (uint16_t i = TP_LOST_VAL; i < TP_READ_TIMES - TP_LOST_VAL; i++)
    {
        sum += buf[i];
    }

    return sum / (TP_READ_TIMES - 2 * TP_LOST_VAL); /* 取平均值 */
}

/**
 * @brief       读取x, y坐标
 * @param       x,y: 读取到的坐标值
 * @retval      无
 */
void TP_Read_XY(uint16_t *x, uint16_t *y)
{
    uint16_t xval, yval;

    /* X,Y方向与屏幕相同 */

    xval = TP_Read_XoY(0XD0); /* 读取X轴坐标AD值 */
    yval = TP_Read_XoY(0X90); /* 读取Y轴坐标AD值 */

    *x = xval;
    *y = yval;
}

/* 连续两次读取X,Y坐标的数据误差最大允许值 */
#define TP_ERR_RANGE 50 /* 误差范围 */
/**
 * @brief       连续读取2次触摸IC数据, 并滤波
 * @note        连续2次读取触摸屏IC,且这两次的偏差不能超过ERR_RANGE,满足
 *              条件,则认为读数正确,否则读数错误.该函数能大大提高准确度.
 * @param       x,y: 读取到的坐标值
 * @retval      0, 失败; 1, 成功;
 */
uint8_t TP_Read_XY2(uint16_t *x, uint16_t *y)
{
    uint16_t x1, y1;
    uint16_t x2, y2;

    TP_Read_XY(&x1, &y1); /* 读取第一次数据 */
    TP_Read_XY(&x2, &y2); /* 读取第二次数据 */

    /* 前后两次采样在+-TP_ERR_RANGE内 */
    if (((x2 <= x1 && x1 < x2 + TP_ERR_RANGE) || (x1 <= x2 && x2 < x1 + TP_ERR_RANGE)) &&
        ((y2 <= y1 && y1 < y2 + TP_ERR_RANGE) || (y1 <= y2 && y2 < y1 + TP_ERR_RANGE)))
    {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    }

    return 0;
}

// 画一个校准用的触摸点(十字架)
void TP_Draw_Touch_Point(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Draw_Line(x - 12, y, x + 13, y, color); /* 横线 */
    LCD_Draw_Line(x, y - 12, x, y + 13, color); /* 竖线 */
    LCD_Draw_Point(x + 1, y + 1, color);
    LCD_Draw_Point(x - 1, y + 1, color);
    LCD_Draw_Point(x + 1, y - 1, color);
    LCD_Draw_Point(x - 1, y - 1, color);
    LCD_Draw_Circle(x, y, 6, color); /* 画中心圈 */
}

void TP_Draw_Big_Point(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Draw_Point(x, y, color); /* 中心点 */
    LCD_Draw_Point(x + 1, y, color);
    LCD_Draw_Point(x, y + 1, color);
    LCD_Draw_Point(x + 1, y + 1, color);
}

uint8_t Touch_Sacn(uint8_t mode)
{
    if (TP_IRQ_State == 0) /* 有按键按下 */
    {
        if (mode) /* 读取物理坐标, 无需转换 */
        {
            TP_Read_XY2(&tp_dev.x[0], &tp_dev.y[0]);
        }
        else if (TP_Read_XY2(&tp_dev.x[0], &tp_dev.y[0])) /* 读取屏幕坐标, 需要转换 */
        {
            /* 将X轴 物理坐标转换成逻辑坐标(即对应LCD屏幕上面的X坐标值) */
            tp_dev.x[0] = (signed short)(tp_dev.x[0] - tp_dev.xc) / tp_dev.xfac + LCD_WIDTH / 2;

            /* 将Y轴 物理坐标转换成逻辑坐标(即对应LCD屏幕上面的Y坐标值) */
            tp_dev.y[0] = (signed short)(tp_dev.y[0] - tp_dev.yc) / tp_dev.yfac + LCD_HEIGHT / 2;
        }

        if ((tp_dev.sta & TP_PRES_DOWN) == 0) /* 之前没有被按下 */
        {
            tp_dev.sta = TP_PRES_DOWN | TP_CATH_PRES; /* 按键按下 */
            tp_dev.x[CT_MAX_TOUCH - 1] = tp_dev.x[0]; /* 记录第一次按下时的坐标 */
            tp_dev.y[CT_MAX_TOUCH - 1] = tp_dev.y[0];
        }
    }
    else
    {
        if (tp_dev.sta & TP_PRES_DOWN) /* 之前是被按下的 */
        {
            tp_dev.sta &= ~TP_PRES_DOWN; /* 标记按键松开 */
        }
        else /* 之前就没有被按下 */
        {
            tp_dev.x[CT_MAX_TOUCH - 1] = 0;
            tp_dev.y[CT_MAX_TOUCH - 1] = 0;
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
        }
    }

    return tp_dev.sta & TP_PRES_DOWN; /* 返回当前的触屏状态 */
}
// 提示校准结果(各个参数)
void TP_Adjust_Info_Show(uint16_t xy[5][2], double px, double py)
{
    uint8_t i;
    char sbuf[20];
    for (i = 0; i < 5; i++) /* 显示5个物理坐标值 */
    {
        LCD_Show_String(40, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
        LCD_Show_String(40 + 80, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
    }

    /* 显示X/Y方向的比例因子 */
    LCD_Fill(40, 160 + (i * 20), LCD_WIDTH - 1, 16, 0xFFFF); /* 清除之前的px,py显示 */
    sbuf[7] = 0;                                             /* 添加结束符 */
    LCD_Show_String(40, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
    sbuf[7] = 0; /* 添加结束符 */
    LCD_Show_String(40 + 80, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
}
