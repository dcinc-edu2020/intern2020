/*==============================================================================*/
/* Tire Control Header File							*/
/*==============================================================================*/
#ifndef _TIRE_CONTROL_H
#define _TIRE_CONTROL_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "maze_data.h"
#include "motor_driver.h"
#include "sensor_driver.h"
#include "run_route_judgement.h"

/*------------------------------------------------------------------------------*/
/* Enum Definitions								*/
/*------------------------------------------------------------------------------*/
/* ���s���[�h */
enum RUN_MODE{
	Forward   = 0,	// �O�i		�k
	TurnRight = 1,	// �E����	��
	Reverse	  = 2,	// 180�x����	��
	TurnLeft  = 3,	// ������	��
	Stop      = 4	// ��~
};

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void tire_control(void);					// �^�C������
void run_straight(int distance, float target_speed);		// �^�C������(���i)
void run_rotate(int rotate_direction, int rotate_angle);	// �^�C������(����)
void set_run_mode(enum RUN_MODE set_run_mode);			// ���s���[�h�ݒ�

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ������� */
#define TURN_RIGHT	(0)
#define TURN_LEFT	(1)

/* �쓮���� */
#define HALF_SECTION	(90)	// �����̋���(mm)
#define SECTION		(180)	// 1���̋���(mm)
#define TURN_90		(90)	// �^�[���p�x90�x
#define TURN_180	(180)	// �^�[���p�x180�x

#endif