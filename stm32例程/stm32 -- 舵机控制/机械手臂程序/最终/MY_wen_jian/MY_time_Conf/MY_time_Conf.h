#ifndef __MY_TIME_CONF_H
#define __MY_TIME_CONF_H

#include "stm32f10x.h"


void Timer2_Init(u16 arr,u16 psc);  //定时器2初始化函数
void Timer3_Init(u16 arr,u16 psc);  //定时器3初始化函数
void Timer7_Init(u16 arr,u16 psc);  //定时器7初始化函数


#endif

