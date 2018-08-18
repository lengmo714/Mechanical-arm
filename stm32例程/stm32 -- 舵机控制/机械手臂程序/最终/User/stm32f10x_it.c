/**
  ******************************************************************************
  * @file    GPIO/JTAG_Remap/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "sys.h"
#include "string.h"
//#include "uart_1.h"
//#include "dma.h"
//#include "RS485.h"
//#include "74hc595.h"

//u8 t = 0;	 //¶¨ÒåÁÙÊ±±äÁ¿ ²âÊÔÓÃ
//u8 he = 0;	//Ð£ÑéºÍ
//
//extern u8 f;    //²âÊÔÓÃ,´®¿Ú1×¼±¸·¢ËÍ±êÖ¾
//
//#define led_PB13   PBout(13)	   //Î»°ó¶¨£¬Î»¶¨ÒåPB13¿Ú×÷ÎªLEDÊä³ö¡£ÕâÑùËÙ¶È×î¿ì
//#define feng      PBout(14)	   //Î»°ó¶¨£¬Î»¶¨ÒåPB14¿Ú×÷ÎªLEDÊä³ö(·äÃùÆ÷)¡£ÕâÑùËÙ¶È×î¿ì
//
//#define CLK1   PDout(0)
//#define CWW1   PDout(1)
//#define CLK2   PDout(2)
//#define CWW2   PDout(3)
//
//u8 buff[5] = {0,0,0,0,0}; //²âÊÔ
//u8 p = 0;  //²âÊÔ
//u8 LR_uart_buf = 0;
//u8 UD_uart_buf = 0;
//u8 fang_xiang = 0;
//u8 Led_T = 0; //LED·¢¹âÊ±¼ä±äÁ¿
////u8 Time2_OK = 0;  //¶¨Ê±Æ÷ÖÐ¶ÏÍê³É±êÖ¾

unsigned char Re_buf[11],temp_buf[11],counter=0;
unsigned char sign,t,he;

static unsigned char Temp[11];





/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_JTAG_Remap
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void WWDG_IRQHandler(void)		 //´°¿Ú¶¨Ê±Æ÷ÖÐ¶Ï·þÎñº¯Êý
{
}

void PVD_IRQHandler(void)		 //Áªµ½EXTIµÄµçÔ´µçÑ¹¼ì²â£¨PVD£©ÖÐ¶Ï·þÎñº¯Êý
{
}

void TAMPER_IRQHandler(void)	 //ÇÖÈë¼ì²âÖÐ¶Ï·þÎñº¯Êý
{
}

void RTC_IRQHandler(void)		 //ÊµÊ±Ê±ÖÓ£¨RTC£©È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{

}

void FLASH_IRQHandler(void)		 //ÉÁ´æÈ«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void RCC_IRQHandler(void)		 //¸´Î»ºÍÊ±ÖÓ¿ØÖÆ£¨RCC£©ÖÐ¶Ï·þÎñº¯Êý
{
}

void EXTI0_IRQHandler(void)		 //EXTIÏß0ÖÐ¶Ï·þÎñº¯Êý
{

}
/*
void EXTI1_IRQHandler(void)		 //EXTIÏß1ÖÐ¶Ï·þÎñº¯Êý
{

}
*/
void EXTI2_IRQHandler(void)		 //EXTIÏß2ÖÐ¶Ï·þÎñº¯Êý
{
}

void EXTI3_IRQHandler(void)		 //EXTIÏß3ÖÐ¶Ï·þÎñº¯Êý
{
}

void EXTI4_IRQHandler(void)		 //EXTIÏß4ÖÐ¶Ï·þÎñº¯Êý
{
 
}

void DMA1_Channel1_IRQHandler(void)	   //DMA1Í¨µÀ1È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA1_Channel2_IRQHandler(void)	   //DMA1Í¨µÀ2È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA1_Channel3_IRQHandler(void)	   //DMA1Í¨µÀ3È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA1_Channel4_IRQHandler(void)	   //DMA1Í¨µÀ4È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	//ÅÐ¶ÏÊÇ·ñÎªDMA·¢ËÍÍê³ÉÖÐ¶Ï
//	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)==SET) 
//	{  	
//		DMA_ClearFlag(DMA2_FLAG_TC4);//Çå³ýÍ¨µÀ4´«ÊäÍê³É±êÖ¾ 
//	}	
}

