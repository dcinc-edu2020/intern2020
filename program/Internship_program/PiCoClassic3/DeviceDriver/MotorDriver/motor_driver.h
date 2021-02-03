/*==============================================================================*/
/* MotorDriver Header File							*/
/*==============================================================================*/
#ifndef _MOTOR_DRIVER_H
#define _MOTOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "iodefine.h"
#include "portdef.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
extern void vd_InitMotor(void);			// ���[�^�[����p�p�����[�^������
extern void vd_MotorPowerON(void);		// ���[�^�[�㎥
extern void vd_MotorPowerOFF(void);		// ���[�^�[�E��
extern void vd_StartMotorControl(void);		// ���[�^�[��]�J�n
extern void vd_StopMotorControl(void);		// ���[�^�[��]��~

/*------------------------------------------------------------------------------*/
/* Variable Externs								*/
/*------------------------------------------------------------------------------*/
extern	unsigned int	step_r;			// �E���[�^�[�X�e�b�v��(���荞�ݓ��ŃJ�E���g�A�b�v)
extern	unsigned int	step_l;			// �����[�^�[�X�e�b�v��(���荞�ݓ��ŃJ�E���g�A�b�v)
extern	float		accel;			// �����x(�ݒ�l�������Ȃ�)
extern	float		r_accel;		// �����x(���ۂ̒l����������)
extern	float		max_speed;		// �ō����x(�ݒ�l)
extern	float		min_speed;		// �Œᑬ�x(�ݒ�l)
extern	float		speed;			// ���x(���݂̒l)

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �����I�ȃp�����[�^ */
#define TIRE_DIAMETER	(48.0)			// �^�C���̒��a [mm]
#define TREAD_WIDTH	(65.0+4.2)		// �g���b�h�� [mm]
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)	// ���M�n����̎��Ƀ^�C������������

#define MIN_SPEED	(30)			// �Œᑬ�x.�W�F�l�������W�X�^��16bit�ł��邱�ƂƁAMTU�̓�����g�����狁�߂���l�������悻18mm/s�Ȃ̂ŁA�]�T��������30mm/s

#define PI 		(3.141592653589793)	// �~����

/* ���[�^�쓮�p�p�����[�^ */
#define MOT_FORWARD	(0)	//���[�^�h���C�o��CWCCW�[�q��LOW���o�͂���ƑO�i����
#define MOT_BACK	(1)	//���[�^�h���C�o��CWCCW�[�q��HIGH���o�͂���ƃo�b�N����

/* �֐��}�N�� */
#define TIRE_CIRCUIT	(PI*TIRE_DIAMETER)			//�^�C���̉~���𒼌a����Z�o(PI�͉~����)
#define SPEED2GREG(v)	(7500/(((v)/TIRE_CIRCUIT)))		//�X�s�[�h����W�F�l�������W�X�^�̒l���v�Z

#define LEN2STEP(l)	(2*400*(l)/TIRE_CIRCUIT)		//���s����(mm)����X�e�b�s���O���[�^�̃X�e�b�v�����Z�o
#define STEP2LEN(s) 	(TIRE_CIRCUIT*(s)/(2*400))		//�X�e�b�s���O���[�^�̃X�e�b�v�����瑖�s�������Z�o


#endif