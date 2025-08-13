#ifndef __header_common_H__
#define __header_common_H__

/* -------------------------------------------------------------------------- */
/* include */	
/* RTOS头文件 */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "event_groups.h"

/* stm32库 */
#include "stm32f10x.h"

/* 自带底层设备库 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 开发板硬件bsp头文件 */
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_Enc.h"
#include "bsp_pwm.h"
#include "bsp_Motor.h"
#include "bsp_usart.h"
#include "bsp_Serial.h"
#include "Init.h"
#include "OLED.h"
#include "PID.h"
#include "Control.h"

/* FashionStar */
#include "ring_buffer.h"
#include "sys_tick.h"
#include "bsp_Serial.h"
#include "fashion_star_uart_servo.h"

/* MPU */
//#include "mpu6050.h"
//#include "mpuiic.h"
//#include "delay.h"
//#include "sys.h"
//#include "usart.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
/* -------------------------------------------------------------------------- */
/* define */
#define SERVO_UP				2
#define SERVO_DOWN				1
/* -------------------------------------------------------------------------- */
/* 函数声明 */
void KEY_Task(void* pvParameters);    	/* KEY_Task任务实现 */
void Timer_Callback(void* parameter);	/* 定时器实现 */
void OLED_Task(void* parameter);		/* OLED任务实现 */
/* -------------------------------------------------------------------------- */

#endif
