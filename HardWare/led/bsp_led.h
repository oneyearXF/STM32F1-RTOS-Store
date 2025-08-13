#ifndef __BSP_LED_H
#define	__BSP_LED_H

/* include */
#include "header_common.h"
/* ----------------------------------------------------------------- */
/* define */
/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define LED_GPIO_PORT    	GPIOE			            /* GPIO端口 */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOE		/* GPIO端口时钟 */
#define LED1_GPIO_PIN		GPIO_Pin_10			        
#define LED2_GPIO_PIN		GPIO_Pin_11	
#define LED3_GPIO_PIN		GPIO_Pin_12

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 使用标准的固件库控制IO*/
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);\
				else	\
					GPIO_ResetBits(LED_GPIO_PORT, LED1_GPIO_PIN)
#define LED2(a)	if (a)	\
					GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);\
				else	\
					GPIO_ResetBits(LED_GPIO_PORT, LED2_GPIO_PIN)
#define LED3(a)	if (a)	\
					GPIO_SetBits(LED_GPIO_PORT, LED3_GPIO_PIN);\
				else	\
					GPIO_ResetBits(LED_GPIO_PORT, LED3_GPIO_PIN)

/* 定义控制IO的宏 */
#define LED1_OFF		   GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
#define LED1_ON			   GPIO_ResetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
#define LED2_OFF		   GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);
#define LED2_ON			   GPIO_ResetBits(LED_GPIO_PORT, LED2_GPIO_PIN);
#define LED3_OFF		   GPIO_SetBits(LED_GPIO_PORT, LED3_GPIO_PIN);
#define LED3_ON			   GPIO_ResetBits(LED_GPIO_PORT, LED3_GPIO_PIN);

/* ----------------------------------------------------------------- */
/* 函数声明 */
void LED_GPIO_Config(void);
void Tracking_GPIO_Config(void);
/* ----------------------------------------------------------------- */
#endif /* __LED_H */
