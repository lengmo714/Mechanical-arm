#include "dma.h"

 u8 DMA1_MEM_LEN;						//DMA缓存大小
 
//DMA1的各通道配置
//从外设模式->存储器/16位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx		   //cpar:外设地址 //cmar:存储器地址//cndtr:数据传输量
void MyDMA_Init(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{	  
  DMA_InitTypeDef DMA_InitStructure;

 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA时钟
	
  DMA_DeInit(DMA_CHx);   															//将DMA的通道1寄存器重设为缺省值

	DMA1_MEM_LEN=cndtr;																	//通道数据长度
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  														//DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  																//DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 														//数据传输方向，从外设发送到内存  DMA_CCRX位4
	DMA_InitStructure.DMA_BufferSize = cndtr;  																		//DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 							//外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  											//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  	//外设数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 					//内存数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 															//工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;														//DMA通道 x拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  																//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  																			

	//DMA_Cmd(DMA_CHx, ENABLE);				//使能DMA通道

} 
