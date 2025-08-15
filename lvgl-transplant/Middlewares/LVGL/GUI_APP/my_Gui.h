#ifndef _MY_GUI_H
#define _MY_GUI_H
#include <stdio.h>
#include "lvgl/lvgl.h"
void my_Gui(void);



//声明事件处理函数
static void Toggle_UI(lv_event_t* e);

//显示设置按钮
void Display_SetBtn(void);
//显示主页人物按钮
void Display_PersonBtn(void);
void Display_HomeBtn(void);



//--------------------------------------------------------------------------------------------------------------------
//界面加载相关
void First_Load(void);
void Header_Init(void);
void Footer_Init(void);
void Container_Init(void);
void Display_SaveBtn(void);

void Load_Setting(void);
void Load_Adjust(void);



//
void slider_draw_event_cb(lv_event_t * e);
void arrow_event_cb(lv_event_t * e);
lv_coord_t value_to_y(int value, int slider_min, int slider_max, lv_coord_t slider_h);



#endif // _MY_GUI_H
