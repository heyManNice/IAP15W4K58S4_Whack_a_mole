#include "buzzer.h"


//data：固定指前面0x00-0x7F的128个RAM，可以用acc直接读写，速度最快，生成的代码也最小。
//idata：固定指前面0x00-0xFF的256个RAM，其中前128和data的128完全相同，只是访问的方式不同。
//xdata：外部扩展RAM。
//code：ROM。
//===============================
//这个变量是不会在运行中改变的，为了节约内存
//所以把这个数组变量直接定义在code(ROM)内
//音符周期(us) = 1khz周期*1000/音符频率
uint code Tone_Freq[] = {
    //数组0~11位：中音1、1#、2、2#、3、4、4#、5、5#、6、6#、7
    21145,19962,18840,17780,16781,15844,14945,14106,13308,12567,11866,11193,
    //数组12~23：低音1、1#、2、2#、3、4、4#、5、5#、6、6#、7
    42210,39924,37616,35559,33512,31688,29889,28212,26648,25134,23732,22387,
    //数组24~35：高音1、1#、2、2#、3、4、4#、5、5#、6、6#、7
    10573,9972,9412,8883,8391,7916,7472,7053,6658,6284,5930,5597,
    //数组36~40：音符频率和其他类型音频频率的分界线
    0,0,0,0,0,
    //数组41~42：TONE_1KHZ,TONE_ALERT
    11059,65534
};

uchar code Muisc_Gameover[] = {
    DO_,16,MUTE,30,SO,13,MUTE,30,MI,30,
    LA,20,SI,20,LA,20,
    SO,30,LA,30,SO,30,
    MI,10,RE,13,MI,63,
    FINISH
};

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
    PWMC = Tone_Freq[TONE_1KHZ];
    PWM4T1 = 0;
    PWM4T2 = Tone_Freq[TONE_1KHZ]/2;
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
//参数是音符在Tone_Freq[]数组中的顺序位置
//示例：Buzzer_Tone(DO);
//其中DO是顺序位置0
void Buzzer_Tone(uchar tone){
    P_SW2 |= 0x80;
    PWMC = Tone_Freq[tone];
    PWM4T1 = 0;
    PWM4T2 = Tone_Freq[tone]/2;
    if(tone == MUTE){
        PWMCR = 0x00;
    }else{
        PWMCR = 0x84;
    }
    P_SW2 &= ~0x80;
}

//设置为1，蜂鸣器响起一次警告
//结束自动归零
uchar Buzzer_Is_Alert = 0;
//设置为1，蜂鸣器响起一次得分提示音
//结束自动归零
uchar Buzzer_Is_Bingo = 0;

//刷新蜂鸣器状态的函数
//该函数每10ms执行一次
void Refresh_Buzzer_Hook(){
    if(Buzzer_Is_Alert)Buzzer_Alert();
    if(Buzzer_Is_Bingo)Buzzer_Bingo();
    if(!Buzzer_Is_Alert && !Buzzer_Is_Bingo && Player_State == PLAYER_PALY)Buzzer_Player_Hook();
}

//如果Buzzer_Is_Alert=1就会执行此函数
//此函数执行的时间间隔由Refresh_Buzzer_Hook决定
void Buzzer_Alert(){
    static uchar i =0;
    if(i==0)Buzzer_Tone(TONE_ALERT);
    if(i==10)Buzzer_noBeep();
    if(i==20)Buzzer_Tone(TONE_ALERT);
    if(i==30){
        Buzzer_noBeep();
        i=0;
        Buzzer_Is_Alert=0;
        return;
    }
    i++;
}

//如果Buzzer_Is_Bingo=1就会执行此函数
//此函数执行的时间间隔由Refresh_Buzzer_Hook决定
void Buzzer_Bingo(){
    static uchar i =0;
    if(i==0)Buzzer_Tone(SI);
    if(i==6)Buzzer_Tone(MI_);
    if(i==36){
        Buzzer_noBeep();
        i=0;
        Buzzer_Is_Bingo=0;
        return;
    }
    i++;
}

uchar *Player_Note_List=0;
uchar Player_State = PLAYER_STOP;
long int Player_Ps = 0;

//播放器的刷新函数
//在播放状态每10ms执行一次
void Buzzer_Player_Hook(){
    static uchar count = 0;
    uchar tone = Player_Note_List[Player_Ps];
    //如果当前的音调是播放完成标志，那么停止播放播放
    if(tone==FINISH){
        Buzzer_Player_Stop();
        return;
    }
    //如果当前的播放计数是0，那么该音符第一次进入播放器循环
    //播放该音符
    if(count==0){
        Buzzer_Tone(tone);
    }
    //如果当前计数次数大于音符列表限制的循环次数
    //那么结束当前音符，将播放音符位置移动到下一个音符 
    if(++count>Player_Note_List[Player_Ps+1]){
        Player_Ps+=2;
        count=0;
        return;
    }
}

//播放器开始播放音乐
//参数是音乐音符数组指针
//示例：Buzzer_Player_Play(&Muisc_Gameover);
void Buzzer_Player_Play(uchar *note_list){
    Player_Note_List = note_list;
    Player_Ps = 0;
    Player_State = PLAYER_PALY;
}

//停止音乐播放器的播放
void Buzzer_Player_Stop(){
    Player_State=PLAYER_STOP;
    Player_Ps=0;
    Buzzer_noBeep();
}