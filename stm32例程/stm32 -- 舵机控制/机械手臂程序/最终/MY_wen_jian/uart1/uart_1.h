#ifndef __UART_1_H
#define __UART_1_H
#include "stm32f10x.h" 


void USART1_Configuration(void);		//初始化串口硬件设备，启用中断
void Uart1_PutChar(u8 ch);	            //串口1发送1字节


#endif

