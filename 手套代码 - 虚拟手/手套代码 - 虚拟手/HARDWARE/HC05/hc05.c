#include "hc05.h"
#include "string.h"
#define ADC_CHLS 9
void USART1_Send_Char(u8 c)
{
	while((USART1->SR&0X40)==0);//等待上一次发送完毕   
	USART1->DR=c;   	
} 


void USART1_Send_Data(u8*data,u8 len){
//	u8 send_buf[15];
//	u16 ADC_VALUES_AVER[ADC_CHLS];   //每个通道的平均值
//	int aacx,pitch_s,aacy,roll_s,aacz,yaw_s;
//  int finger1,finger2,finger3,finger4,finger5;
//	u8 i;
//	send_buf[0] = 0X55;										//帧头
//	send_buf[1] = 0X53;
//	send_buf[8] = 0X55;			
//	send_buf[14]= 0Xbb;
//	send_buf[2]=aacx;
//	send_buf[3]=pitch_s;
//	send_buf[4]=aacy;
//	send_buf[5]=roll_s;
//	send_buf[6]=aacz;
//	send_buf[7]=yaw_s;
//	for(j=0;j<=5;j++)
//	{
//		send_buf[j+7]=ADC_VALUES_AVER[j];
//	}
// 	for(i=0; i<15; i++)USART1_Send_Char(send_buf[i]);	
}

void HC05_Send_Data(short aacx, short aacy, short aacz, short pitch, short roll, short yaw, 
										short finger1, short finger2, short finger3, short finger4, short finger5
										)
{
	u8 tbuf[22]; 
	tbuf[0] = (aacx>>8)&0XFF;
	tbuf[1] = aacx&0XFF;
	tbuf[2] = (aacy>>8)&0XFF;
	tbuf[3] = aacy&0XFF;
	tbuf[4] = (aacz>>8)&0XFF;
	tbuf[5] = aacz&0XFF; 
	tbuf[6] =(pitch>>8)&0XFF;
	tbuf[7] = pitch&0XFF;
	tbuf[8] = (roll>>8)&0XFF;
	tbuf[9] = roll&0XFF;
	tbuf[10] = (yaw>>8)&0XFF;
	tbuf[11] = yaw&0XFF;
	tbuf[12] = (finger1>>8)&0XFF;
	tbuf[13] = finger1&0XFF;
	tbuf[14] = (finger2>>8)&0XFF;
	tbuf[15] = finger2&0XFF;
	tbuf[16] = (finger3>>8)&0XFF;
	tbuf[17] = finger3&0XFF; 
	tbuf[18] = (finger4>>8)&0XFF;
	tbuf[19] = finger4&0XFF;
	tbuf[20] = (finger5>>8)&0XFF;
	tbuf[21] = finger5&0XFF; 
	USART1_Send_Data(tbuf,22);
}	

void HC05_Send_Data1(short pitch, short roll, short finger1, short finger2, short finger3,short finger4,short finger5)
{
	u8 tbuf[14]; 
	tbuf[0] =(pitch>>8)&0XFF;
	tbuf[1] = pitch&0XFF;
	tbuf[2] = (roll>>8)&0XFF;
	tbuf[3] = roll&0XFF;
	tbuf[4] = (finger1>>8)&0XFF;
	tbuf[5] = finger1&0XFF;
	tbuf[6] = (finger2>>8)&0XFF;
	tbuf[7] = finger2&0XFF;
	tbuf[8] = (finger3>>8)&0XFF;
	tbuf[9] = finger3&0XFF; 
	tbuf[10] = (finger4>>8)&0XFF;
	tbuf[11] = finger4&0XFF; 
	tbuf[12] = (finger5>>8)&0XFF;
	tbuf[13] = finger5&0XFF; 
	USART1_Send_Data(tbuf,14);
}	
