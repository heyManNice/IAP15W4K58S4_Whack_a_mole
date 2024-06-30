#include "framework.h"
#include "buzzer.h"

//定义系统运行时间变量
//系统每一次启动从0开始计数
//每秒增加一个数值
//使用uint类型只有2字节，只能保存18小时的秒数大小
//而ulint类型有4字节，可以保存136年的秒数大小
//当前把储存秒数改为储存毫秒数，以上计算的时间都除以1000
//储存毫秒数用于给随机函数提供种子值
//使用毫秒提供随机数种子能让随机数看起来更随机
unsigned long int Uptime_Seconds = 0;


//如果要给Loop_Time登记0000 0001，2ms周期
//只需要Loop_Time与TIME_2MS按位或赋值
//需要判断当时2ms周期是否已到
//只需要Loop_Time与TIME_2MS按位与，如果结果不为0那么说明条件符合
uchar Loop_Time = 0x00;

//初始化系统运行定时器，每毫秒执行一次中断函数
void System_Timer_0_Init() {
    AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xCD;				//设置定时初始值
	TH0 = 0xD4;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
    EA = 1;                 //打开使能总中断
}

//系统定时器0执行的中断函数
//每隔一秒钟就给Uptime_Seconds加1
//用来表示系统运行的秒数
//后面增加了在不同的时间周期内
//给Loop_Time赋值标记当前周期的功能
void System_Timer_0() interrupt 1 {
    static uint i=0;
    i++;
	Uptime_Seconds++;
    i%2	  || (Loop_Time|=TIME_2MS);
    i%10  || (Loop_Time|=TIME_10MS);
    i%500 || (Loop_Time|=TIME_500MS);

    if(i==1000){
        i = 0;
        Loop_Time|=TIME_1S;
    }

}
//初始化端口的工作模式
void Port_Init(){
    P0M1 = 0x00;P0M0 = 0x00;
	P1M1 = 0x00;P1M0 = 0x00;
    P2M1 = 0x00;P2M0 = 0x00;
}


void main(){
    //开机只会执行一次的操作
    Port_Init();
    Buzzer_Init();
	System_Timer_0_Init();
    //开机后重复执行的操作
	while(1)
	{
		if(Loop_Time&TIME_1S)TIME_1S_FUNCTION();//如果1s周期已到，那就执行TIME_1S_FUNCTION函数；
		if(Loop_Time&TIME_500MS)TIME_500MS_FUNCTION();
		if(Loop_Time&TIME_10MS)TIME_10MS_FUNCTION();
		if(Loop_Time&TIME_2MS)TIME_2MS_FUNCTION();//如果2ms周期已到，那就执行TIME_2MS_FUNCTION函数；
	}
}
