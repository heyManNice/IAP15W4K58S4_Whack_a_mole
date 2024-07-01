#ifndef DISPLAY_H
#define DISPLAY_H
#include "framework.h"

//第0个数码管显示数字示例(数值可动态变化)：
//Display_Memory[0] = NUMBER(1)
#define NUMBER(num) font_table[num]


//第0个数码管显示字母示例：
//Display_Memory[0] = LETTER_C
#define LETTER_A         0x77
#define LETTER_B         0x7c
#define LETTER_C         0x39
#define LETTER_D         0x5e
#define LETTER_E         0x79
#define LETTER_F         0x71
#define LETTER_G         0x7d
#define LETTER_T         0x07
#define LETTER_O         0x3F
#define LETTER_U         0x3E
#define LETTER_R         0x31
#define LETTER_N         0x37
#define DISPLAY_OFF      0x00
#define DISPLAY_ON       0xFF

extern uchar xdata font_table[];

extern uchar Display_Memory[];

void Refresh_Display_Hook();
void Display_Show(uchar d0,uchar d1,uchar d2,uchar d3,uchar d4,uchar d5,uchar d6,uchar d7);

#endif