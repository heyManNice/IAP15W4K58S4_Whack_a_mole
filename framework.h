//使用if判断预定义，防止头文件因为include的
//复杂关系偶然出现执行定义函数的情况
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "STC15.h"

//定义这些类型方便使用
#define uint unsigned int
#define uchar unsigned char

extern unsigned long int Uptime_Seconds;
extern uchar Loop_Time;

//Loop_Time变量存储当前的时间周期
//用于定制操作的依据
//目前只用了低4位来储存4种情况，还有高四位可以后续拓展
//以下是Loop_Time可能的值
#define TIME_2MS  0x01   //二进制是0000 0001，代表当前2ms周期已到
#define TIME_10MS 0x02   //二进制是0000 0010，代表当前10ms周期已到
#define TIME_500MS 0x04   //二进制是0000 0100，代表当前500ms周期已到
#define TIME_1S    0x08   //二进制是0000 1000，代表当前1s周期已到

void TIME_1S_FUNCTION();
void TIME_500MS_FUNCTION();
void TIME_10MS_FUNCTION();
void TIME_2MS_FUNCTION();

//定义一个延时宏定义，不阻塞代码运行
//延时时间等于当前函数执行周期的倍数
//如果在一个函数内要使用这个延时宏定义
//首先按照符合c89标准要求在函数开始定义变量
//必须使用USE_TIMEOUT宏在函数开始处定义局部变量
//在需要延时处使用如下语句，延时时间以当前函数的调用周期而定
//SETTIMEOUT(延时倍数){延时执行的语句}
//如果当前函数每2秒执行一次，那么SETTIMEOUT(4)就是每8秒执行一次
//延时倍数最大值由time_out_count类型决定，目前是uint。延时倍数必须是整数
#define USE_TIMEOUT static uint time_out_count = 0;time_out_count++
#define SETTIMEOUT(num) if(time_out_count % num == 0)

#endif