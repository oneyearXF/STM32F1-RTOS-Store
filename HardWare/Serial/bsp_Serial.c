/* include */
#include "bsp_serial.h"

#if USART1_ENABLE
    uint8_t usart1SendBuf[USART_SEND_BUF_SIZE+1];
	uint8_t usart1RecvBuf[USART_RECV_BUF_SIZE+1];
	RingBufferTypeDef usart1SendRingBuf;
	RingBufferTypeDef usart1RecvRingBuf;
	Usart_DataTypeDef usart1;
	 
#endif

#if USART2_ENABLE
    uint8_t usart2SendBuf[USART_SEND_BUF_SIZE+1];
	uint8_t usart2RecvBuf[USART_RECV_BUF_SIZE+1];
	RingBufferTypeDef usart2SendRingBuf;
	RingBufferTypeDef usart2RecvRingBuf;
	Usart_DataTypeDef usart2;
#endif

#if USART3_ENABLE
    uint8_t usart3SendBuf[USART_SEND_BUF_SIZE+1];
	uint8_t usart3RecvBuf[USART_RECV_BUF_SIZE+1];
	RingBufferTypeDef usart3SendRingBuf;
	RingBufferTypeDef usart3RecvRingBuf;
	Usart_DataTypeDef usart3;
#endif

void Usart_Init(void){
    //GPIO Port Settings
    GPIO_InitTypeDef GPIO_InitStructure;
    // Serial Port Configuration Structure
    USART_InitTypeDef USART_InitStructure;
    // External Interrupt Structure
    NVIC_InitTypeDef NVIC_InitStructure;

    #if USART1_ENABLE
        // Assignment structure usart pointer
        usart1.pUSARTx = USART1;
		// Initialization buffer (ring queue)
		RingBuffer_Init(&usart1SendRingBuf,  USART_SEND_BUF_SIZE, usart1SendBuf);
		RingBuffer_Init(&usart1RecvRingBuf, USART_RECV_BUF_SIZE,  usart1RecvBuf);
		usart1.recvBuf = &usart1RecvRingBuf;
		usart1.sendBuf = &usart1SendRingBuf;
	
		// usart1.recvBuf = RingBuffer_Init(USART_RECV_BUF_SIZE);
		// usart1.sendBuf = RingBuffer_Init(USART_SEND_BUF_SIZE);
        // Enable USART Clock
        USART1_APBxClkCmd(USART1_CLK, ENABLE);
        // Enable GPIO Clock
        USART1_GPIO_APBxClkCmd(USART1_GPIO_CLK, ENABLE);
        // Configure the transmit pin of the serial USART port
        GPIO_InitStructure.GPIO_Pin = USART1_TX_GPIO_PIN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//Multiplexing Push-Pull Outputs
        GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

        // Configure the receive pins of the serial USART port
        GPIO_InitStructure.GPIO_Pin = USART1_RX_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//float input
        GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure); 
		
				//USART Initialization Settings
        USART_InitStructure.USART_BaudRate = USART1_BAUDRATE;//serial port baud rate
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//Word length 8-bit data format
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//A stop bit.
        USART_InitStructure.USART_Parity = USART_Parity_No;//No parity bit
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//No hardware data flow control
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and Receiving Mode
		
        // NVIC Configuring Serial Port External Interrupts
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Nested Vector Interrupt Controller Group Selection
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//preemptive prioritization
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//sub-priority
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ Channel Enable
        NVIC_Init(&NVIC_InitStructure);	//Initialize the NVIC registers according to the specified parameters
        

        USART_Init(USART1, &USART_InitStructure);

        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		// Enable Serial Port
        USART_Cmd(USART1, ENABLE);
    #endif
    #if USART2_ENABLE
        usart2.pUSARTx = USART2;

		RingBuffer_Init(&usart2SendRingBuf,  USART_SEND_BUF_SIZE, usart2SendBuf);
		RingBuffer_Init(&usart2RecvRingBuf, USART_RECV_BUF_SIZE,  usart2RecvBuf);
		usart2.recvBuf = &usart2RecvRingBuf;
		usart2.sendBuf = &usart2SendRingBuf;
		

        USART2_APBxClkCmd(USART2_CLK, ENABLE);

        USART2_GPIO_APBxClkCmd(USART2_GPIO_CLK, ENABLE);

        GPIO_InitStructure.GPIO_Pin = USART2_TX_GPIO_PIN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
        GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);


        GPIO_InitStructure.GPIO_Pin = USART2_RX_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);


        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
        NVIC_Init(&NVIC_InitStructure);	
        
        
        USART_InitStructure.USART_BaudRate = USART2_BAUDRATE;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
        
        USART_Init(USART2, &USART_InitStructure);
        
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		
        USART_Cmd(USART2, ENABLE);
    #endif

    #if USART3_ENABLE
		// 赋值结构体usart指针
        usart3.pUSARTx = USART3;
        // 初始化缓冲区(环形队列)
		RingBuffer_Init(&usart3SendRingBuf,  USART_SEND_BUF_SIZE, usart3SendBuf);
		RingBuffer_Init(&usart3RecvRingBuf, USART_RECV_BUF_SIZE,  usart3RecvBuf);
		usart3.recvBuf = &usart3RecvRingBuf;
		usart3.sendBuf = &usart3SendRingBuf;
		
        // 使能USART时钟
        USART3_APBxClkCmd(USART3_CLK, ENABLE);
        // 使能GPIO时钟
        USART3_GPIO_APBxClkCmd(USART3_GPIO_CLK, ENABLE);
        // 配置串口USART的发送管脚 TX
        GPIO_InitStructure.GPIO_Pin = USART3_TX_GPIO_PIN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
        GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

        // 配置串口USART的接收管脚 RX
        GPIO_InitStructure.GPIO_Pin = USART3_RX_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
        GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);

        // Usart NVIC 配置串口外部中断
        NVIC_InitStructure.NVIC_IRQChannel = 39;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
        NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
        
        //USART 初始化设置
        USART_InitStructure.USART_BaudRate = USART3_BAUDRATE;//串口波特率
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
        USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
        // 初始化串口
        USART_Init(USART3, &USART_InitStructure);
        //开启串口接收中断 IT: Interupt
        USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		// 使能串口
        USART_Cmd(USART3, ENABLE);
    #endif

}

