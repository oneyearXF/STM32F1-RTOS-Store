/* include */
#include "bsp_key.h"

/* KEY初始化 */
void KEY_IO_Config(void)
{
	/* 结构体声明 */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* 开启时钟总线 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	/* GPIOB -- PB0 PB1 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = KEY3_GPIO_PIN | KEY4_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* GPIOC -- PC4 PC5 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = KEY5_GPIO_PIN | KEY6_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* GPIOE -- PE7 PE8 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN | KEY2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/* 读取按键 */
uint8_t KeyScan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	/* 检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)  
	{	 
		/* 等待按键释放 */
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

/* 按键集合确认 */
uint8_t KeyRedify(uint8_t ID)
{
	/* 按键号选择 */
	if(ID == 1)
	{
		if(KeyScan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON) return 1;
	} else if(ID == 2)
	{
		if(KeyScan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON) return 2;
	} else if(ID == 3)
	{
		if(KeyScan(KEY3_GPIO_PORT, KEY3_GPIO_PIN) == KEY_ON) return 3;
	} else if(ID == 4)
	{
		if(KeyScan(KEY4_GPIO_PORT, KEY4_GPIO_PIN) == KEY_ON) return 4;
	} else if(ID == 5)
	{
		if(KeyScan(KEY5_GPIO_PORT, KEY5_GPIO_PIN) == KEY_ON) return 5;
	} else if(ID == 6)
	{
		if(KeyScan(KEY6_GPIO_PORT, KEY6_GPIO_PIN) == KEY_ON) return 6;
	}
	
	return 0;
}
/* include */













