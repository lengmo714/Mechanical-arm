#include "led.h"
#include "delay.h"
#include "sys.h"
#include "includes.h"
#include "stdio.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "TFT_demo.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "hc05.h"
#include "mpu6050.h"
#include "inv_mpu.h" 

//-------------------------------------UCOSII任务设置----------------------------------------------
//START 任务
#define START_TASK_PRIO      						6     //设置任务优先级,开始任务的优先级设置为最低
#define START_STK_SIZE  								64		//设置任务堆栈大小
OS_STK START_TASK_STK[START_STK_SIZE];				//任务堆栈	
void start_task(void *pdata);									//任务函数
 			   
//LED任务
#define LED_TASK_PRIO   			    			2      //设置任务优先级,开始任务的优先级设置为最低
#define LED_STK_SIZE  		    					64      //设置任务堆栈大小
OS_STK LED_TASK_STK[LED_STK_SIZE];             //任务堆栈         
void led_task(void *pdata);                     //任务函数

//GUI任务
#define GUI_TASK_PRIO       						4       //设置任务优先级,开始任务的优先级设置为最低
#define GUI_STK_SIZE  									128      //设置任务堆栈大小
OS_STK GUI_TASK_STK[GUI_STK_SIZE];
void gui_task(void *pdata);

//ADC转换任务
#define ADC_TASK_PRIO 									3        //设置任务优先级,开始任务的优先级设置为最低
#define ADC_STK_SIZE										64       //设置任务堆栈大小
OS_STK ADC_TASK_STK[ADC_STK_SIZE];
void adc_task(void *pdata);

//MPU6050任务
#define MPU6050_TASK_PRIO								1          //设置任务优先级,开始任务的优先级设置为最低
#define MPU6050_STK_SIZE								128        //设置任务堆栈大小
OS_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];
void mpu6050_task(void *pdata);

//HC05任务
#define HC05_TASK_PRIO									5           //设置任务优先级,开始任务的优先级设置为最低
#define HC05_STK_SIZE										64          //设置任务堆栈大小
OS_STK HC05_TASK_STK[HC05_STK_SIZE];
void hc05_task(void *pdata);


//-------------------------------------UCOSII任务设置结束----------------------------------------------

//-----------------------------------------全局变量----------------------------------------------------

#define ADC_CHLS 5 							        //5路ADC
#define ADC_CNTS 10						         //每个ADC通道取10次值
u16 ADC_VALUES[ADC_CNTS][ADC_CHLS];			//存储ADC转换后M*N个数字量的数据 
u16 ADC_VALUES_AVER[ADC_CHLS];					//每个ADC通道的平均值
float pitch, roll, yaw;
short pitch_s, roll_s, yaw_s;
short aacx, aacy, aacz;
short aacx_t, aacy_t, aacz_t;
char  gps_rec_data1[10];
char  gps_rec_data2[10];
u8 t;
u8 len;
int count = 0;
int m = 0;
int n = 0;
int figure1,figure2,figure3,figure4,figure5;
int i,j;
long int sum1=0;
long int sum2=0;
long int sum3=0;
long int sum4=0;
long int sum5=0;
u8 send_buf[15];
//---------------------------------------全局变量定义结束---------------------------------------------

//ADC
void ADC_Filter(void)
{
	u8 i, j;
	u16 sum = 0;											
	for(i=0; i < ADC_CHLS; i++)							//每个通道进行循环滤波
	{
		for(j = 0; j < ADC_CNTS; j++)					//采样N次循环
		{
			 sum += ADC_VALUES[j][i];						//计算出N次采样值的总和
    }
    ADC_VALUES_AVER[i]= sum /10;          //求出通道数字量的平均值
    sum = 0;                              //清零便于下次重新计算
  }
}
 
//int ADC_figure(int i)                    //弯曲度传感器的初始值
//{
//	u8 j;
//	int figure;
//	long int sum = 0;
//		for(j = 0; j < ADC_CNTS; j++)				  	//采样N次循环
//		{
//			  sum += ADC_VALUES[j][i];						//计算出N次采样值的总和
//    }
//    figure = sum / ADC_CNTS;                //求出通道数字量的平均值
//    sum = 0;                                //清零便于下次重新计算
//		return figure;
//}

//------------------------------------------主函数-----------------------------------------------------

 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	
  NVIC_Configuration();	 
	uart_init(115200);
	Init_LEDpin();		  	//初始化与LED连接的硬件接口
	Lcd_Init();  //LCD初始化
	Adc_Init();   //模拟数字转换器初始化
	MyDMA_Init(DMA1_Channel1,(u32)&ADC1->DR, (u32)&ADC_VALUES, ADC_CHLS*ADC_CNTS);	//初始化DMA DMA存储器直接访问
	while(MPU_Init() != 0) printf("mpu init error!");
	while(mpu_dmp_init() != 0)printf("mpu dmp init error!");
	OSInit(); //系统初始化 ucos ii初始化   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	//任务开始
 }

	  
