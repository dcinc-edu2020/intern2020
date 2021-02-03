/*==============================================================================*/
/* Tire Control Header File							*/
/*==============================================================================*/
#ifndef _TIRE_CONTROL_H
#define _TIRE_CONTROL_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "motor_driver.h"
#include "sensor_driver.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
extern void vd_TireControl(int i_MotorRotateDir_R, int i_MotorRotateDir_L, int i_DriveDistance);	// タイヤ制御
extern void vd_RunStraight(int i_DriveDistance, float f_TargetSpeed);					// タイヤ制御(直進)
extern void vd_RunRotate(int i_DriveDistance, int i_MotorRotateDir_R, int i_MotorRotateDir_L);		// タイヤ制御(旋回)

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 制御状態パラメータ */
#define STRAIGHT		(0)	// 直進
#define TURN			(1)	// 旋回
#define UNKNOWN			(2)	// 未定義
#define START			(3)	// スタート状態(停止)

/* 駆動距離 */
#define STRAIGHT_HALFSECTION	(90)	// 半区画の距離(mm)
#define STRAIGHT_SECTION	(180)	// 1区画の距離(mm)
#define TURN_90			(1)
#define TURN_180		(2)

/* 走行パラメータ */
#define SEARCH_SPEED		(400)	// 探索の速度 400[mm/s]
#define SEARCH_ACCEL		(1.5)	// 探索の加速度

#define TURN_ACCEL		(0.3)	// 超信地旋回の加速度
#define TURN_SPEED		(500)	// 超信地旋回の最高速のリミット

#endif