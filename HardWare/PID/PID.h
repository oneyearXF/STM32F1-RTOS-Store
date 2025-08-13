/* USER CODE BEGIN Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PID_H
#define __PID_H
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif
	
/* include*/
#include "header_common.h"
/* --------------------------------------------------------------------------- */
/* define */

/* --------------------------------------------------------------------------- */
/* typedef */
/* FOC数据结构 */
typedef struct _FOC_t
{
    /* Uq */
    float Uq;           /* 力矩 */
    /* PWM */
    float Rate_A;       /* A相的比例 */
    float Rate_B;       /* B相的比例 */
    float Rate_C;       /* C相的比例 */
    /* 三相电压 */
    float UA;
    float UB;
    float UC;
    /* 二维的Ualpha, Ubeta */
    float Ualpha;
    float Ubeta;
    /* 零点角度 */
    float zero_electrial_angle;
}FOC_t;

/* PID 控制器结构体 */
typedef struct _PID_t
{
	/* 控制参数 */
    float Kp;
    float Ki;
    float Kd;
    /* 位置环--数据获取 */
	float CurrentPos;		/* 当前位置 */
	float TargetPos;		/* 目标位置 */
	float ErrorPos;		    /* 计算的误差位置 */
	float Last_ErrorPos;	/* 记录上一次的误差位置 */
	float Integral_Pos;		/* 积分的计算值 */
	float Derivative_Pos;	/* 微分的计算值 */
    float PosResult;        /* 结果 */
	/* 速度环--数据获取 */
	float CurrentSpeed;		/* 当前速度 */
	float TargetSpeed;		/* 目标速度 */
	float ErrorSpeed;		/* 计算的误差速度 */
	float Last_ErrorSpeed;	/* 记录上一次的误差速度 */
	float Integral_Speed;	/* 积分的计算值 */
	float PrvIntegral_Speed;
	float Derivative_Speed; /* 微分的计算值 */
    float SpeedResult;      /* 结果 */
    /* 电流环--数据获取 */
    float CurrentEle;		/* 当前电流 */
	float TargetEle;		/* 目标电流 */
	float ErrorEle;		    /* 计算的误差电流 */
	float Last_ErrorEle;	/* 记录上一次的误差电流 */
	float Integral_Ele;	    /* 积分的计算值 */
	float Derivative_Ele;	/* 微分的计算值 */
    float EleResult;        /* 结果 */ 
}PID_t;
/* --------------------------------------------------------------------------- */
/* 函数声明 */
void SpeedLoop_Control(PID_t *PID_param, FOC_t *FOC_param);
void PosLoop_Control(PID_t *PID_param);
void EleLoop_Control(PID_t *PID_param, FOC_t *FOC_param);
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif
#endif /* __FOC_H */

