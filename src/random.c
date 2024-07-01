#include "random.h"

//生成随机数字的函数
//输入参数是最小值和最大值
//random(最小值，最大值);
//返回uint类型数字
uint random(uint min,uint max) {
    uint value;
    srand(Uptime_Seconds);
    if(max<200){
        //当数值过小时，随机数就看起来不太随机
        //这里通过增大数值范围来添加随机的效果
        max *=100;
        min *=100;
        value = rand() % (max + 1 - min) + min;
        return value/100;
    }
    value = rand() % (max + 1 - min) + min;
    return value;
}
