#include "random.h"

//生成随机数字的函数
//输入参数是最小值和最大值
//random(最小值，最大值);
//返回uint类型数字
uint random(uint min,uint max) {
    uint value;
    srand(Uptime_Seconds);
    value = rand() % (max + 1 - min) + min;
    return value;
}
