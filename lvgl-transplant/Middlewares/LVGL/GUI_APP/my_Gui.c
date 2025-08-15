#include "my_Gui.h"
//容器
static lv_obj_t* Header;
static lv_obj_t* Container;
static lv_obj_t* Footer;
//设置按钮
static lv_obj_t* Setting_Btn;
//人物按钮
static lv_obj_t* Person_Btn;
//主页按钮
static lv_obj_t* Home_Btn;

//--------设置界面相关组件------------
//调节按钮
static lv_obj_t*   Adjust_Btn;

//下限Label
static lv_obj_t* Label_Bottom;
//上限Label
static lv_obj_t* Label_Top;

static lv_obj_t* Adjust_Slider;
//箭头相关
static lv_obj_t * img_left;
static lv_obj_t * img_right;

//保存按钮
static lv_obj_t * save_btn =NULL;

// 拖动起始值和起始触摸位置
static int drag_start_value;
static lv_coord_t drag_start_y;
// 滑块相关变量
static int slider_min = 0;
static int slider_max = 15;
static int slider_h = 200;
static int32_t upper_limit_value = 10;
static int32_t lower_limit_value= 6;



//声明图片源
LV_IMG_DECLARE(set_img);
LV_IMG_DECLARE(person_img);
LV_IMG_DECLARE(home_img);
LV_IMG_DECLARE(adjust_img);
LV_IMG_DECLARE(left_arrow);
LV_IMG_DECLARE(right_arrow);
LV_IMG_DECLARE(save_img);

enum{
    Home,
    Setting
};


//外部调用
void my_Gui(void){
        // 禁用屏幕的滚动
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
        First_Load();
}




//设置按钮处理函数
static void Toggle_UI(lv_event_t* e){
    lv_obj_t* target = lv_event_get_target(e);
    if(target  == Setting_Btn ){
        //删除Container中的内容
        lv_obj_del(Container);
        Container = NULL;
        Person_Btn = NULL;

        //设置页面不显示设置按钮
        lv_obj_del(Setting_Btn);
        Setting_Btn = NULL;

        //重新初始化容器
        Container_Init();
        Display_HomeBtn();
        //加载设置界面
        Load_Setting();

    }else if(target == Home_Btn){
        //删除Container中的内容
        lv_obj_del(Container);
        Container = NULL;
        Adjust_Btn =NULL;
        Adjust_Slider =NULL;
        //重新初始化容器
        Container_Init();
        Display_PersonBtn();
        //首页不显示首页按钮
        lv_obj_del(Home_Btn);
        if (save_btn != NULL)
        {
            /* code */
            lv_obj_del(save_btn);
            save_btn = NULL;
        }
        Home_Btn = NULL;
        //首页显示设置按钮
        Display_SetBtn();
    }else if(target == Adjust_Btn){
        //删除Container中的内容
        lv_obj_del(Container);
        Container = NULL;
        Adjust_Btn = NULL;
        //重新初始化容器
        Container_Init();
        Load_Adjust();
        Display_SaveBtn();
    }else if (target == save_btn)
    {
        if (Adjust_Slider != NULL)
        {
            lower_limit_value = lv_slider_get_left_value(Adjust_Slider);
            upper_limit_value = lv_slider_get_value(Adjust_Slider);
            lv_obj_del(Container);
            Container = NULL;
            Adjust_Slider = NULL;
            lv_obj_del(save_btn);
            save_btn = NULL;
            Container_Init();
            Load_Setting();
        }
        
    }
    
}






//------------------------------------界面加载相关函数--------------------------------------------------------
static void First_Load(void){
    //初始化头部
    Header_Init();
    Display_SetBtn();

    //初始化主体
    Container_Init();
    Display_PersonBtn();

    //初始化底部
    Footer_Init();
}