/* Send a single byte */
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* Send a byte to USART */
    USART_SendData(pUSARTx, ch);
	/* Wait for transmit register to be empty */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/* Send 8-bit byte stream */
void Usart_SendByteArr(USART_TypeDef *pUSARTx, uint8_t *byteArr, uint16_t size){
    uint16_t bidx;
    for (bidx=0; bidx<size; bidx++){
        Usart_SendByte(pUSARTx, byteArr[bidx]);
    }
    /* Wait for transmit register to be empty */
    // while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/* Send string */
void Usart_SendString(USART_TypeDef *pUSARTx, char *str){
    uint16_t sidx=0;
    do
    {
        Usart_SendByte(pUSARTx, (uint8_t)(*(str + sidx)));
        sidx++;
    } while(*(str + sidx) != '\0');

}

// Sends out the entire contents of the serial port send buffer
void Usart_SendAll(Usart_DataTypeDef *usart){
	uint8_t value;
	while(RingBuffer_GetByteUsed(usart->sendBuf)){
		value = RingBuffer_Pop(usart->sendBuf);
		// printf("Usart_SendAll pop: %d", value);
		Usart_SendByte(usart->pUSARTx, value);
	}
}
#if USART1_ENABLE
    // Define the serial port interrupt handler function
    void USART1_IRQHandler(void){
        uint8_t ucTemp;
	    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	    {
			// Read a character from the serial port
            ucTemp = USART_ReceiveData(USART1);
			// New characters are added to the ring buffer queue of the serial port
			RingBuffer_Push(usart1.recvBuf, ucTemp);
        }
    }
	

#endif
	
#if USART2_ENABLE
	// Define the serial port interrupt handler function
    void USART2_IRQHandler(void){
        uint8_t ucTemp;
	    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	    {
			// Read a character from the serial port
            ucTemp = USART_ReceiveData(usart2.pUSARTx);
			// New characters are added to the ring buffer queue of the serial port
            RingBuffer_Push(usart2.recvBuf, ucTemp);
        }
    }
#endif

#if USART3_ENABLE
    void USART3_IRQHandler(void){
        uint8_t ucTemp;
	    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
	    {
			// Read a character from the serial port
            ucTemp = USART_ReceiveData(usart3.pUSARTx);
			// Neue Zeichen werden in die Ringpuffer-Warteschlange der seriellen Schnittstelle eingefügt
            RingBuffer_Push(usart3.recvBuf, ucTemp);
        }
    }
#endif
	
/* 变量声明 */
uint8_t Serial_RxFlag_X, Serial_RxFlag_Y, Serial_RxFlag_ColorPicture;

/* USART1---PA9 PA10 */
/* USART2---PA2 PA3  */
/* USART3---PB10 PB11 */
/* UART4----PC10 PC11 */
/**
  * @brief  USART初始化
  * @param  无
  * @retval 无
  */
void MyUSART_Config(USART_TypeDef* USARTx, uint16_t GPIO_TX, uint16_t GPIO_RX, GPIO_TypeDef* GPIOx)
{
	/* 结构体声明 */
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 时钟总线 */
	if(USARTx == USART1)		/* USART1 */
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	} else if(USARTx == USART2) /* USART2 */
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	} else if(USARTx == USART3) /* USART3 */
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	} else if(USARTx == UART4)  /* UART4 */
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	}
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);	
	
	/* USART设置 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USARTx, &USART_InitStructure);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	
	/* 中断初始化 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	if(USARTx == USART1)		NVIC_InitStructure.NVIC_IRQChannel = 37;
	else if(USARTx == USART2) 	NVIC_InitStructure.NVIC_IRQChannel = 38;
	else if(USARTx == USART3)	NVIC_InitStructure.NVIC_IRQChannel = 39;
	else if(USARTx == UART4)	NVIC_InitStructure.NVIC_IRQChannel = 52;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	/* 使能USART */
	USART_Cmd(USARTx, ENABLE); 
}

