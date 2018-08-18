#include "exti.h"
//#include "led.h"
//#include "key.h"
#include "delay.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

 
 
//外部中断初始化函数
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	//  KEY_Init();//初始化按键对应io模式

    //GPIOC.5 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		

 
}

 
void EXTI1_IRQHandler(void)
{

	USART_SendData(USART1,0xFF);   //用串口3发送一个字节
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  //等待串口3发送完毕
	
  USART_SendData(USART1,0xAA);   //用串口3发送一个字节
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  //等待串口3发送完毕
	
  USART_SendData(USART1,0x52);   //用串口3发送一个字节
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  //等待串口3发送完毕
	
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI0线路挂起位
}

