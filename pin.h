#ifndef PIN_H
#define PIN_H
//定义常用引脚名称

//蜂鸣器
//本次程序操作PWM4输出信号到P4_4引脚驱动无源蜂鸣器
//不直接操作io口，具体声明请看buzzer.c中的Buzzer_Init()
#define PIN_BUZZER           P4_4 //蜂鸣器

#define PORT_DISPLAY_DATA    P0   //数码管数据线端口
#define PORT_DISPLAY_SELECT  P1   //数码管位选线端口
#define PORT_KEYBOARD        P2   //矩阵键盘端口

#endif