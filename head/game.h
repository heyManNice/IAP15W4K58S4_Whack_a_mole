#ifndef GAME_H
#define GAME_H
#include "framework.h"
#include "keyboard.h"

extern uint xdata Game_Time_Level[];
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
#define GAME_STATE_SHOW_TOTAL_TIME      44

void Refresh_Game_Hook();
void Game_Menu_Run_Hook();
void Game_Menu_Top_Hook();
void Game_Menu_TL_Hook();
void Game_Menu_SL_Hook();

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

#endif
