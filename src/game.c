#include "game.h"
#include "display.h"
#include "random.h"
#include "buzzer.h"


//不同等级下的小鼠亮灯持续时间(ms)
//等级值为1~9
unsigned long int xdata Game_Time_Level[10] = {
    0,2000,1700,1400,1100,
    900,600,400,300,200
};

//把键值按顺序放在一个数组中
//当生成小鼠时候才好方便
//把小鼠的位置与键盘对应起来
uchar Key_Value_List[] = {
    KEY_NULL,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,
    KEY_7,KEY_8,KEY_9,KEY_10,KEY_11,KEY_12
};

//不同等级下的晋级分数线
//等级值为1~9
uint xdata Game_Score_Level[10] = {
    0,20,30,40,50,
    60,70,80,80,9999
};

long int xdata Game_Total_Score     =   0;
long int xdata Game_Total_Time      =   0;
long int xdata Best_Total_Score     =   0;
long int xdata Best_Total_Time      =   0;

//该游戏目前的等级
uchar Game_Level = 1;
//该游戏目前等级的分数
uint Game_Socre = 0;
//该游戏目前等级的倒计时
uint Game_Timer = GAME_TIMER_VALUE;

//分数从0数到总分的动画数值
 uint Count_Score = 0;


//记录游戏状态的变量
//该游戏分为多个状态
//在不同的状态内执行不同的代码
//所有状态可能的值为GAME_STATE_开头的值
//详细内容请查看game.h
uchar Game_State = 1;

void Refresh_Game_Hook(){
    switch (Game_State)
    {
    case GAME_STATE_MENU_RUN:
        Game_Menu_Run_Hook();
        break;
    case GAME_STATE_MENU_TOP:
        Game_Menu_Top_Hook();
        break;
    case GAME_STATE_MENU_TL:
        Game_Menu_TL_Hook();
        break;
    case GAME_STATE_MENU_SL:
        Game_Menu_SL_Hook();
        break;
    case GAME_STATE_PLAYING:
        Game_Playing_Hook();
        break;

    case GAME_STATE_OVER:
        Game_Over_Hook();
        break;
    case GAME_STATE_SHOW_TOTAL_SCORE:
        Show_Total_Score_Hook();
        break;
    case GAME_STATE_NEXT_LEVEL:
        Next_Level_Hook();
        break;
    case GAME_STATE_SHOW_TOTAL_TIME:
        Show_Total_Time_Hook();
        break;
    default:

        break;
    }
}

//一个求次方的函数
//因为当前项目的简单要求
//该函数的返回值只有正整数，上限为65535
//num：底数
//power：指数
uint Pow(uchar num,uchar power){
    uint value = num;
    if(power==0)return 1;
    power -= 1;
    while (power--)
    {
        value *= num;
    }
    return value;
}

//菜单 切换页面的按键事件
//这是一个公共的函数
//提供给所有的菜单Hook函数使用
void Switch_Page_Key_Event(){
    KEY_DOWN(KEY_NEXT_PAGE){
        if(++Game_State>MENU_MAX_NUMBER)Game_State = 1;
    }
    KEY_DOWN(KEY_PREV_PAGE){
        if(--Game_State<1)Game_State = MENU_MAX_NUMBER;
    }
}

