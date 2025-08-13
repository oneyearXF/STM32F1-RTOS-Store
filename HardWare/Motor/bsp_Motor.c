/* include */
#include "bsp_Motor.h"                

/**
  * @brief  控制电机方向引脚初始化
  * @param  无
  * @retval 无
  */
void MotorDirIO_Init(void)
{
	/* 结构体声明 */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 时钟总线 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_Pin = MOTOR_DIR_1 | MOTOR_DIR_2 | MOTOR_DIR_3 | MOTOR_DIR_4;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   					
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 					
	GPIO_Init(MOTOR_PORT, &GPIO_InitStructure);									
}

/**
  * @brief  设置速度
  * @param  int16_t MotorX, int16_t CHx, int Speed
  * @retval 无
  */
void ControlMotor(int16_t MotorX, int16_t CHx, int Speed)
{
	if	   (MotorX == ENCMOTOR1)	
		Motor_switch(MOTOR_PORT, MOTOR_DIR_1, MOTOR_DIR_2, CHx, Speed);
	else if(MotorX == ENCMOTOR2)	
		Motor_switch(MOTOR_PORT, MOTOR_DIR_3, MOTOR_DIR_4, CHx, Speed);
}

/**
  * @brief  正反转控制
  * @param  GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin1, uint16_t GPIO_Pin2, int16_t CHx, int Speed
  * @retval 无
  */
void Motor_switch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin1, uint16_t GPIO_Pin2, int16_t CHx, int Speed)
{
	/* 正转 */
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOx, GPIO_Pin1);
		GPIO_ResetBits(GPIOx, GPIO_Pin2);
		/* 设置占空比 */
		PWM_SetCompare(MOTOR_TIM, CHx, Speed);
	}
	/* 反转 */
	else if(Speed < 0)
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin1);
		GPIO_SetBits(GPIOx, GPIO_Pin2);
		/* 设置占空比 */
		PWM_SetCompare(MOTOR_TIM, CHx, -Speed);
	}
}



