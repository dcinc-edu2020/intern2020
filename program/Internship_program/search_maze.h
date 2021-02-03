/* search_maze.h */
#ifndef _SEARCH_MAZE_H
#define _SEARCH_MAZE_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "motor_driver.h"
#include "tire_control.h"
#include "run.h"

/*------------------------------------------------------------------------------*/
/* Enum Definitions								*/
/*------------------------------------------------------------------------------*/
/* ���p��� */
typedef enum
{
	north =0,	// �k
	east  =1,	// ��
	south =2,	// ��
	west  =3,	// ��
}t_direction;

/* ���Ԃ��猩���i�s���� */
//typedef enum
//{
//	north =0,	// �k
//	east  =1,	// ��
//	south =2,	// ��
//	west  =3,	// ��
//}t_direction;

/*------------------------------------------------------------------------------*/
/* Struct Definitions								*/
/*------------------------------------------------------------------------------*/
/* �Ǐ����i�[����\����(�r�b�g�t�B�[���h) */
typedef struct
{
	unsigned char north	:2;	// �k�̕Ǐ��
	unsigned char east	:2;	// ���̕Ǐ��
	unsigned char south	:2;	// ��̕Ǐ��
	unsigned char west	:2;	// ���̕Ǐ��
}t_wall;

/* �}�C�N���}�E�X�̌��݂̈ʒu���������\���� */
typedef struct
{
	short x;		// X���W
	short y;		// Y���W
	t_direction dir;	// ���݌����Ă�����p
}t_position;

/* ���H�̃}�X���Ƃ̑�����ێ�����\����(�r�b�g�t�B�[���h) */
typedef struct
{
	unsigned char isUnknown	:1; // ���m���ۂ�(����͕s�g�p)
	unsigned char isGoal	:1; // �S�[�����ۂ�
	unsigned char padding	:6; // �\���̗̈�
}t_mapFlag;

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ���H��� */
#define MAZESIZE_X	(6)	// ���H�̑傫��(MAZESIZE_X * MAZESIZE_Y)���H
#define MAZESIZE_Y	(6)	// ���H�̑傫��(MAZESIZE_X * MAZESIZE_Y)���H

/* �Ǐ�� */
#define NOWALL		(0)	// �ǂ��Ȃ��ꍇ�̒l
#define WALL		(1)	// �ǂ�����ꍇ�̒l
#define UNKNOWN		(2)	// �ǂ����邩�Ȃ�������Ȃ���Ԃ̏ꍇ�̒l

/* ������ */
#define GOAL		(1)	// �S�[���̏ꍇ�̒l
#define MASK_SEARCH	(0x01)	// �T�����s�p�}�X�N�l.�Ǐ��Ƃ��̒l��AND�l���O�iNOWALL�j�Ȃ�ǂȂ�or���T�����
#define UNEXPLORED	(0xff)	// ���T���̏ꍇ�̒l(255)
#define EXPLORED	(0)	// �T���ς݂̏ꍇ�̒l(0)

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
extern  t_wall	g_wall[MAZESIZE_X][MAZESIZE_Y];	//�ǂ̏����i�[����\���̔z��
extern	t_sensor	sen_r;		// �E�Z���T�\����
extern	t_sensor	sen_l;		// ���Z���T�\����
extern	t_sensor	sen_fr;		// �E�O�Z���T�\����
extern	t_sensor	sen_fl;		// ���O�Z���T�\����
extern	t_control	con_wall;	// ����\����

#endif