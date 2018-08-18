#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h" 
#include "stdio.h"	 
 	  
 
	  	
void USART1_Config(void);   //初始化 配置USART1
void USART2_Config(void);   //初始化 配置USART2
void USART3_Config(void);   //初始化 配置USART3
void UART4_Config(void);    //初始化 配置UART4
void UART5_Config(void);    //初始化 配置UART5
void usart3_SendByte(unsigned char SendData);	  //用串口3发送一个字节数据



#endif	   
















