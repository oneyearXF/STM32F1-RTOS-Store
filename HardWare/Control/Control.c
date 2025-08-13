/* include */
#include "Control.h"                  
/* --------------------------------------------------------------------------- */
/* 变量声明 */
Usart_DataTypeDef* servoUsart = &usart3;
extern float Angle_Up, Angle_Down;

/* --------------------------------------------------------------------------- */
// 定义云台参数
#define SERVO_X_ID 1           // X轴舵机ID
#define SERVO_Y_ID 2           // Y轴舵机ID
#define SERVO_X_MIN_ANGLE 20.0f   // X轴舵机最小角度(度)
#define SERVO_X_MAX_ANGLE 55.0f   // X轴舵机最大角度(度)
#define SERVO_Y_MIN_ANGLE 79.0f   // Y轴舵机最小角度(度)
#define SERVO_Y_MAX_ANGLE 103.0f  // Y轴舵机最大角度(度)
#define SERVO_MOVING_THRESHOLD 1.0f // 舵机运动完成阈值(度)

// 定义正弦波参数
#define SIN_CYCLES 2           // 正弦波周期数
#define POINTS_PER_CYCLE 50    // 每个周期的点数
/* --------------------------------------------------------------------------- */
/* 舵机控制角度 */
void ControlFSUSServoAngle(uint8_t ID, int Angle, int waitTime)
{
	FSUS_SetServoAngle(servoUsart, ID, Angle, waitTime, 0);
}

/* 舵机查询角度 */
void QueryFSUSServoAngle(uint8_t ID, float *Angle)
{
	FSUS_QueryServoAngle(servoUsart, ID, Angle);
}

/* 舵机阻尼模式 */
void ControlFSUSServoDamping(uint8_t ID)
{
	FSUS_DampingMode(servoUsart, ID, 300);
}

/* AMT限幅 */
float AMT_Limit(float AMT, float Low, float High)
{
	if(AMT < Low)		AMT = Low;
	else if(AMT > High)	AMT = High;
	
	return AMT;
}

/* --------------------------------------------------------------------------- */
/* 初始化圆控制器 */
void GimbalController_Init(GimbalController* ctrl, 
                          float yaw_offset, float pitch_offset, 
                          float radius, float speed) 
{
    ctrl->yaw_offset = yaw_offset;
    ctrl->pitch_offset = pitch_offset;
    ctrl->radius = radius;
    ctrl->speed = speed;
    ctrl->angle = 0.0f;
}

/* 画圆 */
void GimbalController_Update(GimbalController* ctrl, float delta_time) 
{
    /* 更新角度(转换为弧度) */
    ctrl->angle += (ctrl->speed * delta_time * M_PI / 180.0f);
    if (ctrl->angle > 2 * M_PI) 
        ctrl->angle -= 2 * M_PI;
 
    
    /* 计算新的目标位置 */
    Angle_Down = ctrl->yaw_offset + ctrl->radius * cosf(ctrl->angle);
    Angle_Up = ctrl->pitch_offset + ctrl->radius * sinf(ctrl->angle);
	
//	/* 角度限幅 */
//	AMT_Limit(Angle_Up, 50, 130.3);
//	AMT_Limit(Angle_Down, 0.3, 70);
    
    /* 舵机控制 */
	ControlFSUSServoAngle(SERVO_UP, Angle_Up, 0);
	ControlFSUSServoAngle(SERVO_DOWN, Angle_Down, 0);
	
    
    /* 更新当前角度 */
    ctrl->current_yaw = Angle_Down;
    ctrl->current_pitch = Angle_Up;
}

/* --------------------------------------------------------------------------- */

// 初始化三角形控制器
void TriangleController_Init(TriangleController* ctrl, 
                           float speed,
                           float v1_yaw, float v1_pitch,
                           float v2_yaw, float v2_pitch,
                           float v3_yaw, float v3_pitch) {
    ctrl->speed = speed;
    ctrl->current_vertex = 0;
    ctrl->progress = 0.0f;
    
    // 设置三个顶点
    ctrl->vertex[0][0] = v1_yaw;
    ctrl->vertex[0][1] = v1_pitch;
    
    ctrl->vertex[1][0] = v2_yaw;
    ctrl->vertex[1][1] = v2_pitch;
    
    ctrl->vertex[2][0] = v3_yaw;
    ctrl->vertex[2][1] = v3_pitch;
    
    // 初始位置设为第一个顶点
    ctrl->current_yaw = v1_yaw;
    ctrl->current_pitch = v1_pitch;
}

// 计算两点之间距离(度)
float CalculateDistance(float yaw1, float pitch1, float yaw2, float pitch2) {
    float dyaw = yaw2 - yaw1;
    float dpitch = pitch2 - pitch1;
    return sqrtf(dyaw*dyaw + dpitch*dpitch);
}

