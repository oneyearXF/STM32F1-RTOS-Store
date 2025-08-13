#ifndef __bsp_PWM_H
#define __bsp_PWM_H

/* -------------------------------------------------------------------------- */
/* include */
#include "header_common.h"

/* -------------------------------------------------------------------------- */
/* define */
#define CHANNEL_1			1
#define CHANNEL_2			2
#define CHANNEL_3			3
#define CHANNEL_4			4
/* -------------------------------------------------------------------------- */
/* º¯ÊýÉùÃ÷ */
void MotorPWM_Init(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, uint8_t CHx, int16_t psc, int16_t arr);
void PWM_SetCompare(TIM_TypeDef* TIMx, uint8_t INx, uint16_t Compare);
/* -------------------------------------------------------------------------- */
#endif
