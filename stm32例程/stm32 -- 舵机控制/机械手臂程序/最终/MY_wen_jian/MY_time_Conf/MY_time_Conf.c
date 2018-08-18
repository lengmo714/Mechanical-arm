#include "MY_time_Conf.h"


void Timer2_Init(u16 arr,u16 psc)  //定时器2初始化函数
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  //定义配置定时器的结构体变量
	
	//定时器2库函数初始化部分：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能TIM2时钟
	TIM_DeInit(TIM2);	            //将外设TIMx寄存器重设为缺省值 
	TIM_InternalClockConfig(TIM2);  //定时器时钟源，选择内部时钟
	/*基础设置*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;                     //设定计数器自动重装值  
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;    	            //预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  	                //设置时钟分割  采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM2->CR1  &= ~(1<<7);   //自动重装ARR里的值没有缓冲,随时更新数据随时有效。
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);					//初始化

	TIM_Cmd(TIM2, ENABLE);						 //使能定时器2，开始定时
	//TIM_Cmd(TIM2, DISABLE);						 //暂时不启动使能定时器2
	TIM_PrescalerConfig(TIM2, psc - 1, TIM_PSCReloadMode_Immediate);//让定时器预分频值立即装入
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);     //清除中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能定时器中断
}

void Timer3_Init(u16 arr,u16 psc)  //定时器3初始化函数
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  //定义配置定时器的结构体变量
	
	//定时器3库函数初始化部分：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能TIM3时钟
	TIM_DeInit(TIM3);	            //将外设TIMx寄存器重设为缺省值 
	TIM_InternalClockConfig(TIM3);  //定时器时钟源，选择内部时钟
	/*基础设置*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;                     //设定计数器自动重装值  
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;    	            //预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  	                //设置时钟分割  采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM3->CR1  &= ~(1<<7);   //自动重装ARR里的值没有缓冲,随时更新数据随时有效。
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);					//初始化

	TIM_Cmd(TIM3, ENABLE);						 //使能定时器3，开始定时
	//TIM_Cmd(TIM3, DISABLE);						 //暂时不启动使能定时器3
	TIM_PrescalerConfig(TIM3, psc - 1, TIM_PSCReloadMode_Immediate);//让定时器预分频值立即装入
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);     //清除中断标志
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //使能定时器中断
}

void Timer7_Init(u16 arr,u16 psc)  //定时器7初始化函数
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  //定义配置定时器的结构体变量
	
	//定时器7库函数初始化部分：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //使能TIM7时钟
	TIM_DeInit(TIM7);	            //将外设TIMx寄存器重设为缺省值 
	TIM_InternalClockConfig(TIM7);  //定时器时钟源，选择内部时钟
	/*基础设置*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;                     //设定计数器自动重装值  
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;    	            //预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  	                //设置时钟分割  采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);					//初始化

	TIM_Cmd(TIM7, ENABLE);						 //使能定时器7，开始定时
	TIM_PrescalerConfig(TIM7, psc - 1, TIM_PSCReloadMode_Immediate);//让定时器预分频值立即装入
	TIM_ClearFlag(TIM7,TIM_FLAG_Update);     //清除中断标志
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //使能定时器中断
}



//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
/*
void Timerx_Init(u16 arr,u16 psc)
{
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	//定时器2初始化部分：
//	RCC->APB1ENR |= 1<<0;  //打开通用定时器TIM2时钟
//	
//	TIM2->ARR = arr;       //设定计数器自动重装值//arr=10刚好1ms    
//	TIM2->PSC = psc;       //预分频器7200,得到10Khz的计数时钟 72MHz/7200=10KHz=0.1ms=100us
//	TIM2->DIER |= 1<<0;    //允许更新中断				
//	TIM2->DIER |= 1<<6;    //允许触发中断	   
//	TIM2->CR1  |= 0x01;    //使能定时器2 

	//定时器3初始化部分：
//	RCC->APB1ENR |= 1<<1;  //打开通用定时器TIM3时钟 
//	   
// 	TIM3->ARR = arr;       //设定计数器自动重装值//arr=10刚好1ms    
//	TIM3->PSC = psc;       //预分频器7200,得到10Khz的计数时钟 72MHz/7200=10KHz=0.1ms=100us
//	TIM3->DIER |= 1<<0;    //允许更新中断				
//	TIM3->DIER |= 1<<6;    //允许触发中断	   
//	TIM3->CR1  |= 0x01;    //使能定时器3

	//定时器4初始化部分：
//	RCC->APB1ENR |= 1<<2;  //打开通用定时器TIM4时钟
//	
//	TIM4->ARR = arr;       //设定计数器自动重装值//arr=10刚好1ms    
//	TIM4->PSC = psc;       //预分频器7200,得到10Khz的计数时钟 72MHz/7200=10KHz=0.1ms=100us
//	TIM4->DIER |= 1<<0;    //允许更新中断				
//	TIM4->DIER |= 1<<6;    //允许触发中断	   
//	TIM4->CR1  |= 0x01;    //使能定时器4 

	//定时器5初始化部分：
//	RCC->APB1ENR |= 1<<3;  //打开通用定时器TIM5时钟
//	
//	TIM5->ARR = arr;       //设定计数器自动重装值//arr=10刚好1ms    
//	TIM5->PSC = psc;       //预分频器7200,得到10Khz的计数时钟 72MHz/7200=10KHz=0.1ms=100us
//	TIM5->DIER |= 1<<0;    //允许更新中断				
//	TIM5->DIER |= 1<<6;    //允许触发中断	   
//	TIM5->CR1  |= 0x01;    //使能定时器5 

	//定时器6初始化部分：
//	RCC->APB1ENR |= 1<<4;  //打开通用定时器TIM6时钟
//	
//	TIM6->ARR = arr;       //设定计数器自动重装值//arr=10刚好1ms    
//	TIM6->PSC = psc;       //预分频器7200,得到10Khz的计数时钟 72MHz/7200=10KHz=0.1ms=100us
//	TIM6->DIER |= 1<<0;    //允许更新中断				
//	TIM6->DIER |= 1<<6;    //允许触发中断	   
//	TIM6->CR1  |= 0x01;    //使能定时器6 

	//定时器7初始化部分：
//	RCC->APB1ENR |= 1<<5;  //打开通用定时器TIM7时钟
//	
//	TIM7->ARR = arr;       //设定计数器自动重装值//arr=10刚好1ms    
//	TIM7->PSC = psc;       //预分频器7200,得到10Khz的计数时钟 72MHz/7200=10KHz=0.1ms=100us
//	TIM7->DIER |= 1<<0;    //允许更新中断				
//	TIM7->DIER |= 1<<6;    //允许触发中断	   
//	TIM7->CR1  |= 0x01;    //使能定时器7 
	
	
	
  	//MY_NVIC_Init(1,3,TIM3_IRQChannel,2);//抢占1，子优先级3，组2									 
}	 */

