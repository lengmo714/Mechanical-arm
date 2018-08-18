#ifndef _HC05_H
#define _HC05_H

#include "sys.h"
#include "usart.h"

void USART1_Send_Char(u8 c);
void USART1_Send_Data(u8*data,u8 len);
//void HC05_Send_Data(short aacx, short aacy, short aacz, short gyrox, short gyroy, short gyroz, 
//										short finger1, short finger2, short finger3, short finger4, short finger5,
//										short joint1, short joint2, short joint3, short joint4);
void HC05_Send_Data(short aacx, short aacy, short aacz, short pitch, short roll, short yaw, 
										short finger1, short finger2, short finger3, short finger4, short finger5
										);
void HC05_Send_Data1(short gyrox, short gyroy, short finger1, short finger2, short finger3, short finger4, short finger5);
#endif		//_HC05_H											