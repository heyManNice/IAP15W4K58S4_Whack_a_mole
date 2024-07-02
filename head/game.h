#ifndef GAME_H
#define GAME_H
#include "framework.h"
#include "keyboard.h"

extern unsigned long int xdata Game_Time_Level[];
extern uint xdata Game_Score_Level[];



//游戏菜单状态值
#define GAME_STATE_MENU_RUN             1
#define GAME_STATE_MENU_TOP             2
#define GAME_STATE_MENU_TL              3  //设置小鼠持续时间
#define GAME_STATE_MENU_SL              4  //设置晋级分数
//记录着菜单里最大的值
#define MENU_MAX_NUMBER                 4

//游戏非菜单状态值
#define GAME_STATE_PLAYING              41
#define GAME_STATE_PAUSE                42
#define GAME_STATE_OVER                 43
#define GAME_STATE_SHOW_TOTAL_SCORE     44
#define GAME_STATE_SHOW_TOTAL_TIME      45
#define GAME_STATE_NEXT_LEVEL           46


//用于在给某些固定的数组求长度
//规定该数组的第0位手动输入数组长度
//有效内容位从1开始
#define LENGTH                          0

void Switch_Page_Key_Event();
void Refresh_Game_Hook();
void Game_Menu_Run_Hook();
void Game_Menu_Top_Hook();
void Game_Menu_TL_Hook();
void Game_Menu_SL_Hook();
void Game_Timer_Hook();
void Game_Playing_Hook();
void Show_Mole(uchar location);
void Hide_Mole();
void Game_Over_Hook();
void Show_Total_Score_Hook();
void Next_Level_Hook();
void Show_Total_Time_Hook();

//当处于菜单页面的按键映射关系
#define KEY_ADD                         KEY_3
#define KEY_MINUS                       KEY_11
#define KEY_PREV_BIT                    KEY_6
#define KEY_NEXT_BIT                    KEY_8
#define KEY_OK                          KEY_7
#define KEY_PREV_PAGE                   KEY_10
#define KEY_NEXT_PAGE                   KEY_12

//当处于游戏或者暂停中的按键映射关系
#define KEY_PAUSE                       KEY_16
#define KEY_CONTINUE                    KEY_16
#define KEY_EXIT                        KEY_15
#define KEY_LEVEL_SCORE                 KEY_13
#define KEY_TOTAL_SCORE                 KEY_9
#define KEY_TOTAL_TIME                  KEY_10


//游戏每一个等级倒计时的时间
#define GAME_TIMER_VALUE                70

//小鼠消失状态
#define MOLE_STATE_DISAPPEAR            1
//小鼠准备好要出现的状态
#define MOLE_STATE_READY                2
//小鼠出现了！的状态
#define MOLE_STATE_APPEAR               3

#endif
