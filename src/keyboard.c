#include "keyboard.h"
#include "pin.h"
#include "display.h"
#include "buzzer.h"
#include "random.h"

//当前的实时键值
uchar Key_Value = KEY_NULL;

//当前已按下的键值
uchar Key_Down_Value = KEY_NULL;

//当前已抬起的键值
uchar Key_Up_Value = KEY_NULL;

//扫描矩阵键盘按下的键
//该函数每10ms执行一次
//每执行两次求出键值
void Key_Scan(){
    static uchar State = 0;
    static uchar Value;
    uchar temp;
    if(State){
        Value = 0x00;
        Value |= PORT_KEYBOARD;
        State = 0;
        PORT_KEYBOARD = 0xF0;
    }else{
        Value |= PORT_KEYBOARD;
        //判断当Value是一个有效的键值时
        //才将它写入Key_Value变量中
        //有效的值包括
        //1、按下时包含两个0的八位二进制数
        //2、没有按下按键 KEY_NULL
        temp = ~Value;
        temp &= temp-1;
        //有时候因为按下按键的时机问题获得无效的键值
        //这时候获得的键值是有可能是包含1个0的八位二进制数
        //temp给键值取反会得到包含1个1的八位二进制数
        //使用与运算去掉一个1，如果此时结果是0
        //证明该键值是无效的，应舍去
        //否则是有效的，为Key_Value赋值该键值
        if(temp!=0 || Value==KEY_NULL)Key_Value = Value;

        //解析按键事件的函数
        //只能在这个if分支里面生效
        //所以就放在了这个分支里
        //放在分支外工作正常，但是会多浪费一次算力
        Decode_Key_Event();
        State = 1;
        PORT_KEYBOARD = 0x0F;
    }
}

//解析按键事件
void Decode_Key_Event(){
    static uchar Prev_Value=KEY_NULL;
    //如果上次的键值不等于这次的键值
    //这次键值为空的话，那么就是抬起了按键
    //否则是按下了按键
    if(Prev_Value!=Key_Value){
        if(Key_Value==KEY_NULL){
            Key_Up_Value = Prev_Value;
        }else{
            Key_Down_Value = Key_Value;
        }
        Prev_Value = Key_Value;
    }
}

//测试按键的函数
//同时也是按键使用的示例代码
void Test_Key(){
    static uchar i = 1;
    static uchar j = 1;
    if(i>15)i=1;
    if(j>15)j=1;

    KEY_UP(KEY_1){
        Display_Memory[0]=NUMBER(i++);
    }
    KEY_DOWN(KEY_1){
        Display_Memory[3]=NUMBER(j++);
    }

    KEY_DOWN(KEY_5){
        //生成一个三位数随机数
        uint random_value = random(0,999);
        Display_Memory[7]=NUMBER(random_value%10);//个位
        random_value /= 10;
        Display_Memory[6]=NUMBER(random_value%10);//十位
        random_value /= 10;
        Display_Memory[5]=NUMBER(random_value%10);//百位
    }

    KEY_DOWN(KEY_4){
        Buzzer_Beep();
    }
    KEY_UP(KEY_4){
        Buzzer_noBeep();
    }

    KEY_DOWN(KEY_13){
        Buzzer_Tone(DO);
    }
    KEY_UP(KEY_13){
        Buzzer_noBeep();
    }

    KEY_DOWN(KEY_14){
        Buzzer_Tone(RE);
    }
    KEY_UP(KEY_14){
        Buzzer_noBeep();
    }

    KEY_DOWN(KEY_15){
        Buzzer_Tone(MI);
    }
    KEY_UP(KEY_15){
        Buzzer_noBeep();
    }

    KEY_DOWN(KEY_16){
        Buzzer_Tone(FA);
    }
    KEY_UP(KEY_16){
        Buzzer_noBeep();
    }

    KEY_DOWN(KEY_8){
        Buzzer_Tone(_RE);
    }
    KEY_UP(KEY_8){
        Buzzer_noBeep();
    }

    KEY_DOWN(KEY_12){
        Buzzer_Is_Alert=1;
    }
    KEY_DOWN(KEY_10){
        Buzzer_Is_Bingo=1;
    }

    KEY_DOWN(KEY_9){
        Buzzer_Player_Play(&Muisc_Gameover);
    }
    KEY_DOWN(KEY_11){
        Buzzer_Player_Stop();
    }
}