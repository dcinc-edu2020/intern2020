/* run.h */
#ifndef _RUN_H
#define _RUN_H


#include "iodefine.h"

#include "sensor_driver.h"
#include "motor_driver.h"
#include "tire_control.h"

#include "common.h"

//extern float		speed;
//extern t_control		con_wall;						//制御構造体

typedef enum
{
	front=0,		//前
	right=1,		//右
	rear=2,			//後
	left=3,			//左
	unknown,		//方向不明
}t_local_dir;		//自分から見た方向を示す列挙型

extern void straight(int len, float init_speed, float max_sp, float tar_speed);
extern void rotate(t_local_dir dir, int times);
extern void rotate2(t_local_dir dir, int times);




#endif