/**
  * @brief  发送数据
  * @param  需传输的数据, flag-对哪个串口进行发送（1， 2， 3）
  * @retval 无
  */
void Serial_SentData(uint8_t Data, int16_t flag)
{
	if(flag == USART1_FLAG){
		USART_SendData(USART1, Data);//TX发送数据
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
	
	if(flag == USART2_FLAG){
		USART_SendData(USART2, Data);//TX发送数据
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
	
	if(flag == USART3_FLAG){
		USART_SendData(USART3, Data);//TX发送数据
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	}
}
	
/**
  * @brief  发送二位数以上的数据 如：11  111
  * @param  数据所在的数组, 数组长度, flag-对哪个串口进行发送（1， 2， 3）
  * @retval 无
  */
void Serial_SentMath(uint8_t math[], uint8_t length, int16_t flag)
{
	uint8_t i;
	
	for(i = 0; i < length; i++)
	{
		if(flag == USART1_FLAG)
			Serial_SentData(math[i], 1);
		if(flag == USART2_FLAG)
			Serial_SentData(math[i], 2);
		if(flag == USART3_FLAG)
			Serial_SentData(math[i], 3);
	}
}

/**
  * @brief  算出多少的多少次方  如 5 的 3 次方
  * @param  x-底数, y-几次方
  * @retval 无
  */
uint32_t Serial_Pow(uint8_t x, uint8_t y)
{	
	return (pow(x, y));
}

/**
  * @brief  发送较大数据 如：10的5次方
  * @param  无
  * @retval 无
  */
void Serial_SentNum(uint8_t Number, uint8_t length, int16_t flag)
{
	uint32_t i;
	
	for(i = 0; i < length; i++)
	{
		if(flag == USART1_FLAG)
			Serial_SentData(Number / Serial_Pow(10, length - 1 - i) % 10 + '0', 1);
		if(flag == USART2_FLAG)
			Serial_SentData(Number / Serial_Pow(10, length - 1 - i) % 10 + '0', 2);
		if(flag == USART3_FLAG)
			Serial_SentData(Number / Serial_Pow(10, length - 1 - i) % 10 + '0', 3);
	}
}

/**
  * @brief  发送字符串
  * @param  字符串, flag-对哪个串口进行发送（1， 2， 3）
  * @retval 无
  */
void Serial_SentString(char *string, int16_t flag)
{	
	while(*string != '\0')
	{
		if(flag == USART1_FLAG){
			Serial_SentData(*string, 1);}
		if(flag == USART2_FLAG){
			Serial_SentData(*string, 2);}
		if(flag == USART3_FLAG){
			Serial_SentData(*string, 3);}
		string++;
	}
}


/**
  * @brief  判断是否接收到了数据
  * @param  无
  * @retval 无
  */
uint8_t Serial_GetRxData_X(void)
{
	if (Serial_RxFlag_X == 1)
	{
		Serial_RxFlag_X = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t Serial_GetRxData_Y(void)
{
	if(Serial_RxFlag_Y == 1)
	{
		Serial_RxFlag_Y = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t Serial_GetRxData_ColorPicture(void)
{
	if(Serial_RxFlag_ColorPicture == 1)
	{
		Serial_RxFlag_ColorPicture = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

///**
//  * @brief  串口1的中断
//  * @param  无
//  * @retval 接收数据时进入中断
//  */
//void USART1_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		/* 用户程序 */
//		
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}

///**
//  * @brief  串口2的中断
//  * @param  无
//  * @retval 接收数据时进入中断
//  */
//void USART2_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
//	{
//		/* 用户程序 */
//		
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	}
//}

///**
//  * @brief  串口3的中断
//  * @param  无
//  * @retval 接收数据时进入中断
//  */
//void USART3_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
//	{
//		/* 用户程序 */
//		
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//	}
//}

///* 串口重定向 */
//int fputc(int ch, FILE *f)
//{  
//	USART_SendData(UART4, ch); 								/* 发送数据 */
//	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);/* 等待发送完成 */

//	return ch;

//}
