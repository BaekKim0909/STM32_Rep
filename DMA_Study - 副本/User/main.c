/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       串口通信 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./stm32f1xx_it.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "dma.h"


//定义全局变量，表示数据传输完成
uint8_t IsFinsihed = 0;


//定义全局常量数据：常量存在FLASH里
const uint8_t source[] = {10,20,30,40};
//定义变量：变量存在RAM里
uint8_t dest[4] = {0};




int main(void)
{
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟为72Mhz */
    delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    //初始化DMA1
    DMA1_Init();
    //传输数据
    DMA1_Transmit((uint32_t)source,(uint32_t)dest,sizeof(source)/sizeof(source[0]));
    while (1)
    {
        
        if (IsFinsihed)
        {
            /* code */
            //打印输出验证
            printf("source's Address:%p,dest's Address:%p \n",source,dest);
            for (uint8_t i = 0; i < sizeof(dest)/sizeof(dest[0]); i++)
            {
                printf("%d\t",dest[i]);
            }
            
            delay_ms(1000);
        }
        
    }
}