void DMA1_Channel5_IRQHandler(void)	   //DMA1Í¨µÀ5È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(DMA_GetITStatus(DMA1_IT_TC5))
// 	{
//	    //DataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);//»ñÈ¡Ê£Óà³¤¶È,Ò»°ã¶¼Îª0,µ÷ÊÔÓÃ
//	    DMA_ClearITPendingBit(DMA1_IT_GL5);	//Çå³ýÈ«²¿ÖÐ¶Ï±êÖ¾										     
//		//×ª»»¿É²Ù×÷BUF
//		if(Free_Buf_No==BUF_NO1) //Èç¹ûBUF1¿ÕÏÐ£¬½«DMA½ÓÊÕÊý¾Ý¸³Öµ¸øBUF1
//		{	
//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf1;
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//			Free_Buf_No=BUF_NO2;
//		}
//		else  //Èç¹ûBUF2¿ÕÏÐ£¬½«DMA½ÓÊÕÊý¾Ý¸³Öµ¸øBUF2
//		{
//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf2;
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//			Free_Buf_No=BUF_NO1;
//		}
//		Buf_Ok=TRUE;	   //ÓÐ×¼±¸ºÃµÄÊý¾ÝÁË
// 	}
}

void DMA1_Channel6_IRQHandler(void)	   //DMA1Í¨µÀ6È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA1_Channel7_IRQHandler(void)	   //DMA1Í¨µÀ7È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void ADC1_2_IRQHandler(void)		   //ADCÈ«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
    //Get injected channel1 converted value  // ADC_GetConversionValue(ADC1);
 //     ADC_ConvertedValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
 //     ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC); // Çå³ýADCxµÄÖÐ¶Ï´ý´¦ÀíÎ» £»

/*  GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)));
    ADC_ClearITPendingBit(ADC1, ADC_IT_AWD); // Çå³ýADC1µÄAWDOGÖÐ¶ÏÆÁ±Î´¦ÀíÎ» £»    */

    /* Clear ADC1 JEOC pending interrupt bit */
  //    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
  //    ADC_ConvertedValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
}

void USB_HP_CAN_TX_IRQHandler(void)	   //USB¸ßÓÅÏÈ¼¶»òCAN·¢ËÍÖÐ¶Ï·þÎñº¯Êý
{
}

void USB_LP_CAN_RX0_IRQHandler(void)   //USBµÍÓÅÏÈ¼¶»òCAN½ÓÊÕ0ÖÐ¶Ï·þÎñº¯Êý
{
}

void CAN_RX1_IRQHandler(void)		   //CAN½ÓÊÕ1ÖÐ¶Ï·þÎñº¯Êý
{
}

void CAN_SCE_IRQHandler(void)		   //CAN SCEÖÐ¶Ï·þÎñº¯Êý
{
}

void EXTI9_5_IRQHandler(void)		   //Íâ²¿ÖÐ¶Ï9Ïß¡¾9:5¡¿ÖÐ¶Ï·þÎñº¯Êý
{
//	if(EXTI_GetITStatus(EXTI_Line9) != RESET) 
//	{
//     //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
////		t = !t;	   //È¡·´±êÖ¾Î»
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ
//
//		led_PB13 = ~led_PB13;	   //È¡·´
//	
//		EXTI_ClearFlag(EXTI_Line9);			          //Çå³ýÖÐ¶Ï±êÖ¾£¨±ØÐë£©
//		EXTI_ClearITPendingBit(EXTI_Line9);			  //Çå³ýÖÐ¶Ï¹ÒÆð»
//	 }
}

void TIM1_BRK_IRQHandler(void)		   //¶¨Ê±Æ÷1¶Ï¿ªÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM1_UP_IRQHandler(void)		   //¶¨Ê±Æ÷1¸üÐÂÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM1_TRG_COM_IRQHandler(void)	   //¶¨Ê±Æ÷1´¥·¢ºÍÍ¨ÐÅÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM1_CC_IRQHandler(void)		   //¶¨Ê±Æ÷1²¶»ñ±È½ÏÖÐ¶Ï·þÎñº¯Êý
{
}
/*
void TIM2_IRQHandler(void)			   //¶¨Ê±Æ÷2È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(TIM2->SR & 0X0001)//Òç³öÖÐ¶Ï
//	{	
//	    //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
////		t = !t;	   //È¡·´±êÖ¾Î»
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ
//		
//		CLK1 = ~CLK1;
//	}				   
//	TIM2->SR &= ~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î»
//	TIM_Cmd(TIM2, DISABLE);						 //¹Ø¶¨Ê±Æ÷2£¬ÔÚmainº¯ÊýÄÚ´ò¿ª
//	
//	//Time2_OK = 1;
}

void TIM3_IRQHandler(void)			   //¶¨Ê±Æ÷3È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(TIM3->SR & 0X0001)//Òç³öÖÐ¶Ï
//	{	
//	    //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
////		t = !t;	   //È¡·´±êÖ¾Î»
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ
//		
//		CLK2 = ~CLK2;
//	}				   
//	TIM3->SR &= ~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î»
//	TIM_Cmd(TIM3, DISABLE);						 //¹Ø¶¨Ê±Æ÷3£¬ÔÚmainº¯ÊýÄÚ´ò¿ª
}
*/
void TIM4_IRQHandler(void)			   //¶¨Ê±Æ÷4È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(TIM4->SR & 0X0001)//Òç³öÖÐ¶Ï
//	{	
//	    //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
//		t = !t;	   //È¡·´±êÖ¾Î»
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ			    				   				     	    	
//	}				   
//	TIM4->SR &= ~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î»
}

