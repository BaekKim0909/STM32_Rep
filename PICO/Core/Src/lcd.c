#include "lcd.h"
#include "lcdfont.h"
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
// ���ģ��SPI����һ���ֽ�
void LCD_SPI_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            LCD_MOSI_High();
        }
        else
        {
            LCD_MOSI_Low();
        }
        LCD_SCK_Low();
        LCD_SCK_High();

        data <<= 1;
    }
}
// д����(8bit)
void LCD_WR_REG(uint8_t cmd)
{
    LCD_CS_Low();
    LCD_DC_Low(); // DC=0  ��ʾд����
    LCD_SPI_WriteByte(cmd);
    LCD_CS_High();
}
// д����(8bit)
void LCD_WR_DATA(uint8_t data)
{
    LCD_CS_Low();
    LCD_DC_High(); // DC=1 ��ʾд����
    LCD_SPI_WriteByte(data);
    LCD_CS_High();
}

// дһ������
void LCD_WriteRam(uint16_t color)
{
    LCD_CS_Low();
    LCD_DC_High();
    LCD_SPI_WriteByte(color >> 8);   // �ȷ��߰�λ
    LCD_SPI_WriteByte(color & 0xFF); // �󷢵Ͱ�λ
    LCD_CS_High();
}

// д�������ص�׼��
void LCD_WriteRam_Prepare(void)
{
    LCD_WR_REG(0x2C);
}

// ��������Χ
void LCD_SetArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    // 1. �����з�Χ
    LCD_WR_REG(0x2A);
    // 1.1 ��ʼ��
    LCD_WR_DATA((x >> 8) & 0xFF);
    LCD_WR_DATA(x & 0xFF);
    // 1.2 ������
    LCD_WR_DATA(((x + width - 1) >> 8) & 0xFF);
    LCD_WR_DATA((x + width - 1) & 0xFF);

    // 2. �����з�Χ
    LCD_WR_REG(0x2B);
    // 2.1 ��ʼ��
    LCD_WR_DATA((y >> 8) & 0xFF);
    LCD_WR_DATA(y & 0xFF);
    // 2.2������
    LCD_WR_DATA(((y + height - 1) >> 8) & 0xFF);
    LCD_WR_DATA((y + height - 1) & 0xFF);
}
// ���ù��λ��
void LCD_SET_Cursor(uint16_t x, uint16_t y)
{

    LCD_WR_REG(0x2A);
    LCD_WR_DATA(x >> 8);
    LCD_WR_DATA(x & 0xFF);
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(y >> 8);
    LCD_WR_DATA(y & 0XFF);
}

// ����
void LCD_Clear(uint16_t color)
{

    LCD_SetArea(0, 0, LCD_WIDTH, LCD_HEIGHT);
    LCD_WriteRam_Prepare();
    LCD_CS_Low();
    LCD_DC_High();
    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    {
        LCD_WriteRam(color);
        // LCD_SPI_WriteByte(color >> 8);   // �ȷ��߰�λ
        // LCD_SPI_WriteByte(color & 0xFF); // �󷢵Ͱ�λ
    }
    LCD_CS_High();
}

// ��ָ����������䵥����ɫ
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;
    for (i = sy; i <= ey; i++)
    {
        LCD_SET_Cursor(sx, i);  /* ���ù��λ�� */
        LCD_WriteRam_Prepare(); /* ��ʼд��GRAM */
        LCD_CS_Low();
        LCD_DC_High();
        for (j = 0; j < xlen; j++)
        {
            LCD_SPI_WriteByte(color >> 8);   // ��8λ
            LCD_SPI_WriteByte(color & 0xFF); // ��8λ
        }
        LCD_CS_High();
    }
}

