#include "RS485.h"


u8 buff_485[9] = {0,0,0,0,0,0,0,0,0};  //接收485信号缓存区
u8 uart_1 = 0;                         //串口1接收标志
u8 di_zhi = 1;		                   //设备地址





/****** 串口1初始化 *************************************************/
void USART1_Config(void)		//初始化 配置USART1
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 第1步：打开GPIO和USART部件的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//打开串口复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //打开PC端口时钟
	USART_DeInit(USART1);  //复位串口1

	/*配置485芯片的DE和RE引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //选定哪个IO口 现选定PC4口和PC5口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //设定IO口的输出速度为10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //设定IO口的模式为推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //初始化GPIOC

	/* 第2步：将USART1 Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			   //串口1发送脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		   //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //输出速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //初始化GPIOA
														  
	/* 第3步：将USART Rx的GPIO配置为浮空输入模式   */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			   //串口1接收脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //初始化GPIOA

	/* 第4步：配置USART1参数  */
	USART_InitStructure.USART_BaudRate             = 2400;							 //波特率设置：2400
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 //数据位数设置：8位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 //停止位设置：1位
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; //硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 //接收与发送都使能
	USART_Init(USART1, &USART_InitStructure);										 //初始化USART1

    /* 若接收数据寄存器满，则产生中断 */
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  // 使能指定的USART1发送中断 ；
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 使能指定的USART1接收中断 ；

	/* 第5步：使能 USART1， 配置完毕 */
	USART_Cmd(USART1, ENABLE);							   //使能 USART1

    /* 如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART1, USART_FLAG_TC);                //清串口1发送标志
	
}

/****** 串口2初始化 *************************************************/
void USART2_Config(void)   //初始化 配置USART2
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 USART2 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//打开串口复用时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //打开PA端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //打开PC端口时钟	 
	/*配置485芯片的DE和RE引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //选定哪个IO口 现选定PC4口和PC5口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //设定IO口的输出速度为10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //设定IO口的模式为推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //初始化GPIOC

	/* USART2 使用IO端口TX发射配置 */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //选定哪个IO口 现选定PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //设定IO口的输出速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);    				  //初始化GPIOA
	/* USART2 使用IO端口RX接收配置 */														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //选定哪个IO口 现选定PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);                    //初始化GPIOA
	  
	/* USART2 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 2400;	                    //波特率设置：2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收与发送都使能
	USART_Init(USART2, &USART_InitStructure);                       //初始化USART2
	
    /*使能串口2的发送和接收中断*/
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         // 使能指定的USART2接收中断 ；
	USART_Cmd(USART2, ENABLE);                             // USART2使能

	/* 如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART2, USART_FLAG_TC);                //清串口2发送标志

	Clr_DE;		 //DE清零准备接收
	Clr_RE; 	 //RE清零准备接收  
}

/****** 串口3初始化 *************************************************/
void USART3_Config(void)   //初始化 配置USART3
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 USART3 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//打开串口复用时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //打开PB端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //打开PC端口时钟	 
	/*配置485芯片的DE和RE引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //选定哪个IO口 现选定PC4口和PC5口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //设定IO口的输出速度为10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //设定IO口的模式为推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //初始化GPIOC

	/* USART3 使用IO端口配置 */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				  //选定哪个IO口 现选定PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //设定IO口的输出速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);    				  //初始化GPIOB
															  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //选定哪个IO口 现选定PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);                    //初始化GPIOA
	  
	/* USART3 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 2400;	                    //波特率设置：2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收与发送都使能
	USART_Init(USART3, &USART_InitStructure);                       //初始化USART3
	
    /*使能串口3的发送和接收中断*/
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         // 使能指定的USART1接收中断 ；
	USART_Cmd(USART3, ENABLE);                             // USART3使能

	/* 如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART3, USART_FLAG_TC);                //清串口3发送标志

	Clr_DE;		 //DE清零准备接收
	Clr_RE; 	 //RE清零准备接收  
}

/****** 串口4初始化 *************************************************/
void UART4_Config(void)   //初始化 配置USART4
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 UART4 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//打开串口复用时钟
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //打开PB端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //打开PC端口时钟	 
	/*配置485芯片的DE和RE引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //选定哪个IO口 现选定PC4口和PC5口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //设定IO口的输出速度为10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //设定IO口的模式为推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //初始化GPIOC

	/* UART4 使用IO端口TX发射配置 */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				  //选定哪个IO口 现选定PC10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //设定IO口的输出速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);    				  //初始化GPIOC
	/* UART4 使用IO端口RX接收配置 */														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //选定哪个IO口 现选定PC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);                    //初始化GPIOC
	  
	/* UART4 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 2400;	                    //波特率设置：2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收与发送都使能
	USART_Init(UART4, &USART_InitStructure);                       //初始化UART4
	
    /*使能串口4的发送和接收中断*/
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);         // 使能指定的UART4接收中断 ；
	USART_Cmd(UART4, ENABLE);                             // UART4使能

	/* 如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(UART4, USART_FLAG_TC);                //清串口4发送标志

	Clr_DE;		 //DE清零准备接收
	Clr_RE; 	 //RE清零准备接收  
}

/****** 串口5初始化 *************************************************/
void UART5_Config(void)   //初始化 配置UART5
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 UART5 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//打开串口复用时钟
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //打开PB端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //打开PC端口时钟	 
	/*配置485芯片的DE和RE引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //选定哪个IO口 现选定PC4口和PC5口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //设定IO口的输出速度为10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //设定IO口的模式为推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //初始化GPIOC

	/* UART5 使用IO端口TX发射配置 */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				  //选定哪个IO口 现选定PC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //设定IO口的输出速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);    				  //初始化GPIOC
	/* UART5 使用IO端口RX接收配置 */														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //选定哪个IO口 现选定PD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);                    //初始化GPIOC
	  
	/* UART5 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 2400;	                    //波特率设置：2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收与发送都使能
	USART_Init(UART5, &USART_InitStructure);                       //初始化UART5
	
    /*使能串口5的发送和接收中断*/
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);         // 使能指定的UART5接收中断 ；
	USART_Cmd(UART5, ENABLE);                             // UART5使能

	/* 如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(UART5, USART_FLAG_TC);                //清串口5发送标志

	Clr_DE;		 //DE清零准备接收
	Clr_RE; 	 //RE清零准备接收  
}

void RS485_SendByte(unsigned char SendData)	  //发送一个字节数据
{	   
        Set_DE;		 //DE置位准备发送
	    Set_RE;		 //RE置位准备发送
		//DelayNuS(5000);
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		//DelayNuS(5000);
	    Clr_DE;		 //DE清零准备接收
	    Clr_RE; 	 //RE清零准备接收   
}  