void I2C1_EV_IRQHandler(void)		   //I2C1ÊÂ¼þÖÐ¶Ï·þÎñº¯Êý
{
}

void I2C1_ER_IRQHandler(void)		   //I2C1´íÎóÖÐ¶Ï·þÎñº¯Êý
{
}

void I2C2_EV_IRQHandler(void)		   //I2C2ÊÂ¼þÖÐ¶Ï·þÎñº¯Êý
{
}

void I2C2_ER_IRQHandler(void)		   //I2C2´íÎóÖÐ¶Ï·þÎñº¯Êý
{
}

void SPI1_IRQHandler(void)			   //SPI1È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void SPI2_IRQHandler(void)			   //SPI2È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void USART1_IRQHandler(void)		   //´®¿Ú1È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
	{
	      Temp[counter] = USART_ReceiveData(USART1);   //½ÓÊÕÊý¾Ý
      //Íø¹º¸øµÄ³ÌÐò
      //if(counter == 0 && Re_buf[0] != 0x55) return;      //µÚ 0 ºÅÊý¾Ý²»ÊÇÖ¡Í·£¬Ìø¹ý
	  if(counter == 0 && (Temp[0] != 0x55)) return;      //µÚ 0 ºÅÊý¾Ý²»ÊÇÖ¡Í·£¬Ìø¹ý
      counter++; 
      if(counter==15) //½ÓÊÕµ½ 15 ¸öÊý¾Ý
      { 
         memcpy(Re_buf,Temp,15);
         counter=0; //ÖØÐÂ¸³Öµ£¬×¼±¸ÏÂÒ»Ö¡Êý¾ÝµÄ½ÓÊÕ
         sign=1;
      }  
	}
//  	{
//    	//buff_485[0] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //Èç¹û½ÓÊÕÍêÊý¾Ý£¬½ÓÊÕ×´Ì¬¹éÁã
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //½øÐÐÐ£Ñé
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//					{
//						//ming_ling_jie_shi();         //½âÊÍÃüÁî
//						if(buff_485[3] == 0x08 )	feng = 0;  //ÉÏ ·äÃùÆ÷·¢Éú
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //·¢ËÍÍ£Ö¹ÐÅºÅ
//						{
//						 	feng = 1;	//¹Ø·äÃùÆ÷
//						}
//					}
//					else  //·ñÔò²»ÕýÈ·
//					{
//					 	for(t = 0;t<9;t++)           //ÇåÁã
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(USART1);	//½ÓÊÕÊý¾Ý
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //½øÐÐÐ£Ñé

//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//				{
//					//ming_ling_jie_shi();         //½âÊÍÃüÁî
//				}
//				else  //·ñÔò²»ÕýÈ·
//				{
//				 	for(t = 0;t<9;t++)           //ÇåÁã
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}



//	if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)      // ·¢ËÍÖÐ¶ÏÓÐÐ§ £» 
//  	{   
//		//USART_ClearFlag(USART1, USART_FLAG_TC);                //Çå´®¿Ú1·¢ËÍ±êÖ¾
//
//		f ++;
//		if(f >= 2)	{f = 0; } // Çå³ýUSART1µÄ·¢ËÍÖÐ¶Ï £» 
//		else  
//		{
//			USART_ClearITPendingBit(USART1, USART_IT_TXE);     // Çå³ýUSART1µÄ·¢ËÍÖÐ¶Ï 
//			USART_SendData(USART1, 0x97);
//		}
//  	}   
}  	 