//菜单 开始游戏界面的钩子函数
void Game_Menu_Run_Hook(){
    Switch_Page_Key_Event();
    Display_Show(LETTER_G,LETTER_A,LETTER_N,LETTER_E,DISPLAY_OFF,LETTER_R,LETTER_U,LETTER_N);
    KEY_DOWN(KEY_OK){
        Game_Level = 1;
        Game_Total_Score = 0;
        Game_Total_Time = 0;
        //游戏跳到显示下一等级
        Game_State = GAME_STATE_NEXT_LEVEL;
    }
}
//菜单 显示最好成绩的钩子函数
void Game_Menu_Top_Hook(){
    Switch_Page_Key_Event();

    Display_Memory[0] = LETTER_T;
    Display_Memory[1] = LETTER_O;
    Display_Memory[2] = LETTER_P;
    Display_Memory[3] = DISPLAY_OFF;
    Display_Show_Number(Best_Total_Score,7,4);
}
//菜单 设置不同等级的地鼠显示持续时间钩子函数
void Game_Menu_TL_Hook(){
    static uchar caret = 1;
    static uchar level = 1;
    static uchar Is_Hide_Caret = 0;
    //Variable_Index数组用于储存当前界面可以增减的
    //数字所在的数码管位子
    //该数组的第0位应该手动储存该储存有效位的内容个数
    //有效位内容从第1位开始计算
    //如果需要获取该数组的有效内推个数
    //应写Variable_Index[0]
    //同时也可以写Variable_Index[LENGTH]
    uchar code Variable_Index[]={4,2,4,5,6};
    static count = 0;
    //每500ms显示或者隐藏光标
    if(count==0)Is_Hide_Caret=0;
    if(count==50)Is_Hide_Caret=1;
    if(++count == 100) count=0;
    Switch_Page_Key_Event();
    Display_Memory[0] = LETTER_T;
    Display_Memory[1] = LETTER_L;
    Display_Memory[2] = NUMBER(level);
    Display_Memory[3] = DISPLAY_OFF;
    Display_Show_Number(Game_Time_Level[level],7,4);
    if(Is_Hide_Caret)Display_Memory[Variable_Index[caret]] = DISPLAY_OFF;
    KEY_DOWN(KEY_ADD){
        if(caret==1){
            if(++level>9) level=1;
        }else{
            Game_Time_Level[level] += Pow(10,7-Variable_Index[caret]);
        }
        count=0;
    }
    KEY_DOWN(KEY_MINUS){
        if(caret==1){
            if(--level<1) level=9;
        }else{
            Game_Time_Level[level] -= Pow(10,7-Variable_Index[caret]);
        }
        count=0;
    }
    KEY_DOWN(KEY_PREV_BIT){
        if(--caret<1)caret = Variable_Index[LENGTH];
        count=50;
    }
    KEY_DOWN(KEY_NEXT_BIT){
        if(++caret>Variable_Index[LENGTH])caret = 1;
        count=50;
    }
}
//菜单 设置不同等级的晋级分数条件钩子函数
void Game_Menu_SL_Hook(){
    static uchar caret = 1;
    static uchar level = 1;
    static uchar Is_Hide_Caret = 0;
    uchar code Variable_Index[]={5,2,4,5,6,7};
    static count = 0;
    if(count==0)Is_Hide_Caret=0;
    if(count==50)Is_Hide_Caret=1;
    if(++count == 100) count=0;
    Switch_Page_Key_Event();
    Display_Memory[0] = LETTER_S;
    Display_Memory[1] = LETTER_L;
    Display_Memory[2] = NUMBER(level);
    Display_Memory[3] = DISPLAY_OFF;
    Display_Show_Number(Game_Score_Level[level],7,4);
    if(Is_Hide_Caret)Display_Memory[Variable_Index[caret]] = DISPLAY_OFF;
    KEY_DOWN(KEY_ADD){
        if(caret==1){
            if(++level>9) level=1;
        }else{
            Game_Score_Level[level] += Pow(10,7-Variable_Index[caret]);
        }
        count=0;
    }
    KEY_DOWN(KEY_MINUS){
        if(caret==1){
            if(--level<1) level=9;
        }else{
            Game_Score_Level[level] -= Pow(10,7-Variable_Index[caret]);
        }
        count=0;
    }
    KEY_DOWN(KEY_PREV_BIT){
        if(--caret<1)caret = Variable_Index[LENGTH];
        count=50;
    }
    KEY_DOWN(KEY_NEXT_BIT){
        if(++caret>Variable_Index[LENGTH])caret = 1;
        count=50;
    }
}

void Game_Over_Hook(){
    static uint count = 0;
    Display_Show(LETTER_G,LETTER_A,LETTER_N,LETTER_E,LETTER_O,LETTER_U,LETTER_E,LETTER_R);
    if(++count == 550){
        count = 0;
        Game_State = GAME_STATE_SHOW_TOTAL_SCORE;
        //清除在这5秒内按键的记录
        //防止对后面代码逻辑的影响
        Key_Down_Value = KEY_NULL;
    }
}

