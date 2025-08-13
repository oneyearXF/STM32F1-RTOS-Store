/* include */
#include "PID.h"

/* 速度环控制 */
void SpeedLoop_Control(PID_t *PID_param, FOC_t *FOC_param)
{
	/* PID数据获取 */
	PID_param->ErrorSpeed = PID_param->TargetSpeed - PID_param->CurrentSpeed;					/* 误差速度 */
	PID_param->Derivative_Speed = PID_param->ErrorSpeed - PID_param->Last_ErrorSpeed;			/* 微分值 */
	
	/* PID计算 */
	FOC_param->Uq = PID_param->Kp * PID_param->ErrorSpeed +			/* P */
               		PID_param->Ki * PID_param->Integral_Speed +		/* I */
               		PID_param->Kd * PID_param->Derivative_Speed;	/* D */
	PID_param->SpeedResult = FOC_param->Uq;
	
	PID_param->Integral_Speed += PID_param->Last_ErrorSpeed;				/* 积分值 */
	/* 积分限幅 */
	PID_param->Integral_Speed = AMT_Limit(PID_param->Integral_Speed, -5000.0f, 5000.0f);
	
	/* 限幅 */
	FOC_param->Uq = AMT_Limit(FOC_param->Uq, -6.0f, 6.0f);
	PID_param->SpeedResult = AMT_Limit(PID_param->SpeedResult, -6.0f, 6.0f);

	/* 记录上一次的误差速度 */
	PID_param->Last_ErrorSpeed = PID_param->ErrorSpeed;
}

/* 位置环控制 */
void PosLoop_Control(PID_t *PID_param)
{
	/* PID数据获取 */
	PID_param->ErrorPos = PID_param->TargetPos - PID_param->CurrentPos;						/* 计算误差位置 */

	/* PID计算 */
	PID_param->PosResult =  PID_param->Kp * PID_param->ErrorPos;
	
	/* 限幅 */
	PID_param->PosResult = AMT_Limit(PID_param->PosResult, -6.0f, 6.0f);
}

/* 电流环控制 */
void EleLoop_Control(PID_t *PID_param, FOC_t *FOC_param)
{
	/* 变量声明 */
	float dt = 0.001f;

	/* PID数据获取 */
	PID_param->ErrorEle = PID_param->TargetEle - PID_param->CurrentEle;						/* 计算误差电流 */
	PID_param->Integral_Ele += PID_param->ErrorEle * dt;									/* 计算积分值 */
	PID_param->Derivative_Ele = (PID_param->ErrorEle - PID_param->Last_ErrorEle);			/* 计算微分值 */

	/* PID计算 */
	PID_param->EleResult =  PID_param->Kp * PID_param->ErrorEle +				/* P */
               				PID_param->Ki * PID_param->Integral_Ele +			/* I */
               				PID_param->Kd * PID_param->Derivative_Ele;			/* D */
	FOC_param->Uq = PID_param->EleResult;

	/* 限幅 */
	FOC_param->Uq = AMT_Limit(FOC_param->Uq, -2.0f, 2.0f);
	PID_param->EleResult = AMT_Limit(PID_param->EleResult, -2.0f, 2.0f);
	
	/* 记录上一次的误差位置 */
	PID_param->Last_ErrorEle = PID_param->ErrorEle;
}