void USART2_IRQHandler(void)		   //´®¿Ú2È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
//  	{
//		Re_buf[counter] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//		//Íø¹º¸øµÄ³ÌÐò
//		if(counter == 0 && Re_buf[0] != 0x55) return;      //µÚ 0 ºÅÊý¾Ý²»ÊÇÖ¡Í·£¬Ìø¹ý
//		counter++; 
//		if(counter==11) //½ÓÊÕµ½ 11 ¸öÊý¾Ý
//		{ 
//			counter=0; //ÖØÐÂ¸³Öµ£¬×¼±¸ÏÂÒ»Ö¡Êý¾ÝµÄ½ÓÊÕ
//			sign=1;
//			for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//		}



//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
//	{
//		Re_buf[counter] = USART_ReceiveData(USART2);   //½ÓÊÕÊý¾Ý
//		if(counter == 0 && Re_buf[0] != 0x55) return;      //µÚ 0 ºÅÊý¾Ý²»ÊÇÖ¡Í·£¬Ìø¹ý
//		counter++; 
//		if(counter==11) //½ÓÊÕµ½ 11 ¸öÊý¾Ý
//		{ 
//			counter=0; //ÖØÐÂ¸³Öµ£¬×¼±¸ÏÂÒ»Ö¡Êý¾ÝµÄ½ÓÊÕ
//			he = 0;
//            for(t=0; t<10; t++)
//                he += Re_buf[t];             //½øÐÐÐ£Ñé
//			he = he%256;
//
//            if(Re_buf[10] == he && Re_buf[0] == 0x55)     //Èç¹ûÐ£ÑéÕýÈ·ÖÃÎ»sign=1;
//			{
//				for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//				sign = 1;        //½âÊÍÃüÁî
//			}
//
////			sign=1;
////			for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//		}    
//	}

 
   /*
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
     {
      Temp[counter] = USART_ReceiveData(USART2);   //½ÓÊÕÊý¾Ý
    
	  if(counter == 0 && Temp[0] != 0x55) return;      //µÚ 0 ºÅÊý¾Ý²»ÊÇÖ¡Í·£¬Ìø¹ý
      counter++; 
      if(counter==11) //½ÓÊÕµ½ 11 ¸öÊý¾Ý
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //ÖØÐÂ¸³Öµ£¬×¼±¸ÏÂÒ»Ö¡Êý¾ÝµÄ½ÓÊÕ
         sign=1;
      }    
   }
		 */



		
//		switch(counter)
//        {
//            case 0:
//				Re_buf[0] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                if(Re_buf[0] == 0x55)  counter = 1; 
//                else   counter = 0;   
//                break;
//            case 1:
//                Re_buf[1] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 2;
//                break;
//            case 2:
//                Re_buf[2] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 3;
//                break;
//            case 3:
//                Re_buf[3] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 4;
//                break;
//            case 4:
//                Re_buf[4] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 5;
//                break;
//            case 5:
//                Re_buf[5] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 6;
//                break;
//            case 6:
//                Re_buf[6] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 7;
//                break;
//            case 7:
//                Re_buf[7] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 8;
//                break;
//			case 8:
//                Re_buf[8] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 9;
//                break;
//			case 9:
//                Re_buf[9] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 10;
//                break;
//            case 10:
//                Re_buf[10] = USART_ReceiveData(USART2);	//½ÓÊÕÊý¾Ý
//                counter = 0;
//                he = 0;
//                for(t=0; t<10; t++)
//                    he += Re_buf[t];             //½øÐÐÐ£Ñé
//				//he = he%256;
//
//                if(Re_buf[10] == he && Re_buf[0] == 0x55)     //Èç¹ûÐ£ÑéÕýÈ·ÖÃÎ»sign=1;
//				{
//					for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//					sign = 1;        //½âÊÍÃüÁî
//				}
//
//                break;
//            default:  break;
//        }	 	
}



