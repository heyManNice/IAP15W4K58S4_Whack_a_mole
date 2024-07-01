#include "display.h"
#include "pin.h"

//定义数码管显示每一个字的字形码
uchar xdata font_table[]=
    {
    0x3f,0x06,0x5b,0x4f,// 0  1  2  3
    0x66,0x6d,0x7d,0x07,// 4  5  6  7
    0x7f,0x6f,0x77,0x7c,// 8  9  A  B
    0x39,0x5e,0x79,0x71 // C  D  E  F
    };


//定义数码管显示器内存，
//如果需要修改显示内容，只需要改此变量的内容
//示例，修改第0个数码管为数字2:
//Display_Memory[0]=NUMBER(2);
uchar Display_Memory[] = 
    {
	DISPLAY_OFF,DISPLAY_OFF,DISPLAY_OFF,DISPLAY_OFF, //数码管第0~3位初始内容
    DISPLAY_OFF,DISPLAY_OFF,DISPLAY_OFF,DISPLAY_OFF  //数码管第4~7位初始内容
    };



//刷新数码管内容函数
//该函数每2ms执行一次
//从显示器内存中获取当前需要显示的内容
//使用动态刷新的方法显示在数码管上
void Refresh_Display_Hook(){
    static uchar i=0;

    PORT_DISPLAY_SELECT = ~(0x01<<i);//切换当前工作的数码管
    PORT_DISPLAY_DATA=Display_Memory[i];//将显示内存数据依次发送到数码管数据线上
    if(++i>7)i=0;
}

//数码管显示八个内容
//参数分别是数码管从
//第0位到第7位的内容
//示例：
//Display_Show(LETTER_G,LETTER_A,LETTER_N,LETTER_E,DISPLAY_OFF,LETTER_R,LETTER_U,LETTER_N);
void Display_Show(uchar d0,uchar d1,uchar d2,uchar d3,uchar d4,uchar d5,uchar d6,uchar d7){
    Display_Memory[0] = d0;
    Display_Memory[1] = d1;
    Display_Memory[2] = d2;
    Display_Memory[3] = d3;
    Display_Memory[4] = d4;
    Display_Memory[5] = d5;
    Display_Memory[6] = d6;
    Display_Memory[7] = d7;
}