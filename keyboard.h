#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "framework.h"

//矩阵键盘的键值码
#define KEY_1       0xEE
#define KEY_2       0xDE
#define KEY_3       0xBE
#define KEY_4       0x7E

#define KEY_5       0xED
#define KEY_6       0xDD
#define KEY_7       0xBD
#define KEY_8       0x7D

#define KEY_9       0xEB
#define KEY_10      0xDB
#define KEY_11      0xBB
#define KEY_12      0x7B

#define KEY_13      0xE7
#define KEY_14      0xD7
#define KEY_15      0xB7
#define KEY_16      0x77

#define KEY_NULL    0xFF

//按键使用示例：
//按下按键时执行一次代码
//KEY_DOWN(键值){
//    需要执行的代码;
//}
#define KEY_DOWN(value) for(;Key_Down_Value == value;Key_Down_Value = KEY_NULL)

//抬起按键时执行一次代码
//KEY_UP(键值){
//    需要执行的代码;
//}
#define KEY_UP(value) for(;Key_Up_Value == value;Key_Up_Value = KEY_NULL)

//非必要情况下不需要读取以下键值
//只需要按照上方宏定义的用法使用就好

extern uchar Key_Value;
extern uchar Key_Down_Value;
extern uchar Key_Up_Value;

void Key_Scan();
void Test_Key();
void Decode_Key_Event();
#endif