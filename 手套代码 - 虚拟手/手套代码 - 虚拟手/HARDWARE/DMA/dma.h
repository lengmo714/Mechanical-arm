#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"

//≈‰÷√DMA1_CHx
void MyDMA_Init(DMA_Channel_TypeDef *DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
		   
#endif
