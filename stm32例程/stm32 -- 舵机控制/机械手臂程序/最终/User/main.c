#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "MY_time_Conf.h"
//#include "uart_1.h"
//#include "dma.h"
//#include "RS485.h"
//#include "74hc595.h"
#include "string.h"
#include "timer.h"
#include "exti.h"
/**************************
模板配置信息：
选用芯片是 stm32f103vc
启动信息：stm32f10x_hd.s
固件库：stm32固件库v3.5
***************************/

//#define led_PB12   PBout(12)	   //位绑定，位定义PB12口作为LED输出。这样速度最快
//#define led_PB1   PBout(1)	   //位绑定，位定义PB1口作为LED输出。这样速度最快
//#define PA9   PAout(10)
//#define CLK1   PDout(0)
//#define CWW1   PDout(1)
//#define CLK2   PDout(2)
//#define CWW2   PDout(3)


//uint8_t i = 0;    //测试用

float a[3],w[3],angle[3],T,finger[5];
extern unsigned char Re_buf[15],temp_buf[15],counter;
extern unsigned char sign;


int time_js = 0;
int compare0 = 150;//PWM宽度
int compare = 150;//PWM宽度
int compare1 = 150;//PWM宽度
int compare2 = 150;//PWM宽度
int compare3 = 150;//PWM宽度
int compare4 = 150;//PWM宽度

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键1

int sure;



/*************************************************
函数: int main(void)
功能: main主函数
参数: 无
返回: 无
**************************************************/

int main(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
   unsigned char Temp[15];
   //u8 i;

   RCC_Configuration();      //初始化时钟
   GPIO_Configuration();      //初始化IO端口
   delay_init(72);            //初始化延时函数
   NVIC_Configuration();      //中断优先级初始化

   USART1_Config();   //初始化 配置USART1
 //  USART2_Config();   //初始化 配置USART2 （用于接收MPU6050数据）
   TIM3_Int_Init(9,71,1);//0.01ms中断一次（不用PWM通道输出，通过中断产生pwm
	
		EXTIX_Init();		//外部中断初始化
   delay_ms(200);
	
 
 	
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PD端口时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);	 //使能PD端口时钟
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
  GPIO_SetBits(GPIOA,GPIO_Pin_6);						 //PA.8 输出高

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //LED1-->PD.2 端口配置, 推挽输出

  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
  GPIO_ResetBits(GPIOA,GPIO_Pin_4);						 //PD.2 输出高 	 
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_1|GPIO_Pin_15|GPIO_Pin_13;				 //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
  GPIO_SetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_1|GPIO_Pin_15|GPIO_Pin_13);						 //PA.8 输出高
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
  GPIO_SetBits(GPIOD,GPIO_Pin_2);						 //PA.8 输出高
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
 
	
	 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;            
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;                     
 GPIO_Init(GPIOB, &GPIO_InitStructure); 


	
//	delay_ms(2000);		
      
   while (1)
   {
		 //陀螺仪读取数据
      if(sign)
      {  
         memcpy(Temp,Re_buf,15);
         sign=0;
         if((Re_buf[0]==0x55)&&(Re_buf[1]==0x53))       //检查帧头
         {  

                 angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角（x 轴）
                 angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
                 angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角（z 轴）
    	
						
	       //手臂舵机打角，横滚角，俯仰角和偏转角分别控制不同舵机
						compare0 =150 + angle[2];
						compare = 150 + 0.3*angle[0];
						compare1 =150 - 0.5*angle[0];	
						compare2 =150 - angle[0];	
						compare3 =150 + angle[1];	
						
					
						
						       
						}
				 
		
						//手指舵机打角，这里只控制了一个舵机，也只用了一根手指，事实上finger数组里面存的是5手指弯曲度，均可使用
						  if(Re_buf[8]==0xaa)       
           {  
              finger[0] = Temp[9] ;
					 
					  	compare4 =150 + finger[0]*0.5;
						    
						}
						
						
						
				
											
    //	delay_ms(20);		
						
						
						
						
         }
         
      }
     // delay_ms(50);
   }
 



