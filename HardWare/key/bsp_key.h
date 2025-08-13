/* USER CODE BEGIN Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#ifdef __cplusplus
extern "C" {
#endif
/* --------------------------------------------------------------------------- */	
/* include*/
#include "header_common.h"
/* --------------------------------------------------------------------------- */
/* define */
/* Òý½ÅÅäÖÃ */
#define KEY1_GPIO_PORT		GPIOE
#define KEY1_GPIO_PIN		GPIO_Pin_8
	
#define KEY2_GPIO_PORT		GPIOE
#define KEY2_GPIO_PIN		GPIO_Pin_7
	
#define KEY3_GPIO_PORT		GPIOB
#define KEY3_GPIO_PIN		GPIO_Pin_0
	
#define KEY4_GPIO_PORT		GPIOB
#define KEY4_GPIO_PIN		GPIO_Pin_1
	
#define KEY5_GPIO_PORT		GPIOC
#define KEY5_GPIO_PIN		GPIO_Pin_4

#define KEY6_GPIO_PORT		GPIOC
#define KEY6_GPIO_PIN		GPIO_Pin_5
/* °´¼ü×´Ì¬ */
#define KEY_ON				1
#define KEY_OFF				0

#define KEY1				1
#define KEY2				2
#define KEY3				3
#define KEY4				4
#define KEY5				5
#define KEY6				6
/* --------------------------------------------------------------------------- */	
/* º¯ÊýÉùÃ÷ */
void KEY_IO_Config(void);
uint8_t KeyScan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t KeyRedify(uint8_t ID);
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif
#endif /* __KEY_H */
/* USER CODE BEGIN Header */
/* Define to prevent recursive inclusion -------------------------------------*/





