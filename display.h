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
#define DISPLAY_OFF      0x00
#define DISPLAY_ON       0xFF

extern uchar font_table[];

extern uchar Display_Memory[];

void Refresh_Display_Hook();

#endif