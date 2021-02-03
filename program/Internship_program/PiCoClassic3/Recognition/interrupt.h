/* interrupt.h */
#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#define BATT_MAX		2552			//12.4V
#define BATT_MIN		2034			//10V


#include "motor_driver.h"
#include "sensor_driver.h"
#include "buzzer_driver.h"

void int_cmt0(void);
void int_cmt1(void);
void int_mot_r(void);
void int_mot_l(void);
unsigned short getBatteryVolt(void);
void battery_save(unsigned short v_value);

unsigned int		timer;							//1mSごとにカウントアップされる変数.

//extern t_sensor		sen_r, sen_l, sen_fr, sen_fl;	//センサ構造体
//extern t_control	con_wall;			//外部宣言の制御構造体

#endif