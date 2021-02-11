/*==============================================================================*/
/* Interrupt Header File							*/
/*==============================================================================*/
#ifndef _INTERRUPT_H
#define _INTERRUPT_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "motor_driver.h"
#include "sensor_driver.h"
#include "buzzer_driver.h"
#include "battery_driver.h"
#include "iodefine.h"
#include "tire_control.h"
#include "led_driver.h"
#include "battery_driver.h"

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void int_cmt0(void);				// 姿勢制御用割り込み
void int_cmt1(void);				// センサー読み込み用割り込み
void int_cmt2(void);				// 1msタイマー用割り込み
void int_mot_r(void);				// 右モーターステップカウント割り込み
void int_mot_l(void);				// 左モーターステップカウント割り込み
unsigned short getBatteryVolt(void);		// 電源状態取得
void battery_save(unsigned short v_value);	// 電源電圧監視


#endif