// ��ָ�����������ָ����ɫ��
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint16_t w = ex - sx + 1;
    uint16_t h = ey - sy + 1;

    LCD_SetArea(sx, sy, w, h);
    uint32_t draw_size = w * h;
    LCD_WriteRam_Prepare();
    LCD_CS_Low();
    LCD_DC_High();
    for (uint32_t i = 0; i < draw_size; i++)
    {
        uint16_t c = color[i];
        LCD_SPI_WriteByte(c >> 8);   // ��8λ
        LCD_SPI_WriteByte(c & 0xFF); // ��8λ
    }
    LCD_CS_High();
}
// ����
void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{

    LCD_SET_Cursor(x, y);   /* ���ù��λ�� */
    LCD_WriteRam_Prepare(); /* ��ʼд��GRAM */

    LCD_CS_Low();
    LCD_DC_High();
    LCD_SPI_WriteByte(color >> 8);   // ��8λ
    LCD_SPI_WriteByte(color & 0xFF); // ��8λ
    LCD_CS_High();
}
// չʾһ���ַ�
void LCD_Show_Char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t *pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); /* �õ�����һ���ַ���Ӧ������ռ���ֽ��� */
    chr = chr - ' ';                                        /* �õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩ */

    switch (size)
    {
    case 12:
        pfont = (uint8_t *)asc2_1206[chr]; /* ����1206���� */
        break;

    case 16:
        pfont = (uint8_t *)asc2_1608[chr]; /* ����1608���� */
        break;

    case 24:
        pfont = (uint8_t *)asc2_2412[chr]; /* ����2412���� */
        break;

    case 32:
        pfont = (uint8_t *)asc2_3216[chr]; /* ����3216���� */
        break;

    default:
        return;
    }

    for (t = 0; t < csize; t++)
    {
        temp = pfont[t]; /* ��ȡ�ַ��ĵ������� */

        for (t1 = 0; t1 < 8; t1++) /* һ���ֽ�8���� */
        {
            if (temp & 0x80) /* ��Ч��,��Ҫ��ʾ */
            {
                LCD_Draw_Point(x, y, color); /* �������,Ҫ��ʾ����� */
            }
            else if (mode == 0) /* ��Ч��,����ʾ */
            {
                LCD_Draw_Point(x, y, LCD_BACKGROUNDCOLOR); /* ������ɫ,�൱������㲻��ʾ(ע�ⱳ��ɫ��ȫ�ֱ�������) */
            }

            temp <<= 1; /* ��λ, �Ա��ȡ��һ��λ��״̬ */
            y++;

            if (y >= LCD_HEIGHT)
                return; /* �������� */

            if ((y - y0) == size) /* ��ʾ��һ����? */
            {
                y = y0; /* y���긴λ */
                x++;    /* x������� */

                if (x >= LCD_WIDTH)
                    return; /* x���곬������ */

                break;
            }
        }
    }
}
uint32_t LCD_POW(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while (n--)
        result *= m;

    return result;
}

/**
 * @brief       ��ʾ�ַ���
 * @param       x,y         : ��ʼ����
 * @param       width,height: �����С
 * @param       size        : ѡ������ 12/16/24/32
 * @param       p           : �ַ����׵�ַ
 * @param       color       : �ַ�������ɫ;
 * @retval      ��
 */
void LCD_Show_String(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' ')) /* �ж��ǲ��ǷǷ��ַ�! */
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)
            break; /* �˳� */

        LCD_Show_Char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}
/**
 * @brief       ��ʾlen������
 * @param       x,y : ��ʼ����
 * @param       num : ��ֵ(0 ~ 2^32)
 * @param       len : ��ʾ���ֵ�λ��
 * @param       size: ѡ������ 12/16/24/32
 * @param       color : ���ֵ���ɫ;
 * @retval      ��
 */
void LCD_Show_Num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color){
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++)   /* ������ʾλ��ѭ�� */
    {
        temp = (num / LCD_POW(10, len - t - 1)) % 10;   /* ��ȡ��Ӧλ������ */

        if (enshow == 0 && t < (len - 1))   /* û��ʹ����ʾ,�һ���λҪ��ʾ */
        {
            if (temp == 0)
            {
                LCD_Show_Char(x + (size / 2)*t, y, ' ', size, 0, color);/* ��ʾ�ո�,ռλ */
                continue;   /* �����¸�һλ */
            }
            else
            {
                enshow = 1; /* ʹ����ʾ */
            }

        }

        LCD_Show_Char(x + (size / 2)*t, y, temp + '0', size, 0, color); /* ��ʾ�ַ� */
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

// ����
void LCD_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1; /* ������������ */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0)
        incx = 1; /* ���õ������� */
    else if (delta_x == 0)
        incx = 0; /* ��ֱ�� */
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; /* ˮƽ�� */
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)
        distance = delta_x; /* ѡȡ�������������� */
    else
        distance = delta_y;

    for (t = 0; t <= distance + 1; t++) /* ������� */
    {
        LCD_Draw_Point(row, col, color); /* ���� */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

// ��Բ
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1); /* �ж��¸���λ�õı�־ */

    while (a <= b)
    {
        LCD_Draw_Point(x0 + a, y0 - b, color); /* 5 */
        LCD_Draw_Point(x0 + b, y0 - a, color); /* 0 */
        LCD_Draw_Point(x0 + b, y0 + a, color); /* 4 */
        LCD_Draw_Point(x0 + a, y0 + b, color); /* 6 */
        LCD_Draw_Point(x0 - a, y0 + b, color); /* 1 */
        LCD_Draw_Point(x0 - b, y0 + a, color);
        LCD_Draw_Point(x0 - a, y0 - b, color); /* 2 */
        LCD_Draw_Point(x0 - b, y0 - a, color); /* 7 */
        a++;

        /* ʹ��Bresenham�㷨��Բ */
        if (di < 0)
        {
            di += 4 * a + 6;
        }
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}
