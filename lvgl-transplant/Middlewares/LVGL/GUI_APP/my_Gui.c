#include "my_Gui.h"
//����
static lv_obj_t* Header;
static lv_obj_t* Container;
static lv_obj_t* Footer;
//���ð�ť
static lv_obj_t* Setting_Btn;
//���ﰴť
static lv_obj_t* Person_Btn;
//��ҳ��ť
static lv_obj_t* Home_Btn;

//--------���ý���������------------
//���ڰ�ť
static lv_obj_t*   Adjust_Btn;

//����Label
static lv_obj_t* Label_Bottom;
//����Label
static lv_obj_t* Label_Top;

static lv_obj_t* Adjust_Slider;
//��ͷ���
static lv_obj_t * img_left;
static lv_obj_t * img_right;

//���水ť
static lv_obj_t * save_btn =NULL;

// �϶���ʼֵ����ʼ����λ��
static int drag_start_value;
static lv_coord_t drag_start_y;
// ������ر���
static int slider_min = 0;
static int slider_max = 15;
static int slider_h = 200;
static int32_t upper_limit_value = 10;
static int32_t lower_limit_value= 6;



//����ͼƬԴ
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


//�ⲿ����
void my_Gui(void){
        // ������Ļ�Ĺ���
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
        First_Load();
}




