#include "game.h"
#include "display.h"

//不同等级下的小鼠亮灯持续时间
//等级值为0~9
//单位 10ms
uint xdata Game_Time_Level[] = {
    200,170,140,110,90,
    60,40,30,20,10
};

//不同等级下的晋级分数线
//等级值为0~9
uint xdata Game_Score_Level[] = {
    20,30,80,80,80,
    80,80,80,80,80
};

long int Game_Total_Score = 0;
long int Game_Total_Time = 0;


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
    
    default:
        break;
    }
}

//菜单 开始游戏界面的钩子函数
void Game_Menu_Run_Hook(){
    //Display_Show(LETTER_G,LETTER_A,LETTER_N,LETTER_E,DISPLAY_OFF,LETTER_R,LETTER_U,LETTER_N);
}
//菜单 最高分排行榜的钩子函数
void Game_Menu_Top_Hook(){

}
//菜单 设置不同等级的地鼠显示持续时间钩子函数
void Game_Menu_TL_Hook(){

}
//菜单 设置不同等级的晋级分数条件钩子函数
void Game_Menu_SL_Hook(){

}