void USART3_IRQHandler(void)		   //´®¿Ú3È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
//  	{
//    	//buff_485[0] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //Èç¹û½ÓÊÕÍêÊý¾Ý£¬½ÓÊÕ×´Ì¬¹éÁã
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //½øÐÐÐ£Ñé
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//					{
//						//ming_ling_jie_shi();         //½âÊÍÃüÁî
//						if(buff_485[3] == 0x04 )	{feng = 0; LR_uart_buf = buff_485[4];CWW1 = 1;} //×ó ·äÃùÆ÷·¢Éú¡£buff_485[4]ÊÇÖ¸ÁîËÙ¶È
//						if(buff_485[3] == 0x02 )	{feng = 0; LR_uart_buf = buff_485[4];CWW1 = 0;} //ÓÒ ·äÃùÆ÷·¢Éú¡£buff_485[4]ÊÇÖ¸ÁîËÙ¶È
//						if(buff_485[3] == 0x08 )	{feng = 0; UD_uart_buf = buff_485[5];CWW2 = 1;} //ÉÏ ·äÃùÆ÷·¢Éú¡£buff_485[5]ÊÇÖ¸ÁîËÙ¶È
//						if(buff_485[3] == 0x10 )	{feng = 0; UD_uart_buf = buff_485[5];CWW2 = 0;} //ÏÂ ·äÃùÆ÷·¢Éú¡£buff_485[5]ÊÇÖ¸ÁîËÙ¶È
//						if(buff_485[3] == 0x0C )    //×óÉÏ
//						{
//							fang_xiang = 1;
//							CWW1 = 1;
//							CWW2 = 1;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x14 )    //×óÏÂ
//						{
//							fang_xiang = 2;
//							CWW1 = 1;
//							CWW2 = 0;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x0A )    //ÓÒÉÏ
//						{
//							fang_xiang = 3;
//							CWW1 = 0;
//							CWW2 = 1;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x12 )    //ÓÒÏÂ
//						{
//							fang_xiang = 4;
//							CWW1 = 0;
//							CWW2 = 0;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //·¢ËÍÍ£Ö¹ÐÅºÅ
//						{
//						 	feng = 1;	//¹Ø·äÃùÆ÷
//							LR_uart_buf = 0; //ËÙ¶ÈÖ¸ÁîÇåÁã
//							UD_uart_buf = 0;
//							fang_xiang = 0;
//						}
//					}
//					else  //·ñÔò²»ÕýÈ·
//					{
//					 	for(t = 0;t<9;t++)           //ÇåÁã
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(USART3);	//½ÓÊÕÊý¾Ý
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //½øÐÐÐ£Ñé
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//				{
//					//ming_ling_jie_shi();         //½âÊÍÃüÁî
//				}
//				else  //·ñÔò²»ÕýÈ·
//				{
//				 	for(t = 0;t<9;t++)           //ÇåÁã
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void EXTI15_10_IRQHandler(void)		   //Íâ²¿ÖÐ¶Ï10¡¾15:10¡¿ÖÐ¶Ï·þÎñº¯Êý
{
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET) 
//	{
//     //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
////		t = !t;	   //È¡·´±êÖ¾Î»
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //PB1¿ÚÊä³öµÍµçÆ½µãÁÁLED1
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ ¹Ø±ÕLED1
//
//		led_PB13 = ~led_PB13;	   //È¡·´
//	
//		 EXTI_ClearFlag(EXTI_Line10);			          //Çå³ýÖÐ¶Ï±êÖ¾£¨±ØÐë£©
//	     EXTI_ClearITPendingBit(EXTI_Line10);			  //Çå³ýÖÐ¶Ï¹ÒÆðÎ»
//	 }
}

void RTCAlarm_IRQHandler(void)		   //Áªµ½EXTIµÄRTCÄÖÖÓÖÐ¶Ï·þÎñº¯Êý
{
}

void USBWakeUp_IRQHandler(void)		   //Áªµ½EXTIµÄ´ÓUSB´ý»ú»½ÐÑÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM8_BRK_IRQHandler(void)		   //¶¨Ê±Æ÷8¶Ï¿ªÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM8_UP_IRQHandler(void)		   //¶¨Ê±Æ÷8¸üÐÂÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM8_TRG_COM_IRQHandler(void)	   //¶¨Ê±Æ÷8´¥·¢ºÍÍ¨ÐÅÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM8_CC_IRQHandler(void)		   //¶¨Ê±Æ÷8²¶»ñ±È½ÏÖÐ¶Ï·þÎñº¯Êý
{
}

void ADC3_IRQHandler(void)			   //ADC3È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void FSMC_IRQHandler(void)			   //FSMCÈ«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void SDIO_IRQHandler(void)			   //SDIOÈ«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void TIM5_IRQHandler(void)			   //¶¨Ê±Æ÷5È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(TIM5->SR & 0X0001)//Òç³öÖÐ¶Ï
//	{	
//	    //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
//		t = !t;	   //È¡·´±êÖ¾Î»
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ			    				   				     	    	
//	}				   
//	TIM5->SR &= ~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î»
}

