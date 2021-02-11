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
void int_cmt0(void);				// �p������p���荞��
void int_cmt1(void);				// �Z���T�[�ǂݍ��ݗp���荞��
void int_cmt2(void);				// 1ms�^�C�}�[�p���荞��
void int_mot_r(void);				// �E���[�^�[�X�e�b�v�J�E���g���荞��
void int_mot_l(void);				// �����[�^�[�X�e�b�v�J�E���g���荞��
unsigned short getBatteryVolt(void);		// �d����Ԏ擾
void battery_save(unsigned short v_value);	// �d���d���Ď�


#endif