/*==============================================================================*/
/* Switch Driver Header File							*/
/*==============================================================================*/
#ifndef _SWITCH_DRIVER_H
#define _SWITCH_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "iodefine.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ���[�h�I���X�C�b�` */
#define SW_R	(PORTC.PIDR.BIT.B2)	// �E�X�C�b�`	(��)
#define SW_C	(PORTC.PIDR.BIT.B3)	// �����X�C�b�`	(��)
#define SW_L	(PORT3.PIDR.BIT.B1)	// ���X�C�b�`	(��)

/* �X�C�b�`��� */
#define SW_OFF		(1)		// �X�C�b�`��OFF�̎��Ɏ��l
#define SW_ON		(0)		// �X�C�b�`��ON�̎��Ɏ��l
#define CHATTERING_WAIT	(50)		// �`���^�����O���p�҂�����

#endif