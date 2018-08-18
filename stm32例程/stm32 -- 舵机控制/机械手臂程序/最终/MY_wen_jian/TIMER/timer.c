#include "timer.h"
//#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

////////////////////////////////////////////////////////////////////////////////// 	  
 

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

extern int time_js;
extern int compare0;
extern int compare;
extern int compare1;
extern int compare2;
extern int compare3;
extern int compare4;






#define LED1 PDout(2)	// PD2	


//0~7 17
void TIM3_Int_Init(u16 arr,u16 psc,int i)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = i;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
//11 12 18
void TIM2_Int_Init(u16 arr,u16 psc,int i)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = i;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
	
	//DISABLE
							 
}






void TIM2_IRQHandler(void)
{
  	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
	
			
		}
}



void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
	//	LED1=!LED1;
			
			time_js ++;
			//PA6
					if(time_js > compare0)
			{
			  GPIO_ResetBits(GPIOA,GPIO_Pin_6); 
		//		LED1 = 1;				
			}
			else
			{
			 GPIO_SetBits(GPIOA,GPIO_Pin_6); 
	//		 LED1 = 0;
			}


						if(time_js > compare)
			{
			  GPIO_ResetBits(GPIOA,GPIO_Pin_4); 
			
			}
			else
			{
			 GPIO_SetBits(GPIOA,GPIO_Pin_4); 

			}
			
			
				if(time_js > compare1)
			{
			  GPIO_ResetBits(GPIOC,GPIO_Pin_3); 
			
			}
			else
			{
			 GPIO_SetBits(GPIOC,GPIO_Pin_3); 

			}
			
						if(time_js > compare2)
			{
			  GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
			
			}
			else
			{
			 GPIO_SetBits(GPIOC,GPIO_Pin_1); 

			}
			
				if(time_js > compare3)
			{
			  GPIO_ResetBits(GPIOC,GPIO_Pin_13); 
	//			LED1 = 1;				
			}
			else
			{
			 GPIO_SetBits(GPIOC,GPIO_Pin_13); 
	//		 LED1 = 0;
			}
			
				if(time_js > compare4)
			{
			  GPIO_ResetBits(GPIOB,GPIO_Pin_15); 
	//			LED1 = 1;				
			}
			else
			{
			 GPIO_SetBits(GPIOB,GPIO_Pin_15); 
	//		 LED1 = 0;
			}
			
						
			if(time_js>=2000)
			{
			  time_js = 0;
				LED1 = !LED1;
			
			}
			
	
			
		}
}












