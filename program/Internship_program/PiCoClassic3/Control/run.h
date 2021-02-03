/* run.h */
#ifndef _RUN_H
#define _RUN_H


#include "iodefine.h"

#include "sensor_driver.h"
#include "motor_driver.h"
#include "tire_control.h"

#include "common.h"

//extern float		speed;
//extern t_control		con_wall;						//����\����

typedef enum
{
	front=0,		//�O
	right=1,		//�E
	rear=2,			//��
	left=3,			//��
	unknown,		//�����s��
}t_local_dir;		//�������猩�������������񋓌^

extern void straight(int len, float init_speed, float max_sp, float tar_speed);
extern void rotate(t_local_dir dir, int times);
extern void rotate2(t_local_dir dir, int times);




#endif