// 更新舵机位置(周期性调用)
void TriangleController_Update(TriangleController* ctrl, float delta_time) {
    // 计算当前边的起始点和目标点
    int start_vertex = ctrl->current_vertex;
    int end_vertex = (ctrl->current_vertex + 1) % 3;
    
    float start_yaw = ctrl->vertex[start_vertex][0];
    float start_pitch = ctrl->vertex[start_vertex][1];
    float end_yaw = ctrl->vertex[end_vertex][0];
    float end_pitch = ctrl->vertex[end_vertex][1];
    
    // 计算当前边的总长度
    float edge_length = CalculateDistance(start_yaw, start_pitch, end_yaw, end_pitch);
    
    // 计算本次更新应移动的距离
    float move_distance = ctrl->speed * delta_time;
    
    // 更新进度
    ctrl->progress += move_distance / edge_length;
    
    // 如果完成当前边，切换到下一条边
    if (ctrl->progress >= 1.0f) {
        ctrl->progress = 0.0f;
        ctrl->current_vertex = end_vertex;
        
        // 更新到下一条边的起点
        start_vertex = ctrl->current_vertex;
        end_vertex = (ctrl->current_vertex + 1) % 3;
        start_yaw = ctrl->vertex[start_vertex][0];
        start_pitch = ctrl->vertex[start_vertex][1];
        end_yaw = ctrl->vertex[end_vertex][0];
        end_pitch = ctrl->vertex[end_vertex][1];
    }
    
    // 计算当前目标位置(线性插值)
    float target_yaw = start_yaw + (end_yaw - start_yaw) * ctrl->progress;
    float target_pitch = start_pitch + (end_pitch - start_pitch) * ctrl->progress;
    
    // 控制舵机
    //* 舵机控制 */
    ControlFSUSServoAngle(SERVO_UP, target_pitch, 0);
	ControlFSUSServoAngle(SERVO_DOWN, target_yaw, 0);
    
    // 更新当前角度
    ctrl->current_yaw = target_yaw;
    ctrl->current_pitch = target_pitch;
}

/* --------------------------------------------------------------------------- */

// 绘制单次正弦波函数
void draw_single_sine_wave(void) {
    float x_range = SERVO_X_MAX_ANGLE - SERVO_X_MIN_ANGLE;
    float y_range = SERVO_Y_MAX_ANGLE - SERVO_Y_MIN_ANGLE;
    uint16_t total_points = SIN_CYCLES * POINTS_PER_CYCLE;
    
    // 移动到起始位置
    float start_x = SERVO_X_MIN_ANGLE;
    float start_y = SERVO_Y_MIN_ANGLE + y_range/2 + (y_range/2) * calculate_sine_y(0);
    move_servo_sync(SERVO_X_ID, start_x, SERVO_Y_ID, start_y);
    
    // 绘制正弦波
    for(uint16_t i = 1; i <= total_points; i++) {
        float progress = (float)i / total_points;  // 0到1的进度
        float x_angle = SERVO_X_MIN_ANGLE + progress * x_range;
        float x_normalized = progress * SIN_CYCLES * 2 * M_PI;  // 转换为弧度
        
        // 计算Y轴位置 (正弦波)
        float y_angle = SERVO_Y_MIN_ANGLE + y_range/2 + (y_range/2) * calculate_sine_y(x_normalized);
        
        // 同步移动两个舵机
        move_servo_sync(SERVO_X_ID, x_angle, SERVO_Y_ID, y_angle);
    }
}

// 计算正弦波Y值 (-1到1)
float calculate_sine_y(float x_normalized) {
    return sinf(x_normalized);
}

// 同步移动两个舵机
void move_servo_sync(uint8_t x_id, float x_angle, uint8_t y_id, float y_angle) {
    // 限制角度范围
    x_angle = fmaxf(SERVO_X_MIN_ANGLE, fminf(SERVO_X_MAX_ANGLE, x_angle));
    y_angle = fmaxf(SERVO_Y_MIN_ANGLE, fminf(SERVO_Y_MAX_ANGLE, y_angle));
    
    // 发送移动指令 (速度为最大值)
    ControlFSUSServoAngle(x_id, x_angle, 0);  // 0表示最大速度
    ControlFSUSServoAngle(y_id, y_angle, 0);
    
    // 更新当前角度
    float current_x, current_y;
	QueryFSUSServoAngle(x_id, &current_x);
    QueryFSUSServoAngle(y_id, &current_y);
}

// 等待舵机停止运动 (优化版)
void wait_for_servo_stop(uint8_t servo_id) {
    float prev_angle;
	QueryFSUSServoAngle(servo_id, &prev_angle);
    float current_angle;
    
    do {
        QueryFSUSServoAngle(servo_id, &prev_angle);
    } while(fabs(current_angle - prev_angle) > SERVO_MOVING_THRESHOLD);
}


