void Game_Playing_Hook(){
    static uchar count = 0;
    static uchar Mole_State = MOLE_STATE_DISAPPEAR;
    static uchar random_location = 0;
    static uchar random_time_before_appear = 0;//小鼠出现前的随机时间,单位10ms

    //显示当前等级得分
    Display_Show_Number(Game_Socre,1,2);
    Display_Memory[1] |= 0x80;
    //显示当前倒计时
    Display_Show_Number(Game_Timer,3,2);
    switch (Mole_State)
    {
    case MOLE_STATE_DISAPPEAR:
        random_time_before_appear = random(30,70);
        random_location = random(1,12);
        Mole_State = MOLE_STATE_READY;
        count = 0;
        break;
    case MOLE_STATE_READY:
        if(++count!=random_time_before_appear)break;
        Show_Mole(random_location);
        count = 0;
        Mole_State = MOLE_STATE_APPEAR;
        break;
    case MOLE_STATE_APPEAR:
        if(++count!=Game_Time_Level[Game_Level]/10)break;
        Hide_Mole();
        count = 0;
        Mole_State = MOLE_STATE_DISAPPEAR;
        break;
    default:
        break;
    }
    ANY_KEY_DOWN{
        if(Key_Value == Key_Value_List[random_location]){
            Game_Socre+=1;
            Game_Total_Score+=1;
            Buzzer_Is_Bingo = 1;
            Hide_Mole();
            count = 0;
            Mole_State = MOLE_STATE_DISAPPEAR;
            if(Game_Socre >= Game_Score_Level[Game_Level] && Game_Level!=9){
                //升级啦！
                Game_Level += 1;
                Game_State = GAME_STATE_NEXT_LEVEL;
            }
            //如果游戏等级是9，而且分是9999，直接结束游戏
            if(Game_Level == 9 && Game_Socre == 9999){
                Game_Timer = 1;
            }
        }else{
            Buzzer_Is_Alert = 1;
        }
    }
}

//刷新游戏计时器函数
void Game_Timer_Hook(){
    if(Game_State == GAME_STATE_PLAYING){
        Game_Timer--;
        Game_Total_Time++;
        if(Game_Timer==0){
            Game_State = GAME_STATE_OVER;
            Buzzer_Player_Play(&Muisc_Gameover);
            if(Best_Total_Score < Game_Total_Score){
                Best_Total_Score = Game_Total_Score;
            }
            //清空计数动画数值
            Count_Score = 0;
        }
    }
}

void Next_Level_Hook(){
    static uchar count = 0;
    Display_Show(LETTER_L,LETTER_E,LETTER_U,LETTER_E,LETTER_L,DISPLAY_OFF,DISPLAY_OFF,DISPLAY_OFF);
    Display_Memory[7] = NUMBER(Game_Level);
    if(++count == 200){
        Game_Socre = 0;
        Game_Timer = GAME_TIMER_VALUE;
        Game_State = GAME_STATE_PLAYING;
        Display_Memory[4] = DISPLAY_OFF;
        Display_Memory[5] = DISPLAY_OFF;
        Display_Memory[6] = DISPLAY_OFF;
        Display_Memory[7] = DISPLAY_OFF;
        count = 0;
    }
}

//显示小鼠
//参数
//location：小鼠的位置，范围为1到12
void Show_Mole(uchar location){
    uchar Dispaly_Number = 7;
    uchar row;
    uchar col;
    uchar row_dispaly_data[] = {0x01,0x40,0x08};
    //转换为0到11更方便求行列
    location -= 1;
    //行： 0到2
    row = location/4;
    //列： 0到3
    col = location%4;

    while (Dispaly_Number>3)
    {
        if(Dispaly_Number==col+4){
            Display_Memory[Dispaly_Number] =row_dispaly_data[row];
        }else{
            Display_Memory[Dispaly_Number] = DISPLAY_OFF;
        }
        Dispaly_Number--;
    }
    
}

//隐藏小鼠
void Hide_Mole(){
    Display_Memory[4] = DISPLAY_OFF;
    Display_Memory[5] = DISPLAY_OFF;
    Display_Memory[6] = DISPLAY_OFF;
    Display_Memory[7] = DISPLAY_OFF;
}
//显示当前游戏的总得分
void Show_Total_Score_Hook(){
    //计时用的
    static uint count = 0;

    Display_Memory[0]=LETTER_P;
    Display_Memory[1]=DISPLAY_OFF;
    Display_Show_Number(Count_Score,7,6);

    if(Count_Score==Game_Total_Score){
        ANY_KEY_DOWN{
            Game_State = GAME_STATE_SHOW_TOTAL_TIME;
        }
        Buzzer_noBeep();
        return;
    }

    if(count==0){
        Buzzer_Beep();
        Count_Score++;
    }
    if(count==2){
        Buzzer_noBeep();
    }
    if(++count>3)count = 0;

}

void Show_Total_Time_Hook(){
    Display_Memory[0]=LETTER_T;
    Display_Memory[1]=DISPLAY_OFF;
    Display_Show_Number(Game_Total_Time,7,6);
    ANY_KEY_DOWN{
        Game_State = GAME_STATE_MENU_RUN;
    }
}