/*
int main(void)
{
	
	//u8 i;

	RCC_Configuration();	   //初始化时钟
	GPIO_Configuration();	   //初始化IO端口
	delay_init(72);			   //初始化延时函数
	NVIC_Configuration();	   //中断优先级初始化

	USART1_Config();   //初始化 配置USART1
	USART2_Config();   //初始化 配置USART2 （用于接收MPU6050数据）
	
	delay_ms(200);

		
	while (1)
	{
		if(sign)
		{  
			sign=0;
//			if(Re_buf[0]==0x55)       //检查帧头
//			{  
//				switch(Re_buf[1])
//				{
//					case 0x51: //标识这个包是加速度包
//						a[0] = ((short)(Re_buf[3]<<8 | Re_buf[2]))/32768.0*16;		//X轴加速度
//						a[1] = ((short)(Re_buf[5]<<8 | Re_buf[4]))/32768.0*16;		//Y轴加速度
//						a[2] = ((short)(Re_buf[7]<<8 | Re_buf[6]))/32768.0*16;		//Z轴加速度
//						T    = ((short)(Re_buf[9]<<8 | Re_buf[8]))/340.0+36.25;		//温度
//						break;
//					case 0x52: //标识这个包是角速度包
//						w[0] = ((short)(Re_buf[3]<<8| Re_buf[2]))/32768.0*2000;		//X轴角速度
//						w[1] = ((short)(Re_buf[5]<<8| Re_buf[4]))/32768.0*2000;		//Y轴角速度
//						w[2] = ((short)(Re_buf[7]<<8| Re_buf[6]))/32768.0*2000;		//Z轴角速度
//						T    = ((short)(Re_buf[9]<<8| Re_buf[8]))/340.0+36.25;		//温度
//						break;
//					case 0x53: //标识这个包是角度包
//						angle[0] = ((short)(Re_buf[3]<<8| Re_buf[2]))/32768.0*180;	//X轴滚转角（x 轴）
//						angle[1] = ((short)(Re_buf[5]<<8| Re_buf[4]))/32768.0*180;	//Y轴俯仰角（y 轴）
//						angle[2] = ((short)(Re_buf[7]<<8| Re_buf[6]))/32768.0*180;	//Z轴偏航角（z 轴）
//						T        = ((short)(Re_buf[9]<<8| Re_buf[8]))/340.0+36.25;	//温度
//
//						//printf("X轴角度：%.2f   Y轴角度：%.2f   Z轴角度：%.2f\r\n",angle[0],angle[1],angle[2]);
//						printf("%.2f   %.2f   %.2f\r\n",angle[0],angle[1],angle[2]);
//						break;
//					default:  break;
//				}
//			}
			//printf("X角度：%.2f  Y角度：%.2f  Z角度：%.2f  X速度：%.2f  Y速度：%.2f  Z速度：%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);

//			if(temp_buf[0]==0x55)       //检查帧头
//			{  
//				temp_buf[0] = 0;
//				switch(temp_buf[1])
//				{
//					case 0x51: //标识这个包是加速度包
//						a[0] = ((short)(temp_buf[3]<<8 | temp_buf[2]))/32768.0*16;		//X轴加速度
//						a[1] = ((short)(temp_buf[5]<<8 | temp_buf[4]))/32768.0*16;		//Y轴加速度
//						a[2] = ((short)(temp_buf[7]<<8 | temp_buf[6]))/32768.0*16;		//Z轴加速度
//						T    = ((short)(temp_buf[9]<<8 | temp_buf[8]))/340.0+36.25;		//温度
//						break;
//					case 0x52: //标识这个包是角速度包
//						w[0] = ((short)(temp_buf[3]<<8| temp_buf[2]))/32768.0*2000;		//X轴角速度
//						w[1] = ((short)(temp_buf[5]<<8| temp_buf[4]))/32768.0*2000;		//Y轴角速度
//						w[2] = ((short)(temp_buf[7]<<8| temp_buf[6]))/32768.0*2000;		//Z轴角速度
//						T    = ((short)(temp_buf[9]<<8| temp_buf[8]))/340.0+36.25;		//温度
//						break;
//					case 0x53: //标识这个包是角度包
//						angle[0] = ((short)(temp_buf[3]<<8| temp_buf[2]))/32768.0*180;	//X轴滚转角（x 轴）
//						angle[1] = ((short)(temp_buf[5]<<8| temp_buf[4]))/32768.0*180;	//Y轴俯仰角（y 轴）
//						angle[2] = ((short)(temp_buf[7]<<8| temp_buf[6]))/32768.0*180;	//Z轴偏航角（z 轴）
//						T        = ((short)(temp_buf[9]<<8| temp_buf[8]))/340.0+36.25;	//温度
//
//						printf("X轴角度：%.2f   Y轴角度：%.2f   Z轴角度：%.2f\r\n",angle[0],angle[1],angle[2]);
//						break;
//					default:  break;
//				}
//			}
		}

		//printf("X轴角度：%.2f   Y轴角度：%.2f   Z轴角度：%.2f\r\n",angle[0],angle[1],angle[2]);
		delay_ms(50);
	}
}	 */


