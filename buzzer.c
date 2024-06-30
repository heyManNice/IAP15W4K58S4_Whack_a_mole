#include "buzzer.h"

//初始化蜂鸣器引脚和相关PWM配置
//默认配置1khz频率，50占空比
void Buzzer_Init(){
    P4M1 = 0x00;P4M0 = 0x00;

    P_SW2 |= 0x80;                  //打开访问PWM特殊功能寄存器的权限
    PWMC = 11059;                   //设置PWM周期为1ms
    PWM4T1 = 0;                     
    PWM4T2 = 5529;                  //设置PWM4第2次反转的PWM计数，占空比50
    PWM4CR = 0x08;                  //选择PWM4输出到P4.4
    PWMCR = 0x00;                   //设置0x84可打开PWM4信号输出
    P_SW2 &= ~0x80;
}

//蜂鸣器响起嘟嘟声
void Buzzer_Beep(){
    P_SW2 |= 0x80;
    PWMC = TONE_1KHZ;
    PWM4T1 = 0;
    PWM4T2 = TONE_1KHZ/2;
    PWMCR = 0x84;
    P_SW2 &= ~0x80;
}

//蜂鸣器静音
void Buzzer_noBeep(){
    P_SW2 |= 0x80;
    PWMCR = 0x00;
    P_SW2 &= ~0x80;
}

//蜂鸣器播放含有音高的声音
//参数是音符周期(us)
//示例：Buzzer_Tone(DO);
void Buzzer_Tone(long int tone){
    P_SW2 |= 0x80;
    PWMC = tone;
    PWM4T1 = 0;
    PWM4T2 = tone/2;
    PWMCR = 0x84;
    P_SW2 &= ~0x80;
}