void SPI3_IRQHandler(void)			   //SPI3È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void UART4_IRQHandler(void)			   //´®¿Ú4È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
//  	{
//    	//buff_485[0] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //Èç¹û½ÓÊÕÍêÊý¾Ý£¬½ÓÊÕ×´Ì¬¹éÁã
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //½øÐÐÐ£Ñé
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//					{
//						//ming_ling_jie_shi();         //½âÊÍÃüÁî
//						if(buff_485[3] == 0x08 )	feng = 0;  //ÉÏ ·äÃùÆ÷·¢Éú
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //·¢ËÍÍ£Ö¹ÐÅºÅ
//						{
//						 	feng = 1;	//¹Ø·äÃùÆ÷
//						}
//					}
//					else  //·ñÔò²»ÕýÈ·
//					{
//					 	for(t = 0;t<9;t++)           //ÇåÁã
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(UART4);	//½ÓÊÕÊý¾Ý
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //½øÐÐÐ£Ñé
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//				{
//					//ming_ling_jie_shi();         //½âÊÍÃüÁî
//				}
//				else  //·ñÔò²»ÕýÈ·
//				{
//				 	for(t = 0;t<9;t++)           //ÇåÁã
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void UART5_IRQHandler(void)			   //´®¿Ú5È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶ÏÓÐÐ§,Èô½ÓÊÕÊý¾Ý¼Ä´æÆ÷Âú
//  	{
//    	//buff_485[0] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //Èç¹û½ÓÊÕÍêÊý¾Ý£¬½ÓÊÕ×´Ì¬¹éÁã
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //½øÐÐÐ£Ñé
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//					{
//						//ming_ling_jie_shi();         //½âÊÍÃüÁî
//						if(buff_485[3] == 0x08 )	feng = 0;  //ÉÏ ·äÃùÆ÷·¢Éú
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //·¢ËÍÍ£Ö¹ÐÅºÅ
//						{
//						 	feng = 1;	//¹Ø·äÃùÆ÷
//						}
//					}
//					else  //·ñÔò²»ÕýÈ·
//					{
//					 	for(t = 0;t<9;t++)           //ÇåÁã
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(UART5);	//½ÓÊÕÊý¾Ý
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //½øÐÐÐ£Ñé
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //Èç¹ûÐ£ÑéÕýÈ· ÇÒµØÖ·Ò²ÕýÈ·
//				{
//					//ming_ling_jie_shi();         //½âÊÍÃüÁî
//				}
//				else  //·ñÔò²»ÕýÈ·
//				{
//				 	for(t = 0;t<9;t++)           //ÇåÁã
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void TIM6_IRQHandler(void)			   //¶¨Ê±Æ÷6È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(TIM6->SR & 0X0001)//Òç³öÖÐ¶Ï
//	{	
//	    //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
//		t = !t;	   //È¡·´±êÖ¾Î»
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ			    				   				     	    	
//	}				   
//	TIM6->SR &= ~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î»
}

void TIM7_IRQHandler(void)			   //¶¨Ê±Æ÷7È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
//	if(TIM7->SR & 0X0001)//Òç³öÖÐ¶Ï
//	{	
//	    //Ìí¼ÓÖÐ¶Ï´¦Àí³ÌÐò
////		t = !t;	   //È¡·´±êÖ¾Î»
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //Ò»¸öÎ»²Ù×÷PB1¿ÚÊä³öµÍµçÆ½µãÁÁLEDµÆ
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // Ò»¸öÎ»²Ù×÷ PB1¿ÚÊä³ö¸ßµçÆ½¹Ø±ÕLEDµÆ
//
//		//GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1)))); /* LED1 È¡·´ */	
//		
//		//led_PB13 = ~led_PB13;	   //È¡·´
//		
//		//CLK1 = ~CLK1;
//		//CLK2 = ~CLK2;
//		sao_miao_xian_shi();               //2msÉ¨ÃèÒ»´ÎÊýÂë¹Ü
//		
//		Led_T ++; //200msLED·¢¹â
//		
//	}				   
//	TIM7->SR &= ~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î»
}

void DMA2_Channel1_IRQHandler(void)	   //DMA2Í¨µÀ1È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA2_Channel2_IRQHandler(void)	   //DMA2Í¨µÀ2È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA2_Channel3_IRQHandler(void)	   //DMA2Í¨µÀ3È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

void DMA2_Channel4_5_IRQHandler(void)  //DMA2Í¨µÀ4ºÍDMA2Í¨µÀ5È«¾ÖÖÐ¶Ï·þÎñº¯Êý
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