//���ð�ť������
static void Toggle_UI(lv_event_t* e){
    lv_obj_t* target = lv_event_get_target(e);
    if(target  == Setting_Btn ){
        //ɾ��Container�е�����
        lv_obj_del(Container);
        Container = NULL;
        Person_Btn = NULL;

        //����ҳ�治��ʾ���ð�ť
        lv_obj_del(Setting_Btn);
        Setting_Btn = NULL;

        //���³�ʼ������
        Container_Init();
        Display_HomeBtn();
        //�������ý���
        Load_Setting();

    }else if(target == Home_Btn){
        //ɾ��Container�е�����
        lv_obj_del(Container);
        Container = NULL;
        Adjust_Btn =NULL;
        Adjust_Slider =NULL;
        //���³�ʼ������
        Container_Init();
        Display_PersonBtn();
        //��ҳ����ʾ��ҳ��ť
        lv_obj_del(Home_Btn);
        if (save_btn != NULL)
        {
            /* code */
            lv_obj_del(save_btn);
            save_btn = NULL;
        }
        Home_Btn = NULL;
        //��ҳ��ʾ���ð�ť
        Display_SetBtn();
    }else if(target == Adjust_Btn){
        //ɾ��Container�е�����
        lv_obj_del(Container);
        Container = NULL;
        Adjust_Btn = NULL;
        //���³�ʼ������
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






//------------------------------------���������غ���--------------------------------------------------------
static void First_Load(void){
    //��ʼ��ͷ��
    Header_Init();
    Display_SetBtn();

    //��ʼ������
    Container_Init();
    Display_PersonBtn();

    //��ʼ���ײ�
    Footer_Init();
}

void Header_Init(void){
    //������������
    Header = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(Header);  // ���Ĭ����ʽ
    lv_obj_set_size(Header,240,35);
    lv_obj_set_align(Header,LV_ALIGN_TOP_MID);
    // ������ʽ
    lv_obj_set_style_bg_color(Header, lv_color_hex(0x1E90FF), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(Header, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(Header, 0, LV_PART_MAIN);  // ȥ��Բ��
    lv_obj_set_style_border_width(Header, 0, LV_PART_MAIN);  // ȥ���߿�
    lv_obj_set_style_pad_all(Header, 5, LV_PART_MAIN);  // �����ڱ߾�
    // ��ֹ����
    lv_obj_clear_flag(Header, LV_OBJ_FLAG_SCROLLABLE);

}
//�ײ������ʼ��
void Footer_Init(void){
    Footer = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(Footer);  // ���Ĭ����ʽ
    lv_obj_set_size(Footer,240,50);
    lv_obj_set_align(Footer,LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(Footer,lv_color_hex(0x1E90FF),LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(Footer, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(Footer, 0, LV_PART_MAIN);  // ȥ��Բ��
    lv_obj_set_style_border_width(Footer, 0, LV_PART_MAIN);  // ȥ���߿�
    lv_obj_set_style_pad_all(Footer, 5, LV_PART_MAIN);  // �����ڱ߾�

    // ��ֹ����
    lv_obj_clear_flag(Footer, LV_OBJ_FLAG_SCROLLABLE);
}

//��������ʼ��
void Container_Init(void){

    //������ʼ��
    Container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Container,240,235);
    lv_obj_set_pos(Container,0,35);
    lv_obj_set_style_bg_color(Container,lv_color_hex(0xFFFFF0),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Container, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(Container, 0, LV_PART_MAIN);  // ȥ��Բ��
    lv_obj_set_style_border_width(Container, 0, LV_PART_MAIN);  // ȥ���߿�
    lv_obj_set_style_pad_all(Container, 5, LV_PART_MAIN);  // �����ڱ߾�
    // ��ֹ����
    lv_obj_clear_flag(Container, LV_OBJ_FLAG_SCROLLABLE);
}

//�������ý���
void Load_Setting(void){
    //���������ް�ť
    Adjust_Btn=lv_imgbtn_create(Container);
    lv_imgbtn_set_src(Adjust_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&adjust_img,NULL);
    lv_obj_set_size(Adjust_Btn,28,86);
    lv_obj_set_pos(Adjust_Btn,170,60);
    //����¼�
    lv_obj_add_event_cb(Adjust_Btn,Toggle_UI,LV_EVENT_PRESSED,NULL);
}
//���ص��������޽���
void Load_Adjust(void)
{
    //�������ڻ���
    Adjust_Slider = lv_slider_create(Container);
    lv_obj_set_size(Adjust_Slider, 20, slider_h);              // ���򻬿�
    lv_obj_set_align(Adjust_Slider, LV_ALIGN_CENTER);
    lv_slider_set_mode(Adjust_Slider, LV_SLIDER_MODE_RANGE); // ��Χģʽ�������������ֱ�
    lv_slider_set_range(Adjust_Slider, 0, 15);

    // ���ù����ָʾ��͸������ֹ�ص���ɫӰ��
    lv_obj_set_style_bg_opa(Adjust_Slider, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(Adjust_Slider, LV_OPA_TRANSP, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(Adjust_Slider, LV_OPA_TRANSP, LV_PART_KNOB);

    // ���Զ�����ƻص�������������ɫ���
    lv_obj_add_event_cb(Adjust_Slider, slider_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    //lv_obj_add_event_cb(Adjust_Slider, slider_limit_cb, LV_EVENT_VALUE_CHANGED, NULL);

    //��ֹ���黬��
    lv_obj_clear_flag(Adjust_Slider, LV_OBJ_FLAG_CLICKABLE);

    //����label
    Label_Top = lv_label_create(Container);
    lv_obj_set_pos(Label_Top,85,value_to_y(upper_limit_value,slider_min,slider_max,slider_h)-3);
    lv_label_set_text_fmt(Label_Top,"%d",upper_limit_value);

    Label_Bottom = lv_label_create(Container);
    lv_obj_set_pos(Label_Bottom,130,value_to_y(lower_limit_value,slider_min,slider_max,slider_h)-3);
    lv_label_set_text_fmt(Label_Bottom,"%d",lower_limit_value);

    lv_slider_set_value(Adjust_Slider, upper_limit_value, LV_ANIM_OFF);
    lv_slider_set_left_value(Adjust_Slider, lower_limit_value, LV_ANIM_OFF);
    // �������ͷ���������ֱ���
    img_left = lv_img_create(Container);
    lv_img_set_src(img_left, &left_arrow);
    lv_obj_add_flag(img_left, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img_left, arrow_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(img_left, arrow_event_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_set_pos(img_left, 240/2 - 90 - 10 - 5, value_to_y(upper_limit_value,slider_min,slider_max,slider_h)-3);

    // �����Ҽ�ͷ���������ֱ���
    img_right = lv_img_create(Container);
    lv_img_set_src(img_right, &right_arrow);
    lv_obj_add_flag(img_right, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img_right, arrow_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(img_right, arrow_event_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_set_pos(img_right, (240)/2 + 5, value_to_y(lower_limit_value,slider_min,slider_max,slider_h)-3);
}

//��ʾ���ð�ť
void Display_SetBtn(void){
    Setting_Btn = lv_imgbtn_create(Header);
    lv_imgbtn_set_src(Setting_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&set_img,NULL);
    lv_obj_set_size(Setting_Btn,30,30);
    lv_obj_set_pos(Setting_Btn,5,0);
    //����¼�
    lv_obj_add_event_cb(Setting_Btn,Toggle_UI,LV_EVENT_PRESSED,NULL);
}


//��ʾ���ﰴť
void Display_PersonBtn(void){
    Person_Btn = lv_imgbtn_create(Container);
    lv_imgbtn_set_src(Person_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&person_img,NULL);
    lv_obj_set_size(Person_Btn,100,130);
    lv_obj_set_pos(Person_Btn,50,40);
}
//��ʾHome��ť
void Display_HomeBtn(void){
    Home_Btn = lv_imgbtn_create(Footer);
    lv_imgbtn_set_src(Home_Btn,LV_IMGBTN_STATE_RELEASED,NULL,&home_img,NULL);
    lv_obj_set_size(Home_Btn,40,40);
    lv_obj_set_align(Home_Btn,LV_ALIGN_CENTER);

    //����¼�
    lv_obj_add_event_cb(Home_Btn,Toggle_UI,LV_EVENT_PRESSED,NULL);
}

void Display_SaveBtn(void){
    save_btn = lv_imgbtn_create(Footer);
    lv_imgbtn_set_src(save_btn,LV_IMGBTN_STATE_RELEASED,NULL,&save_img,NULL);
    lv_obj_set_size(save_btn,40,40);
    lv_obj_set_align(save_btn,LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_event_cb(save_btn, Toggle_UI, LV_EVENT_PRESSED, NULL);
}





//---------------------------������ش���-----------------------------------------
/* �Զ��廬�������ƣ�������ɫ */
 void slider_draw_event_cb(lv_event_t * e)
{

    lv_obj_t * slider = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

    if(dsc->part == LV_PART_MAIN) {
        int32_t min   = lv_slider_get_min_value(slider);
        int32_t max   = lv_slider_get_max_value(slider);
        //����
        int32_t left  = lv_slider_get_left_value(slider);
        //����
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

        // ��ֱλ��ӳ�䣬y��Խ��ֵԽС
        lv_coord_t py_left  = y2 - (lv_coord_t)((int64_t)(left  - min) * h / (max - min));
        lv_coord_t py_right = y2 - (lv_coord_t)((int64_t)(right - min) * h / (max - min));

        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        rect_dsc.bg_opa = LV_OPA_COVER;
        rect_dsc.border_opa = LV_OPA_TRANSP;

        // 1) �¶� ��ɫ
        if(py_left < y2) {
            rect_dsc.bg_color = lv_color_hex(0x32CD32);
            lv_area_t a = {x1, py_left + 1, x2, y2};
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &a);
        }
        // 2) �ж� ��ɫ
        if(py_right <= py_left) {
            rect_dsc.bg_color = lv_color_hex(0xFFA500);
            lv_area_t a = {x1, py_right, x2, py_left};
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &a);
        }
        // 3) �϶� ��ɫ
        if(py_right > y1) {
            rect_dsc.bg_color = lv_color_hex(0xFF0000);
            lv_area_t a = {x1, y1, x2, py_right - 1};
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &a);
        }

        // �ر�ϵͳĬ�Ϲ������
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


//��ͷ�¼�
// ӳ�亯����value -> y (knob����)
 lv_coord_t value_to_y(int value, int slider_min, int slider_max, lv_coord_t slider_h)
{
    int range = slider_max - slider_min;
    return (slider_max - value) * (slider_h - 1) / range;
}

// ��ͷ�¼��ص�
 void arrow_event_cb(lv_event_t * e)
{
    lv_obj_t * arrow = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    lv_coord_t slider_h = lv_obj_get_height(Adjust_Slider);

    if(code == LV_EVENT_PRESSED) {
        // ��¼��ʼ����λ��
        lv_point_t p;
        lv_indev_get_point(lv_indev_get_act(), &p);
        drag_start_y = p.y;

        // ��¼��ʼֵ
        if(arrow == img_right) { // ���޼�ͷ
            drag_start_value = lv_slider_get_left_value(Adjust_Slider);
        } else if(arrow == img_left) { // ���޼�ͷ
            drag_start_value = lv_slider_get_value(Adjust_Slider);
        }
    }
    else if(code == LV_EVENT_PRESSING) {
        lv_point_t p;
        lv_indev_get_point(lv_indev_get_act(), &p);

        // �����ƶ������ز�
        int delta_y = p.y - drag_start_y;

        // ���ز�ת����ֵ���������ֵ�������Ǽ�ֵ��
        int range = slider_max - slider_min;
        int delta_value = -(delta_y * range / (slider_h - 1));

        // ��ֵ = ��ʼֵ + ��ֵ
        int new_value = drag_start_value + delta_value;

        if(arrow == img_right) { // ���޼�ͷ
            int top_value = lv_slider_get_value(Adjust_Slider);

            // ���Ʒ�Χ
            if(new_value < slider_min + 1) new_value = slider_min + 1;
            if(new_value >= top_value) new_value = top_value - 1;

            // ���� slider �� label
            lv_slider_set_left_value(Adjust_Slider, new_value, LV_ANIM_OFF);
            lv_label_set_text_fmt(Label_Bottom, "%d", new_value);

            // ��ͷλ��
            lv_coord_t knob_center_y = value_to_y(new_value, slider_min, slider_max, slider_h);
            lv_obj_set_y(img_right, knob_center_y - 3);
            lv_obj_set_y(Label_Bottom, knob_center_y - lv_obj_get_height(Label_Bottom) / 2);
        }
        else if(arrow == img_left) { // ���޼�ͷ
            int bottom_value = lv_slider_get_left_value(Adjust_Slider);

            // ���Ʒ�Χ
            if(new_value > 14) new_value = 14;
            if(new_value <= bottom_value) new_value = bottom_value + 1;

            // ���� slider �� label
            lv_slider_set_value(Adjust_Slider, new_value, LV_ANIM_OFF);
            lv_label_set_text_fmt(Label_Top, "%d", new_value);

            // ��ͷλ��
            lv_coord_t knob_center_y = value_to_y(new_value, slider_min, slider_max, slider_h);
            lv_obj_set_y(img_left, knob_center_y - 3);
            lv_obj_set_y(Label_Top, knob_center_y - lv_obj_get_height(Label_Top) / 2);
        }
    }
}














