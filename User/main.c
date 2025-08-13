/* include */
#include "header_common.h"
/* -------------------------------------------------------------------------- */
/* 变量声明 */
float Angle_Up = 93.8, Angle_Down = 40;
float ControlAngle_Up = 93.8, ControlAngle_Down = 40;
int FLAG = 0;

/* 结构体声明 */
GimbalController gimbal_Circle;
TriangleController triangle;
/* -------------------------------------------------------------------------- */

/**
  * @brief  主函数
  * @param  None
  * @retval None
  */
int main(void)
{	
/* -------------------------------------------------------------------------- */
	/* 硬件初始化 */
	BSP_Init();			
	
	/* 起始位置 */
	ControlFSUSServoAngle(SERVO_UP, Angle_Up, 2000);
	ControlFSUSServoAngle(SERVO_DOWN, Angle_Down, 2000);
	TriangleController_Init(&triangle, 60.0f, 
                          39.8f, 99.3f,   // 顶点1
                          31.2f, 87.4f, // 顶点2
                          47.0f, 87.4f); // 顶点3
	GimbalController_Init(&gimbal_Circle, Angle_Down, Angle_Up, 10.0f, 500.0f);
	
	/* 任务初始化 */
	Task_Init();		
/* -------------------------------------------------------------------------- */   
    while(1);  
}

/**
  * @brief  按键任务
  * @param  无
  * @retval 无
  */
void KEY_Task(void* parameter)
{	
	
	
	/* 主循环 */
    while (1)
    {
		if(KeyRedify(KEY1)){
			FLAG = 1;
		} else if(KeyRedify(KEY2)){
			FLAG = 0;
			/* 阻尼模式 */
			ControlFSUSServoDamping(SERVO_UP);
			ControlFSUSServoDamping(SERVO_DOWN);
		}
		vTaskDelay(10);
    }
}

/**
  * @brief  OLED任务
  * @param  无
  * @retval 无
  */
void OLED_Task(void* parameter)
{		
	
	/* 主循环 */
    while (1)
    {		
		/* 显示数据 */
		OLED_ShowString(1, 1, "LJF");
		OLED_ShowNum(4, 1, FLAG, 2);
		
		/* 打印信息 */
		printf("%02f,%02f\n", Angle_Up, Angle_Down);
		
		vTaskDelay(10);
    }
}

/**
  * @brief  定时器
  * @param  无
  * @retval 无
  */
void Timer_Callback(void* parameter)
{
	/* -------------- 用户程序 -------------- */
	
	/* 读取角度 */
	QueryFSUSServoAngle(SERVO_UP, &Angle_Up);
	QueryFSUSServoAngle(SERVO_DOWN, &Angle_Down);
	
	/* 画图案 */
	if(FLAG == 1) {
		draw_single_sine_wave();
		//GimbalController_Update(&gimbal_Circle, 0.01f);
		//TriangleController_Update(&triangle, 0.01f);
	}
	
	
	/* -------------- 用户程序 -------------- */
}

/********************************END OF FILE****************************/
