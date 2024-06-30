#ifndef BUZZER_H
#define BUZZER_H
#include "framework.h"

//该频率定义是数字为
//该周期在Tone_Freq[]数组中的顺序位置
//TONE_1KHZ的周期在Tone_Freq[41]内，为11059
#define TONE_1KHZ   41  //11059us
#define TONE_ALERT  42  //169hz

void Buzzer_Init();
void Buzzer_Beep();
void Buzzer_noBeep();
void Buzzer_Tone(long int tone);
void Refresh_Buzzer_Hook();

//蜂鸣器警告声的开关
//当设置Buzzer_Is_Alert=1时警报打开
extern uchar Buzzer_Is_Alert;

extern uint code Tone_Freq[];

void Buzzer_Alert();


//宏定义，音调唱名转换为
//该音调的周期在Tone_Freq[]数组中的顺序位置
//这样用来编谱只需要uchar类型保存顺序，减少储存占用

//中音谱
#define DO      0  //1
#define DOS     1  //1#
#define RE      2  //2
#define RES     3  //2#
#define MI      4
#define FA      5
#define FAS     6
#define SO      7
#define SOS     8
#define LA      9
#define LAS     10
#define SI      11
//低音谱
#define _DO     12
#define _DOS    13
#define _RE     14
#define _RES    15
#define _MI     16
#define _FA     17
#define _FAS    18
#define _SO     19
#define _SOS    20
#define _LA     21
#define _LAS    22
#define _SI     23
//高音谱
#define DO_     24
#define DOS_    25
#define RE_     26
#define RES_    27
#define MI_     28
#define FA_     29
#define FAS_    30
#define SO_     31
#define SOS_    32
#define LA_     33
#define LAS_    34
#define SI_     35


#endif