//开始任务
void start_task(void *pdata) //pdata指针
{
  OS_CPU_SR cpu_sr=0;   
	pdata = pdata;       
  OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);						   
 	OSTaskCreate(gui_task,(void *)0,(OS_STK*)&GUI_TASK_STK[GUI_STK_SIZE-1],GUI_TASK_PRIO);	
	OSTaskCreate(adc_task,(void *)0,(OS_STK*)&ADC_TASK_STK[ADC_STK_SIZE-1],ADC_TASK_PRIO);	 
	OSTaskCreate(mpu6050_task,(void *)0,(OS_STK*)&MPU6050_TASK_STK[MPU6050_STK_SIZE-1],MPU6050_TASK_PRIO);	 				   
	OSTaskCreate(hc05_task,(void *)0,(OS_STK*)&HC05_TASK_STK[HC05_STK_SIZE-1],HC05_TASK_PRIO);	   				   
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//gui任务 
void gui_task(void *pdata)
#include <stm32f10x.h>
{	
	char pitch_str[16];
	char roll_str[16];
	char yaw_str[16];

	LCD_LED_SET;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(5,20,BLUE,GRAY0,"pitch:");
	Gui_DrawFont_GBK16(5,40,BLUE,GRAY0," roll:");     
	Gui_DrawFont_GBK16(5,60,BLUE,GRAY0," yaw :");
	
	while(1){
		
			if(USART_RX_STA&0x8000)
		{	
	
			len=USART_RX_STA&0x3fff;   //得到此次接收到的数据长度
			for(t=1;t<len;t++)
			{
				if(USART_RX_BUF[t]==',')
				{	count++; 
					continue;
				 }
				if(count%2 == 1)
				{
				 gps_rec_data2[n] = USART_RX_BUF[t];
				 n++;
				}
				if(count%2 == 0)
				{	
				  gps_rec_data1[m] = USART_RX_BUF[t];
					m++;
				}
			}
			 for(;m<10;m++)  gps_rec_data1[m]=' ';
	  	 for(;n<10;n++)  gps_rec_data2[n]=' ';
			  m = 0;
			  n = 0;
			  count = 0;
        USART_RX_STA=0;
		}
		
		Gui_DrawFont_GBK16(70, 20, GRAY0, GRAY0, "          ");
		Gui_DrawFont_GBK16(70, 40, GRAY0, GRAY0, "          ");
		Gui_DrawFont_GBK16(70, 60, GRAY0, GRAY0, "          ");

		sprintf(pitch_str, "%+4d" , pitch_s);
		sprintf(roll_str, "%+4d", roll_s);
		sprintf(yaw_str, "%+4d", yaw_s);
		
		Gui_DrawFont_GBK16(70, 20, RED, GRAY0, pitch_str);
		Gui_DrawFont_GBK16(70, 40, RED, GRAY0, roll_str);
		Gui_DrawFont_GBK16(70, 60, RED, GRAY0, yaw_str);
		
		  delay_ms(50);
	}
}

//LED任务 
void led_task(void *pdata)
{	  
	while(1)
	{
		LED1=0;
		delay_ms(300);
		LED1=1;
		delay_ms(300);
	};
}

void adc_task(void *pdata){
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	DMA_Cmd(DMA1_Channel1, ENABLE);			    	//使能DMA通道
	delay_ms(2000);
//	for(j=0;j<10;j++)
//	{
//	sum1 = sum1 + ADC_figure(0);
//	figure1 = sum1 /10 ;
//	sum2 = sum2 + ADC_figure(1);
//	figure2 = sum2 /10 ;
//	sum3 = sum3 + ADC_figure(2);
//	figure3 = sum3 /10 ;
//	sum4 = sum4 + ADC_figure(3);
//	figure4 = sum4 /10 ;
//	sum5 = sum5 + ADC_figure(4);
//	figure5 = sum5 /10 ;
//	}
	while(1){
		ADC_Filter();
		delay_ms(20);
	}
}

void mpu6050_task(void *pdata){
	
	while(1){
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
			pitch_s = -(short)pitch ;
			roll_s = (short)roll ;
			yaw_s = (short)yaw ;
			aacx_t = aacx / 10 + 3276;
			aacy_t = aacy / 10 + 3276;
			aacz_t = aacz / 10 + 3276;
			delay_ms(30);
		}
	}
}

void hc05_task(void *pdata){
	while(1){	
	send_buf[0] = 0X55;										//帧头
	send_buf[1] = 0X53;
	send_buf[8] = 0Xaa;			
	send_buf[14]= 0Xbb;
	send_buf[2]=aacx;
	send_buf[3]=pitch_s;
	send_buf[4]=aacy;
	send_buf[5]=roll_s; 
	send_buf[6]=aacz;
	send_buf[7]=yaw_s;	 
	for(j=0;j<5;j++)
	{
		send_buf[j+9]=ADC_VALUES_AVER[j];
	}	
	for(j=0; j<15; j++)USART1_Send_Char(send_buf[j]);			      	//发送数据 
	}

//	while(1){
//		if((ADC_VALUES_AVER[2]>figure3+200)&&pitch_s>20)           //大拇指
//			printf("G91 C05 F2000\n\r");
//		else if((ADC_VALUES_AVER[2]>figure3+200)&&pitch_s<-20)
//			printf("G91 -C05 F2000\n\r");
//		else if((ADC_VALUES_AVER[1]<figure2+100)&&roll_s>20)        //中指
//			printf("G91 D05 F2000\n\r");
//		else if((ADC_VALUES_AVER[1]<figure2+100)&&roll_s<-20)
//			printf("G91 -D05 F2000\n\r");
//		else if(roll_s>20)
//			printf("G91 A05 F2000\n\r");
//		else if(roll_s<-20)
//			printf("G91 -A05 F2000\n\r");
//		else if(pitch_s>20)
//			printf("G91 B05 F2000\n\r");
//		else if(pitch_s<-20)
//			printf("G91 -B05 F2000\n\r");
//		delay_ms(500);
//	}
}
