/* USER CODE BEGIN Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTROL_H
#define __CONTROL_H
/* --------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif
	
/* include*/
#include "header_common.h"
/* --------------------------------------------------------------------------- */
/* define */
#define M_PI					3.1415926
/* --------------------------------------------------------------------------- */
/* typedef */
/* 圆 */
typedef struct {
    float current_yaw;    // 当前偏航角度(度)
    float current_pitch;  // 当前俯仰角度(度)
    float yaw_offset;     // 圆心Yaw位置(度)
    float pitch_offset;   // 圆心Pitch位置(度)
    float radius;         // 圆的半径(角度)     
    float speed;          // 运动速度(度/秒)     
    float angle;          // 当前轨迹角度(弧度)   
} GimbalController;

/* 三角形 */
typedef struct {
    float current_yaw;    // 当前偏航角度(度)
    float current_pitch;  // 当前俯仰角度(度)
    float speed;         // 运动速度(度/秒)
    
    // 三角形顶点坐标 (yaw, pitch)
    float vertex[3][2];  
    int current_vertex;   // 当前目标顶点
    float progress;       // 当前边绘制进度 (0.0-1.0)
} TriangleController;

/* 正弦波 */
/* --------------------------------------------------------------------------- */
/* 函数声明 */
void ControlFSUSServoAngle(uint8_t ID, int Angle, int waitTime);
void ControlFSUSServoDamping(uint8_t ID);
void QueryFSUSServoAngle(uint8_t ID, float *Angle);
float AMT_Limit(float AMT, float Low, float High);
/* --------------------------------------------------------------------------- */
void GimbalController_Init(GimbalController* ctrl, 
                          float yaw_offset, float pitch_offset, 
                          float radius, float speed);
void GimbalController_Update(GimbalController* ctrl, float delta_time);
/* --------------------------------------------------------------------------- */
void TriangleController_Init(TriangleController* ctrl, 
                           float speed,
                           float v1_yaw, float v1_pitch,
                           float v2_yaw, float v2_pitch,
                           float v3_yaw, float v3_pitch);
float CalculateDistance(float yaw1, float pitch1, float yaw2, float pitch2);
void TriangleController_Update(TriangleController* ctrl, float delta_time);						  
/* --------------------------------------------------------------------------- */
void draw_single_sine_wave(void);
float calculate_sine_y(float x_normalized);
void move_servo_sync(uint8_t x_id, float x_angle, uint8_t y_id, float y_angle);
void wait_for_servo_stop(uint8_t servo_id);				   
						   
#ifdef __cplusplus
}
#endif
#endif /* __CONTROL_H */


