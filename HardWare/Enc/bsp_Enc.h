/* USER CODE BEGIN Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bsp_Enc_H__
#define __bsp_Enc_H__
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif
	
/* include*/
#include "header_common.h"
/* --------------------------------------------------------------------------- */
/* define */
#define MOTOR1_ENC		TIM2
#define MOTOR2_ENC		TIM3
/* --------------------------------------------------------------------------- */
/* typedef */

/* --------------------------------------------------------------------------- */
/* º¯ÊýÉùÃ÷ */
void Enc_Init(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIOx, uint16_t GPIO1, uint16_t GPIO2);
int16_t EncValue_Get(TIM_TypeDef* TIMx);
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif
#endif /* __ENC_H */


