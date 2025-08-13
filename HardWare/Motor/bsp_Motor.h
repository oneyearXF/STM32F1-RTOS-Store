/* USER CODE BEGIN Header */
/* Define to prevent recursive inclusion ------------------------------------- */
#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif
	
/* include*/
#include "header_common.h"
/* --------------------------------------------------------------------------- */
/* define */
/* 引脚 */
#define MOTOR_PORT			GPIOD
#define MOTOR_DIR_1			GPIO_Pin_0
#define MOTOR_DIR_2			GPIO_Pin_1
#define MOTOR_DIR_3			GPIO_Pin_2
#define MOTOR_DIR_4			GPIO_Pin_3
/* 电机编号 */
#define ENCMOTOR1			1
#define ENCMOTOR2			2
/* 通道 */
#define ENCMOTOR1_CH		CHANNEL_1
#define ENCMOTOR2_CH		CHANNEL_2
#define MOTOR_TIM			TIM8
/* 满占空比 */
#define PWMLimit			7200
/* --------------------------------------------------------------------------- */
/* typedef */

/* --------------------------------------------------------------------------- */
/* 函数声明 */
void MotorDirIO_Init(void);
void ControlMotor(int16_t MotorX, int16_t CHx, int Speed);
void Motor_switch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin1, uint16_t GPIO_Pin2, int16_t CHx, int Speed);
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif
#endif /* __MOTOR_H */
