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
extern void vd_TireControl(int i_MotorRotateDir_R, int i_MotorRotateDir_L, int i_DriveDistance);	// �^�C������
extern void vd_RunStraight(int i_DriveDistance, float f_TargetSpeed);					// �^�C������(���i)
extern void vd_RunRotate(int i_DriveDistance, int i_MotorRotateDir_R, int i_MotorRotateDir_L);		// �^�C������(����)

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �����ԃp�����[�^ */
#define STRAIGHT		(0)	// ���i
#define TURN			(1)	// ����
#define UNKNOWN			(2)	// ����`
#define START			(3)	// �X�^�[�g���(��~)

/* �쓮���� */
#define STRAIGHT_HALFSECTION	(90)	// �����̋���(mm)
#define STRAIGHT_SECTION	(180)	// 1���̋���(mm)
#define TURN_90			(1)
#define TURN_180		(2)

/* ���s�p�����[�^ */
#define SEARCH_SPEED		(400)	// �T���̑��x 400[mm/s]
#define SEARCH_ACCEL		(1.5)	// �T���̉����x

#define TURN_ACCEL		(0.3)	// ���M�n����̉����x
#define TURN_SPEED		(500)	// ���M�n����̍ō����̃��~�b�g

#endif