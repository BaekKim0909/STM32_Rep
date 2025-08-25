#include "fsmc.h"

void FSMC_Init(void)
{
    // 1. 开启时钟
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;

    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPGEN | RCC_APB2ENR_IOPEEN | RCC_APB2ENR_IOPBEN);

    // 2.配置GPIO工作模式
    FSMC_GPIO_Init();

    //3.FSMC 配置 BCR
    //3.1 存储块使能 片选线选择的是NE4 BCR4----BTCR[6]
    FSMC_Bank1->BTCR[6] |= FSMC_BCRx_MBKEN;

    //3.2 设置存储器类型 00:SRAM
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCRx_MTYP;

    //3.3 禁止访问闪存
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCRx_FACCEN;

    //3.4 数据宽度 01：16位
    FSMC_Bank1->BTCR[6] |= FSMC_BCRx_MWID_0;
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCRx_MWID_1;

    //3.5 地址数据线不复用
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCRx_MUXEN;

    //3.6 开启写使能
    FSMC_Bank1->BTCR[6] |= FSMC_BCRx_WREN;

    //4. FSMC配置BTR  BTR4 ----BTCR[7]
    //4.1 地址建立时间ADDSET
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTRx_ADDSET;
    //4,2 数据保存时间DATASET
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTRx_DATAST;
    FSMC_Bank1->BTCR[7] |= (71<<8);
}

void FSMC_GPIO_Init(void)
{
    // 地址线 FSMC_A10 : PG0     复用推挽输出 MODE:11  CNF:10
    GPIOG->CRL |= GPIO_CRL_MODE0;
    GPIOG->CRL &= ~GPIO_CRL_CNF0_0;
    GPIOG->CRL |= GPIO_CRL_CNF0_1;

    // 数据线  复用推挽输出  MODE:11  CNF:10
    GPIOD->CRL |= (GPIO_CRL_MODE0 |
                   GPIO_CRL_MODE1);
    GPIOD->CRH |= (GPIO_CRH_MODE8 |
                   GPIO_CRH_MODE9 |
                   GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    GPIOE->CRL |= (GPIO_CRL_MODE7);
    GPIOE->CRH |= (GPIO_CRH_MODE8 |
                   GPIO_CRH_MODE9 |
                   GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE11 |
                   GPIO_CRH_MODE12 |
                   GPIO_CRH_MODE13 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    GPIOD->CRL |= (GPIO_CRL_CNF0_1 |
                   GPIO_CRL_CNF1_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0_0 |
                    GPIO_CRL_CNF1_0);

    GPIOD->CRH |= (GPIO_CRH_CNF8_1 |
                   GPIO_CRH_CNF9_1 |
                   GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF8_0 |
                    GPIO_CRH_CNF9_0 |
                    GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    GPIOE->CRL |= (GPIO_CRL_CNF7_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF7_0);

    GPIOE->CRH |= (GPIO_CRH_CNF8_1 |
                   GPIO_CRH_CNF9_1 |
                   GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF11_1 |
                   GPIO_CRH_CNF12_1 |
                   GPIO_CRH_CNF13_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOE->CRH &= ~(GPIO_CRH_CNF8_0 |
                    GPIO_CRH_CNF9_0 |
                    GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF11_0 |
                    GPIO_CRH_CNF12_0 |
                    GPIO_CRH_CNF13_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);
    //控制信号 FSMC_NOE：PD4   FSMC_NWE:PD5 复用推挽输出 MODE:11  CNF:10
    GPIOD->CRL |= (GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
    GPIOD->CRL |= (GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);
    //片选信号 FSMC_NE4:PG12 复用推挽输出 MODE:11  CNF:10
    GPIOG->CRH |= GPIO_CRH_MODE12;
    GPIOG->CRH |= GPIO_CRH_CNF12_1;
    GPIOG->CRH &= ~GPIO_CRH_CNF12_0;
    //背光控制 LCD_BL:PB0  通用推挽输出 MODE:11 CNF:00
    GPIOB->CRL |= GPIO_CRL_MODE0;
    GPIOB->CRL &= ~GPIO_CRL_CNF0;
}
