#ifndef __RS485_H
#define __RS485_H
#include "stm32f10x.h" 

/*RE跟GPIOC5管脚相连*/   
#define Set_RE       GPIO_SetBits(GPIOC,GPIO_Pin_5);		// 一个位操作,某个位置1。	 
#define Clr_RE       GPIO_ResetBits(GPIOC,GPIO_Pin_5);	    // 一个位操作,某个位清零。
/*DE跟GPIOC4管脚相连*/
#define Set_DE       GPIO_SetBits(GPIOC,GPIO_Pin_4);		// 一个位操作,某个位置1。
#define Clr_DE       GPIO_ResetBits(GPIOC,GPIO_Pin_4);	    // 一个位操作,某个位清零。

extern u8 buff_485[9];         //接收485信号缓存区
extern u8 uart_1;              //串口1接收标志
extern u8 di_zhi;		       //设备地址


void USART1_Config(void);   //初始化 配置USART1
void USART2_Config(void);   //初始化 配置USART2
void USART3_Config(void);   //初始化 配置USART3
void UART4_Config(void);    //初始化 配置UART4
void UART5_Config(void);    //初始化 配置UART5
void RS485_SendByte(unsigned char SendData);	  //发送一个字节数据

#endif
