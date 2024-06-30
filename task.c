#include "framework.h"
#include "display.h"
#include "keyboard.h"

//===================1S=====================
//每1秒执行一次的功能写在这个函数里
void TIME_1S_FUNCTION(){
	Loop_Time&=~TIME_1S;//清除这个标记，说明我们已经执行过了
}


//===================500MS=====================
//每500毫秒执行一次的功能写在这个函数里
void TIME_500MS_FUNCTION(){
	Loop_Time&=~TIME_500MS;//清除这个标记，说明我们已经执行过了
}


//===================3MS=====================
//每10毫秒执行一次的功能写在这个函数里
void TIME_10MS_FUNCTION(){
	Loop_Time&=~TIME_10MS;//清除这个标记，说明我们已经执行过了
    Key_Scan();
    Test_Key();
}


//===================3MS=====================
//每2毫秒执行一次的功能写在这个函数里
void TIME_2MS_FUNCTION(){
	Loop_Time&=~TIME_2MS;//清除这个标记，说明我们已经执行过了
    Refresh_Display_Hook();
}