void Header_Init(void){
    //创建顶部容器
    Header = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(Header);  // 清除默认样式
    lv_obj_set_size(Header,240,35);
    lv_obj_set_align(Header,LV_ALIGN_TOP_MID);
    // 设置样式
    lv_obj_set_style_bg_color(Header, lv_color_hex(0x1E90FF), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(Header, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(Header, 0, LV_PART_MAIN);  // 去除圆角
    lv_obj_set_style_border_width(Header, 0, LV_PART_MAIN);  // 去除边框
    lv_obj_set_style_pad_all(Header, 5, LV_PART_MAIN);  // 设置内边距
    // 禁止滚动
    lv_obj_clear_flag(Header, LV_OBJ_FLAG_SCROLLABLE);

}
//底部界面初始化
void Footer_Init(void){
    Footer = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(Footer);  // 清除默认样式
    lv_obj_set_size(Footer,240,50);
    lv_obj_set_align(Footer,LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(Footer,lv_color_hex(0x1E90FF),LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(Footer, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(Footer, 0, LV_PART_MAIN);  // 去除圆角
    lv_obj_set_style_border_width(Footer, 0, LV_PART_MAIN);  // 去除边框
    lv_obj_set_style_pad_all(Footer, 5, LV_PART_MAIN);  // 设置内边距

    // 禁止滚动
    lv_obj_clear_flag(Footer, LV_OBJ_FLAG_SCROLLABLE);
}

//主容器初始化
void Container_Init(void){

    //容器初始化
    Container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Container,240,235);
    lv_obj_set_pos(Container,0,35);
    lv_obj_set_style_bg_color(Container,lv_color_hex(0xFFFFF0),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Container, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(Container, 0, LV_PART_MAIN);  // 去除圆角
    lv_obj_set_style_border_width(Container, 0, LV_PART_MAIN);  // 去除边框
    lv_obj_set_style_pad_all(Container, 5, LV_PART_MAIN);  // 设置内边距
    // 禁止滚动
    lv_obj_clear_flag(Container, LV_OBJ_FLAG_SCROLLABLE);
}

//加载设置界面
void Load_Setting(void){
    //调节上下限按钮
    Adjust_Btn=lv_imgbtn_create(Container);
    lv_imgbtn_set_src(Adjust_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&adjust_img,NULL);
    lv_obj_set_size(Adjust_Btn,28,86);
    lv_obj_set_pos(Adjust_Btn,170,60);
    //添加事件
    lv_obj_add_event_cb(Adjust_Btn,Toggle_UI,LV_EVENT_PRESSED,NULL);
}
//加载调节上下限界面
void Load_Adjust(void)
{
    //创建调节滑块
    Adjust_Slider = lv_slider_create(Container);
    lv_obj_set_size(Adjust_Slider, 20, slider_h);              // 竖向滑块
    lv_obj_set_align(Adjust_Slider, LV_ALIGN_CENTER);
    lv_slider_set_mode(Adjust_Slider, LV_SLIDER_MODE_RANGE); // 范围模式：有两个滑块手柄
    lv_slider_set_range(Adjust_Slider, 0, 15);

    // 设置轨道和指示条透明，防止重叠颜色影响
    lv_obj_set_style_bg_opa(Adjust_Slider, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(Adjust_Slider, LV_OPA_TRANSP, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(Adjust_Slider, LV_OPA_TRANSP, LV_PART_KNOB);

    // 绑定自定义绘制回调，绘制三段颜色轨道
    lv_obj_add_event_cb(Adjust_Slider, slider_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    //lv_obj_add_event_cb(Adjust_Slider, slider_limit_cb, LV_EVENT_VALUE_CHANGED, NULL);

    //禁止滑块滑动
    lv_obj_clear_flag(Adjust_Slider, LV_OBJ_FLAG_CLICKABLE);

    //创建label
    Label_Top = lv_label_create(Container);
    lv_obj_set_pos(Label_Top,85,value_to_y(upper_limit_value,slider_min,slider_max,slider_h)-3);
    lv_label_set_text_fmt(Label_Top,"%d",upper_limit_value);

    Label_Bottom = lv_label_create(Container);
    lv_obj_set_pos(Label_Bottom,130,value_to_y(lower_limit_value,slider_min,slider_max,slider_h)-3);
    lv_label_set_text_fmt(Label_Bottom,"%d",lower_limit_value);

    lv_slider_set_value(Adjust_Slider, upper_limit_value, LV_ANIM_OFF);
    lv_slider_set_left_value(Adjust_Slider, lower_limit_value, LV_ANIM_OFF);
    // 创建左箭头（控制右手柄）
    img_left = lv_img_create(Container);
    lv_img_set_src(img_left, &left_arrow);
    lv_obj_add_flag(img_left, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img_left, arrow_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(img_left, arrow_event_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_set_pos(img_left, 240/2 - 90 - 10 - 5, value_to_y(upper_limit_value,slider_min,slider_max,slider_h)-3);

    // 创建右箭头（控制左手柄）
    img_right = lv_img_create(Container);
    lv_img_set_src(img_right, &right_arrow);
    lv_obj_add_flag(img_right, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img_right, arrow_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(img_right, arrow_event_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_set_pos(img_right, (240)/2 + 5, value_to_y(lower_limit_value,slider_min,slider_max,slider_h)-3);
}

//显示设置按钮
void Display_SetBtn(void){
    Setting_Btn = lv_imgbtn_create(Header);
    lv_imgbtn_set_src(Setting_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&set_img,NULL);
    lv_obj_set_size(Setting_Btn,30,30);
    lv_obj_set_pos(Setting_Btn,5,0);
    //添加事件
    lv_obj_add_event_cb(Setting_Btn,Toggle_UI,LV_EVENT_PRESSED,NULL);
}


//显示人物按钮
void Display_PersonBtn(void){
    Person_Btn = lv_imgbtn_create(Container);
    lv_imgbtn_set_src(Person_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&person_img,NULL);
    lv_obj_set_size(Person_Btn,100,130);
    lv_obj_set_pos(Person_Btn,50,40);
}
//显示Home按钮
void Display_HomeBtn(void){
    Home_Btn = lv_imgbtn_create(Footer);
    lv_imgbtn_set_src(Home_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&home_img,NULL);
    lv_obj_set_size(Home_Btn,40,40);
    lv_obj_set_align(Home_Btn,LV_ALIGN_CENTER);

    //添加事件
    lv_obj_add_event_cb(Home_Btn,Toggle_UI,LV_EVENT_PRESSED,NULL);
}

void Display_SaveBtn(void){
    save_btn = lv_imgbtn_create(Footer);
    lv_imgbtn_set_src(save_btn,LV_IMGBTN_STATE_RELEASED,NULL,&save_img,NULL);
    lv_obj_set_size(save_btn,40,40);
    lv_obj_set_align(save_btn,LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_event_cb(save_btn, Toggle_UI, LV_EVENT_PRESSED, NULL);
}





//---------------------------滑块相关代码-----------------------------------------
/* 自定义滑块轨道绘制，三段颜色 */
 void slider_draw_event_cb(lv_event_t * e)
{

    lv_obj_t * slider = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

    if(dsc->part == LV_PART_MAIN) {
        int32_t min   = lv_slider_get_min_value(slider);
        int32_t max   = lv_slider_get_max_value(slider);
        //下限
        int32_t left  = lv_slider_get_left_value(slider);
        //上限
        int32_t right = lv_slider_get_value(slider);

        if(right < left) {
            int32_t tmp = left; left = right; right = tmp;
        }

        lv_area_t area = *dsc->draw_area;
        lv_coord_t x1 = area.x1;
        lv_coord_t x2 = area.x2;
        lv_coord_t y1 = area.y1;
        lv_coord_t y2 = area.y2;
        lv_coord_t h  = y2 - y1 + 1;

        // 竖直位置映射，y轴越低值越小
        lv_coord_t py_left  = y2 - (lv_coord_t)((int64_t)(left  - min) * h / (max - min));
        lv_coord_t py_right = y2 - (lv_coord_t)((int64_t)(right - min) * h / (max - min));

        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        rect_dsc.bg_opa = LV_OPA_COVER;
        rect_dsc.border_opa = LV_OPA_TRANSP;

        // 1) 下段 绿色
        if(py_left < y2) {
            rect_dsc.bg_color = lv_color_hex(0x32CD32);
            lv_area_t a = {x1, py_left + 1, x2, y2};
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &a);
        }
        // 2) 中段 黄色
        if(py_right <= py_left) {
            rect_dsc.bg_color = lv_color_hex(0xFFA500);
            lv_area_t a = {x1, py_right, x2, py_left};
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &a);
        }
        // 3) 上段 红色
        if(py_right > y1) {
            rect_dsc.bg_color = lv_color_hex(0xFF0000);
            lv_area_t a = {x1, y1, x2, py_right - 1};
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &a);
        }

        // 关闭系统默认轨道绘制
        dsc->rect_dsc->bg_opa = LV_OPA_TRANSP;
        dsc->rect_dsc->border_opa = LV_OPA_TRANSP;
    }
    else if(dsc->part == LV_PART_INDICATOR) {
        dsc->rect_dsc->bg_opa = LV_OPA_TRANSP;
        dsc->rect_dsc->border_opa = LV_OPA_TRANSP;
    }
    else if(dsc->part == LV_PART_KNOB) {
        dsc->rect_dsc->bg_opa = LV_OPA_TRANSP;
        dsc->rect_dsc->border_opa = LV_OPA_TRANSP;
    }
}


//箭头事件
// 映射函数：value -> y (knob中心)
 lv_coord_t value_to_y(int value, int slider_min, int slider_max, lv_coord_t slider_h)
{
    int range = slider_max - slider_min;
    return (slider_max - value) * (slider_h - 1) / range;
}

// 箭头事件回调
 void arrow_event_cb(lv_event_t * e)
{
    lv_obj_t * arrow = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    lv_coord_t slider_h = lv_obj_get_height(Adjust_Slider);

    if(code == LV_EVENT_PRESSED) {
        // 记录起始触摸位置
        lv_point_t p;
        lv_indev_get_point(lv_indev_get_act(), &p);
        drag_start_y = p.y;

        // 记录起始值
        if(arrow == img_right) { // 下限箭头
            drag_start_value = lv_slider_get_left_value(Adjust_Slider);
        } else if(arrow == img_left) { // 上限箭头
            drag_start_value = lv_slider_get_value(Adjust_Slider);
        }
    }
    else if(code == LV_EVENT_PRESSING) {
        lv_point_t p;
        lv_indev_get_point(lv_indev_get_act(), &p);

        // 计算移动的像素差
        int delta_y = p.y - drag_start_y;

        // 像素差转换成值差（向上是增值，向下是减值）
        int range = slider_max - slider_min;
        int delta_value = -(delta_y * range / (slider_h - 1));

        // 新值 = 起始值 + 差值
        int new_value = drag_start_value + delta_value;

        if(arrow == img_right) { // 下限箭头
            int top_value = lv_slider_get_value(Adjust_Slider);

            // 限制范围
            if(new_value < slider_min + 1) new_value = slider_min + 1;
            if(new_value >= top_value) new_value = top_value - 1;

            // 更新 slider 和 label
            lv_slider_set_left_value(Adjust_Slider, new_value, LV_ANIM_OFF);
            lv_label_set_text_fmt(Label_Bottom, "%d", new_value);

            // 箭头位置
            lv_coord_t knob_center_y = value_to_y(new_value, slider_min, slider_max, slider_h);
            lv_obj_set_y(img_right, knob_center_y - 3);
            lv_obj_set_y(Label_Bottom, knob_center_y - lv_obj_get_height(Label_Bottom) / 2);
        }
        else if(arrow == img_left) { // 上限箭头
            int bottom_value = lv_slider_get_left_value(Adjust_Slider);

            // 限制范围
            if(new_value > 14) new_value = 14;
            if(new_value <= bottom_value) new_value = bottom_value + 1;

            // 更新 slider 和 label
            lv_slider_set_value(Adjust_Slider, new_value, LV_ANIM_OFF);
            lv_label_set_text_fmt(Label_Top, "%d", new_value);

            // 箭头位置
            lv_coord_t knob_center_y = value_to_y(new_value, slider_min, slider_max, slider_h);
            lv_obj_set_y(img_left, knob_center_y - 3);
            lv_obj_set_y(Label_Top, knob_center_y - lv_obj_get_height(Label_Top) / 2);
        }
    }
}














