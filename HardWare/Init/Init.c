//---------------------- include ------------------------------------
#include "header_common.h"
#include "Init.h"
//-------------------------------------------------------------------

//----------------------- 句柄声明 ----------------------------------
TaskHandle_t AppTaskCreate_Handle = NULL;	/* 创建任务句柄 */
TaskHandle_t KEY_Task_Handle = NULL;		/* KEY任务句柄 */
TaskHandle_t OLED_Task_Handle = NULL;		/* OLED任务句柄 */
TimerHandle_t Timer_Handle = NULL;   		/* 软件定时器句柄 */
//-------------------------------------------------------------------

/**
  * @brief  硬件初始化
  * @param  无
  * @retval 无
  */
void BSP_Init(void)
{
	/* 初始化 */
	OLED_Init();												/* OLED初始化 */
	SysTick_Init();          									/* 系统时钟初始化 */
	Usart_Init();												/* 舵机串口初始化 */
	UART4_Config();												/* 调试串口初始化 */
	LED_GPIO_Config();											/* LED初始化 */
	KEY_IO_Config();											/* 按键初始化 */
}

/**
  * @brief  任务初始化
  * @param  无
  * @retval 无
  */
void Task_Init(void)
{
	/* 定义一个创建信息返回值，默认为pdPASS */
    BaseType_t xReturn = pdPASS;

	/* 创建AppTaskCreate程 */
    xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  			/* 任务入口函数 */
                          (const char*    )"AppTaskCreate",			/* 任务名字 */
                          (uint16_t       )512,  					/* 任务栈大小 */
                          (void*          )NULL,					/* 任务入口函数参数 */
                          (UBaseType_t    )1, 						/* 任务的优先级 */
                          (TaskHandle_t*  )&AppTaskCreate_Handle); 	/* 任务控制块指针 */ 
    /* 启动任务调度 */           
    if(pdPASS == xReturn)
		/* 启动任务，开始调度 */
        vTaskStartScheduler();    
}

/**
  * @brief  统一创建任务
  * @param  无
  * @retval 无
  */
void AppTaskCreate(void)
{  
    //进入临界区
    taskENTER_CRITICAL();           
		
    /* 创建KEY_Task线程 */
    xTaskCreate((TaskFunction_t )KEY_Task,  			/* 任务入口函数 */
                (const char*    )"KEY_Task",			/* 任务名字 */
                (uint16_t       )512,  					/* 任务栈大小 */
                (void*          )NULL,					/* 任务入口函数参数 */
                (UBaseType_t    )4, 					/* 任务的优先级 */
                (TaskHandle_t*  )&KEY_Task_Handle); 	/* 任务控制块指针 */ 
	
	/* 创建OLEDTask线程 */
    xTaskCreate((TaskFunction_t )OLED_Task,  			/* 任务入口函数 */
                (const char*    )"OLED_Task",			/* 任务名字 */
                (uint16_t       )512,  					/* 任务栈大小 */
                (void*          )NULL,					/* 任务入口函数参数 */
                (UBaseType_t    )3, 					/* 任务的优先级 */
                (TaskHandle_t*  )&OLED_Task_Handle); 	/* 任务控制块指针 */ 	

	/* 创建定时器线程 */
	Timer_Handle = xTimerCreate((const char*	 	  )"AutoReloadTimer",
                              (TickType_t			  )100,		/* 定时器周期 1000(tick) */
                              (UBaseType_t			  )pdTRUE,	/* 周期模式 */
                              (void*				  )1,		/* 为每个计时器分配一个索引的唯一ID */
                              (TimerCallbackFunction_t)Timer_Callback); 
    if(Timer_Handle != NULL)         
		/* 开启周期定时器 */
		xTimerStart(Timer_Handle, 0);	
  
    //删除AppTaskCreate任务
    vTaskDelete(AppTaskCreate_Handle); 
	
    /* 退出临界区 */
    taskEXIT_CRITICAL();            
}

