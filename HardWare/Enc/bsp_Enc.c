/* include */
#include "bsp_Enc.h"                  

/* TIM2_CH1 CH2 ==== PA0 PA1 */
/* TIM3_CH1 CH2 ==== PA6 PA7 */

/* ENC初始化 */
void Enc_Init(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIOx, uint16_t GPIO1, uint16_t GPIO2)
{
	/* 结构体声明 */
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	/* 时钟总线 */
	if(TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
		
	/* GPIO */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO1 | GPIO2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);		
		
	/* 时基单元 */
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	/* 配置时基单元 */
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure); 	
	
	/* 先给结构体赋值一个默认值，因为下方的结构体赋值是不完整的	 */
	TIM_ICStructInit(&TIM_ICInitStructure);	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	/* 将数据写入到通道1 */
	TIM_ICInit(TIMx, &TIM_ICInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	/* 将数据写入到通道2 */
	TIM_ICInit(TIMx, &TIM_ICInitStructure);		
	
	TIM_EncoderInterfaceConfig(TIMx, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	/* 使能 */
	TIM_Cmd(TIMx, ENABLE);
}

/**
  * @brief  获取编码值
  * @param  定时器X
  * @retval 无
  */
int16_t EncValue_Get(TIM_TypeDef* TIMx)
{
	/* 变量声明 */
	int16_t Temp;
	
	/* 获取编码值 */
	Temp = TIM_GetCounter(TIMx);
	/* 清零 */
	TIM_SetCounter(TIMx, 0);
	
	return Temp;
}

