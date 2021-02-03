/*==============================================================================*/
/* SesorDriver Header File							*/
/*==============================================================================*/
#ifndef _SENSOR_DRIVER_H
#define _SENSOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "sensor_driver.h"

/*------------------------------------------------------------------------------*/
/* Type Definitions								*/
/*------------------------------------------------------------------------------*/
/* �^�U�l����舵���񋓌^ */
typedef enum
{
	false = 0,		// �U
	true = 1,		// �^
}t_bool;

/* �Z���T�\���� */
typedef struct
{
	short value;		// ���݂̒l
	short p_value;		// 1mS�ߋ��̒l
	short error;		// value - ref
	short ref;		// ���t�@�����X�l
	short th_wall;		// �ǂ����邩�ۂ���臒l
	short th_control;	// ����������邩�ۂ���臒l
	t_bool is_wall;		// �ǂ����邩������ ( true = �ǂ��� false = �ǂȂ� )
	t_bool is_control;	// ����Ɏg�����ۂ�
}t_sensor;

/* ����\���� */
typedef struct
{
	float control;		// �ŏI�I�Ȑ����
	float error;		// �΍�
	float p_error;		// �ߋ��̕΍�
	float diff;		// �΍��̔����l
	float sum;		// �΍��̐ϕ��l
	float sum_max;		// �ϕ��l�̐����l
	float kp;		// ��ᐧ��萔
	float kd;		// ��������萔
	float ki;		// �ϕ�����萔
	t_bool enable;		// �����on/off
}t_control;

/*------------------------------------------------------------------------------*/
/* Variable Externs								*/
/*------------------------------------------------------------------------------*/
extern	t_sensor	sen_r;		// �E�Z���T�\����
extern	t_sensor	sen_l;		// ���Z���T�\����
extern	t_sensor	sen_fr;		// �E�O�Z���T�\����
extern	t_sensor	sen_fl;		// ���O�Z���T�\����
extern	t_control	con_wall;	// ����\����

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
extern void vd_InitSensor(void);	// �Z���T�[�p�����[�^������

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �Z���T�֘A�p�����[�^ */
#define WAITLOOP_SLED	300				// LED�����点�Ă���AD�ϊ����J�n����܂ł̎��ԉ҂��p�萔

// Ver3
#define REF_SEN_R	925				// �}�E�X����H�����ɒu�������̃Z���T�̒l
#define REF_SEN_L	685				// �}�E�X����H�����ɒu�������̃Z���T�̒l

// Ver2
//#define REF_SEN_R	825				// �}�E�X����H�����ɒu�������̃Z���T�̒l
//#define REF_SEN_L	691				// �}�E�X����H�����ɒu�������̃Z���T�̒l

// Ver1
//#define REF_SEN_R	1703				// �}�E�X����H�����ɒu�������̃Z���T�̒l
//#define REF_SEN_L	1732				// �}�E�X����H�����ɒu�������̃Z���T�̒l

// Ver3
#define TH_SEN_R	344				// �ǂ����邩�ۂ���臒l
#define TH_SEN_L	268				// �ǂ����邩�ۂ���臒l
#define TH_SEN_FR	263				// �ǂ����邩�ۂ���臒l
#define TH_SEN_FL	254				// �ǂ����邩�ۂ���臒l

// Ver2
//#define TH_SEN_R	314				// �ǂ����邩�ۂ���臒l
//#define TH_SEN_L	215				// �ǂ����邩�ۂ���臒l
//#define TH_SEN_FR	191				// �ǂ����邩�ۂ���臒l
//#define TH_SEN_FL	204				// �ǂ����邩�ۂ���臒l

// Ver1
//#define TH_SEN_R	1685				// �ǂ����邩�ۂ���臒l
//#define TH_SEN_L	1697				// �ǂ����邩�ۂ���臒l
//#define TH_SEN_FR	1698				// �ǂ����邩�ۂ���臒l
//#define TH_SEN_FL	1698				// �ǂ����邩�ۂ���臒l

#define CONTH_SEN_R	TH_SEN_R			// ����������邩�ۂ���臒l
#define CONTH_SEN_L	TH_SEN_L			// ����������邩�ۂ���臒l
#define CON_WALL_KP	(0.3)				// �ǃZ���T�ɂ��p������̔�ᐧ��̔��萔

/* �֐��}�N�� */
#define CONV_SEN2WALL(w) ((w) ? WALL : NOWALL)		// �Z���T��񂩂�Ǐ��֕ϊ�

#endif