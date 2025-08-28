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

// MCU������ICд1Byte����
void TP_Write_Byte(uint8_t data)
{
    for (uint8_t count = 0; count < 8; count++)
    {
        if (data & 0x80) /* ����1 */
        {
            TP_MOSI_High();
        }
        else /* ����0 */
        {
            TP_MOSI_Low();
        }

        data <<= 1;

        TP_SCK_Low();
        delay_us(1);
        // HAL_Delay(1);
        TP_SCK_High(); /* ��������Ч */
    }
}

// �Ӵ�����IC��ȡadcֵ
uint16_t TP_Read_AD(uint8_t cmd)
{
    uint16_t num = 0;

    TP_SCK_Low();  /* ������ʱ�� */
    TP_MOSI_Low(); /* ���������� */
    TP_CS_Low();   /* ѡ�д�����IC */

    TP_Write_Byte(cmd); /* ���������� */
    delay_us(6);       /* ADS7846��ת��ʱ���Ϊ6us */
    //HAL_Delay(1);

    TP_SCK_Low();
    delay_us(1);
    //HAL_Delay(1);

    TP_SCK_High(); /* ��1��ʱ�ӣ����BUSY */
    delay_us(1);
    //HAL_Delay(1);

    TP_SCK_Low();

    for (uint8_t count = 0; count < 16; count++) /* ����16λ����,ֻ�и�12λ��Ч */
    {
        num <<= 1;
        TP_SCK_Low(); /* �½�����Ч */
        delay_us(1);
        //HAL_Delay(1);

        TP_SCK_High();

        if (TP_MISO_State)
            num++;
    }

    num >>= 4;    /* ֻ�и�12λ��Ч. */
    TP_CS_High(); /* �ͷ�Ƭѡ */
    return num;
    /* --------------------------------------------*/
    // uint16_t r_data = 0;
    // // ��ʼ״̬
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
// ��ʼ��
uint8_t Touch_Init(void)
{
    LCD_Clear(0xFFFF); /* ���� */
    Touch_Adjust();    /* ��ĻУ׼ */
    return 1;
}

// ������У׼
void Touch_Adjust(void)
{
    uint16_t pxy[5][2]; /* �������껺��ֵ */
    uint8_t cnt = 0;
    short s1, s2, s3, s4; /* 4����������ֵ */
    double px, py;        /* X,Y�������������,�����ж��Ƿ�У׼�ɹ� */
    uint16_t outtime = 0;
    cnt = 0;
    LCD_Clear(0xFFFF);                                                                                                                                                         /* ���� */
    LCD_Show_String(40, 40, 160, 100, 16, "Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.", 0xF800); /* ��ʾ��ʾ��Ϣ */
    TP_Draw_Touch_Point(20, 20, 0xF800);                                                                                                                                       /* ����1 */
    tp_dev.sta = 0;                                                                                                                                                            /* ���������ź� */

    while (1) /* �������10����û�а���,���Զ��˳� */
    {
        tp_dev.scan(1);                            /* ɨ���������� */
        if ((tp_dev.sta & 0xc000) == TP_CATH_PRES) /* ����������һ��(��ʱ�����ɿ���.) */
        {
            outtime = 0;
            tp_dev.sta &= ~TP_CATH_PRES; /* ��ǰ����Ѿ����������. */

            pxy[cnt][0] = tp_dev.x[0]; /* ����X�������� */
            pxy[cnt][1] = tp_dev.y[0]; /* ����Y�������� */
            cnt++;

            switch (cnt)
            {
            case 1:
                TP_Draw_Touch_Point(20, 20, 0xFFFF);             /* �����1 */
                TP_Draw_Touch_Point(LCD_WIDTH - 20, 20, 0xF800); /* ����2 */
                break;

            case 2:
                TP_Draw_Touch_Point(LCD_WIDTH - 20, 20, 0xFFFF);  /* �����2 */
                TP_Draw_Touch_Point(20, LCD_HEIGHT - 20, 0xF800); /* ����3 */
                break;

            case 3:
                TP_Draw_Touch_Point(20, LCD_HEIGHT - 20, 0xFFFF);             /* �����3 */
                TP_Draw_Touch_Point(LCD_WIDTH - 20, LCD_HEIGHT - 20, 0xF800); /* ����4 */
                break;

            case 4:
                LCD_Clear(0xFFFF);                                          /* �����������, ֱ������ */
                TP_Draw_Touch_Point(LCD_WIDTH / 2, LCD_HEIGHT / 2, 0xF800); /* ����5 */
                break;

            case 5:                         /* ȫ��5�����Ѿ��õ� */
                s1 = pxy[1][0] - pxy[0][0]; /* ��2����͵�1�����X�����������ֵ(ADֵ) */
                s3 = pxy[3][0] - pxy[2][0]; /* ��4����͵�3�����X�����������ֵ(ADֵ) */
                s2 = pxy[3][1] - pxy[1][1]; /* ��4����͵�2�����Y�����������ֵ(ADֵ) */
                s4 = pxy[2][1] - pxy[0][1]; /* ��3����͵�1�����Y�����������ֵ(ADֵ) */

                px = (double)s1 / s3; /* X��������� */
                py = (double)s2 / s4; /* Y��������� */

                if (px < 0)
                    px = -px; /* ���������� */
                if (py < 0)
                    py = -py; /* ���������� */

                if (px < 0.95 || px > 1.05 || py < 0.95 || py > 1.05 ||                     /* �������ϸ� */
                    abs(s1) > 4095 || abs(s2) > 4095 || abs(s3) > 4095 || abs(s4) > 4095 || /* ��ֵ���ϸ�, �������귶Χ */
                    abs(s1) == 0 || abs(s2) == 0 || abs(s3) == 0 || abs(s4) == 0            /* ��ֵ���ϸ�, ����0 */
                )
                {
                    cnt = 0;
                    TP_Draw_Touch_Point(LCD_WIDTH / 2, LCD_HEIGHT / 2, 0xFFFF); /* �����5 */
                    TP_Draw_Touch_Point(20, 20, 0xF800);                        /* ���»���1 */
                    TP_Adjust_Info_Show(pxy, px, py);                           /* ��ʾ��ǰ��Ϣ,���������� */
                    continue;
                }

                tp_dev.xfac = (float)(s1 + s3) / (2 * (LCD_WIDTH - 40));
                tp_dev.yfac = (float)(s2 + s4) / (2 * (LCD_HEIGHT - 40));

                tp_dev.xc = pxy[4][0]; /* X��,������������ */
                tp_dev.yc = pxy[4][1]; /* Y��,������������ */

                LCD_Clear(0xFFFF);                                                                      /* ���� */
                LCD_Show_String(35, 110, LCD_WIDTH, LCD_HEIGHT, 16, "Touch Screen Adjust OK!", 0x001F); /* У����� */
                HAL_Delay(1000);

                LCD_Clear(0xFFFF); /* ���� */
                return;            /* У����� */
            }
        }
        HAL_Delay(10);
        outtime++;
    }
}

/* ���败������оƬ ���ݲɼ� �˲��ò��� */
#define TP_READ_TIMES 5 /* ��ȡ���� */
#define TP_LOST_VAL 1   /* ����ֵ */

/**
 * @brief       ��ȡһ������ֵ(x����y)
 * @note        ������ȡTP_READ_TIMES������,����Щ������������,
 *              Ȼ��ȥ����ͺ����TP_LOST_VAL����, ȡƽ��ֵ
 *              ����ʱ������: TP_READ_TIMES > 2*TP_LOST_VAL ������
 * @param       cmd : ָ��
 *              0XD0: ��ȡX������(@����״̬,����״̬��Y�Ե�.)
 *              0X90: ��ȡY������(@����״̬,����״̬��X�Ե�.)
 * @retval      ��ȡ��������(�˲����), ADCֵ(12bit)
 */

uint16_t TP_Read_XoY(uint8_t cmd)
{
    uint16_t buf[TP_READ_TIMES];
    uint16_t sum = 0;

    for (uint16_t i = 0; i < TP_READ_TIMES; i++) /* �ȶ�ȡTP_READ_TIMES������ */
    {
        buf[i] = TP_Read_AD(cmd);
    }

    /* �������� */
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

    /* ȥ�����˵Ķ���ֵ */
    for (uint16_t i = TP_LOST_VAL; i < TP_READ_TIMES - TP_LOST_VAL; i++)
    {
        sum += buf[i];
    }

    return sum / (TP_READ_TIMES - 2 * TP_LOST_VAL); /* ȡƽ��ֵ */
}

/**
 * @brief       ��ȡx, y����
 * @param       x,y: ��ȡ��������ֵ
 * @retval      ��
 */
void TP_Read_XY(uint16_t *x, uint16_t *y)
{
    uint16_t xval, yval;

    /* X,Y��������Ļ��ͬ */

    xval = TP_Read_XoY(0XD0); /* ��ȡX������ADֵ */
    yval = TP_Read_XoY(0X90); /* ��ȡY������ADֵ */

    *x = xval;
    *y = yval;
}

/* �������ζ�ȡX,Y�������������������ֵ */
#define TP_ERR_RANGE 50 /* ��Χ */
/**
 * @brief       ������ȡ2�δ���IC����, ���˲�
 * @note        ����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���ERR_RANGE,����
 *              ����,����Ϊ������ȷ,�����������.�ú����ܴ�����׼ȷ��.
 * @param       x,y: ��ȡ��������ֵ
 * @retval      0, ʧ��; 1, �ɹ�;
 */
uint8_t TP_Read_XY2(uint16_t *x, uint16_t *y)
{
    uint16_t x1, y1;
    uint16_t x2, y2;

    TP_Read_XY(&x1, &y1); /* ��ȡ��һ������ */
    TP_Read_XY(&x2, &y2); /* ��ȡ�ڶ������� */

    /* ǰ�����β�����+-TP_ERR_RANGE�� */
    if (((x2 <= x1 && x1 < x2 + TP_ERR_RANGE) || (x1 <= x2 && x2 < x1 + TP_ERR_RANGE)) &&
        ((y2 <= y1 && y1 < y2 + TP_ERR_RANGE) || (y1 <= y2 && y2 < y1 + TP_ERR_RANGE)))
    {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    }

    return 0;
}

// ��һ��У׼�õĴ�����(ʮ�ּ�)
void TP_Draw_Touch_Point(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Draw_Line(x - 12, y, x + 13, y, color); /* ���� */
    LCD_Draw_Line(x, y - 12, x, y + 13, color); /* ���� */
    LCD_Draw_Point(x + 1, y + 1, color);
    LCD_Draw_Point(x - 1, y + 1, color);
    LCD_Draw_Point(x + 1, y - 1, color);
    LCD_Draw_Point(x - 1, y - 1, color);
    LCD_Draw_Circle(x, y, 6, color); /* ������Ȧ */
}

void TP_Draw_Big_Point(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Draw_Point(x, y, color); /* ���ĵ� */
    LCD_Draw_Point(x + 1, y, color);
    LCD_Draw_Point(x, y + 1, color);
    LCD_Draw_Point(x + 1, y + 1, color);
}

uint8_t Touch_Sacn(uint8_t mode)
{
    if (TP_IRQ_State == 0) /* �а������� */
    {
        if (mode) /* ��ȡ��������, ����ת�� */
        {
            TP_Read_XY2(&tp_dev.x[0], &tp_dev.y[0]);
        }
        else if (TP_Read_XY2(&tp_dev.x[0], &tp_dev.y[0])) /* ��ȡ��Ļ����, ��Ҫת�� */
        {
            /* ��X�� ��������ת�����߼�����(����ӦLCD��Ļ�����X����ֵ) */
            tp_dev.x[0] = (signed short)(tp_dev.x[0] - tp_dev.xc) / tp_dev.xfac + LCD_WIDTH / 2;

            /* ��Y�� ��������ת�����߼�����(����ӦLCD��Ļ�����Y����ֵ) */
            tp_dev.y[0] = (signed short)(tp_dev.y[0] - tp_dev.yc) / tp_dev.yfac + LCD_HEIGHT / 2;
        }

        if ((tp_dev.sta & TP_PRES_DOWN) == 0) /* ֮ǰû�б����� */
        {
            tp_dev.sta = TP_PRES_DOWN | TP_CATH_PRES; /* �������� */
            tp_dev.x[CT_MAX_TOUCH - 1] = tp_dev.x[0]; /* ��¼��һ�ΰ���ʱ������ */
            tp_dev.y[CT_MAX_TOUCH - 1] = tp_dev.y[0];
        }
    }
    else
    {
        if (tp_dev.sta & TP_PRES_DOWN) /* ֮ǰ�Ǳ����µ� */
        {
            tp_dev.sta &= ~TP_PRES_DOWN; /* ��ǰ����ɿ� */
        }
        else /* ֮ǰ��û�б����� */
        {
            tp_dev.x[CT_MAX_TOUCH - 1] = 0;
            tp_dev.y[CT_MAX_TOUCH - 1] = 0;
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
        }
    }

    return tp_dev.sta & TP_PRES_DOWN; /* ���ص�ǰ�Ĵ���״̬ */
}
// ��ʾУ׼���(��������)
void TP_Adjust_Info_Show(uint16_t xy[5][2], double px, double py)
{
    uint8_t i;
    char sbuf[20];
    for (i = 0; i < 5; i++) /* ��ʾ5����������ֵ */
    {
        LCD_Show_String(40, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
        LCD_Show_String(40 + 80, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
    }

    /* ��ʾX/Y����ı������� */
    LCD_Fill(40, 160 + (i * 20), LCD_WIDTH - 1, 16, 0xFFFF); /* ���֮ǰ��px,py��ʾ */
    sbuf[7] = 0;                                             /* ��ӽ����� */
    LCD_Show_String(40, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
    sbuf[7] = 0; /* ��ӽ����� */
    LCD_Show_String(40 + 80, 160 + (i * 20), LCD_WIDTH, LCD_HEIGHT, 16, sbuf, 0xF800);
}
