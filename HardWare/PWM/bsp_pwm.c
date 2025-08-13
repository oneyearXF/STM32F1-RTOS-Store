/* include */
#include "bsp_pwm.h"

/**
  * @brief  对定时器输出PWM波的引脚进行初始化
  * @param  传入参数，psc arr
  * @retval 无返回值
  */
void MotorPWM_Init(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, uint8_t CHx, int16_t psc, int16_t arr)
{
	/* 结构体声明 */
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef 		TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/* 时钟总线 */
	if(TIMx == TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if(TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if(TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if(TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if(TIMx == TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	
	if(TIMx == TIM1 || TIMx == TIM8)
		TIM_DeInit(TIMx);
	else 
		TIM_InternalClockConfig(TIMx);
	
	/* 设置时基单元 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = arr - 1;		//ARR
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;		//PSC
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	/* PWM设置 */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	
	/* 通道初始化 */
	TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	TIM_OC2Init(TIMx, &TIM_OCInitStructure);
	TIM_OC3Init(TIMx, &TIM_OCInitStructure);
	TIM_OC4Init(TIMx, &TIM_OCInitStructure);

	/* 使能 */
	if(TIMx == TIM1 || TIMx == TIM8)
	{
		TIM_CtrlPWMOutputs(TIMx, ENABLE);
		TIM_ARRPreloadConfig(TIMx, ENABLE);
	}
	TIM_Cmd(TIMx, ENABLE);
}

/**
  * @brief  对定时器X通道X的占空比进行设置调整
  * @param  传入参数  占空比为多少
  * @retval 无返回值
  */
void PWM_SetCompare(TIM_TypeDef* TIMx, uint8_t INx, uint16_t Compare)
{
	/* 限幅 */
	if(Compare >= PWMLimit)	Compare = PWMLimit;
	
	/* 设置占空比 */
	if(INx == CHANNEL_1)		TIM_SetCompare1(TIMx, Compare);
	else if(INx == CHANNEL_2)	TIM_SetCompare2(TIMx, Compare);
	else if(INx == CHANNEL_3)	TIM_SetCompare3(TIMx, Compare);
	else if(INx == CHANNEL_4)	TIM_SetCompare4(TIMx, Compare);
}
