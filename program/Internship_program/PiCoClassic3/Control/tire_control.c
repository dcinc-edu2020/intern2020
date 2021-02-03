/*==============================================================================*/
/* Tire Control C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "tire_control.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
int	i_PreviousDrive = START;	// �O��̋쓮������

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void vd_TireControl(int i_MotorRotateDir_R, int i_MotorRotateDir_L, int i_DriveDistance);	// �^�C������
void vd_RunStraight(int i_DriveDistance, float f_TargetSpeed);					// �^�C������(���i)
void vd_RunRotate(int i_DriveDistance, int i_MotorRotateDir_R, int i_MotorRotateDir_L);		// �^�C������(����)

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  �^�C������			                                        	*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		i_MotorRotateDir_R	�E�ԗ֋쓮����		       	*/
/*  			i_MotorRotateDir_L	���ԗ֋쓮����			*/
/*  			i_DriveDistance		�^�C���쓮����			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_TireControl(int i_MotorRotateDir_R, int i_MotorRotateDir_L, int i_DriveDistance)
{
	/* ���䏈�� */
	if(i_MotorRotateDir_R == i_MotorRotateDir_L)	// ���ԗւƉE�ԗւ̉�]�����������Ȃ�
	{
		/* ���i���� */
		vd_RunStraight(i_DriveDistance, SEARCH_SPEED);
	}
	else
	{
		/* ���񐧌� */
		vd_RunStraight(STRAIGHT_HALFSECTION, MIN_SPEED);			// ���i����(����O�Ɍ�������)
		vd_RunRotate(i_DriveDistance, i_MotorRotateDir_R, i_MotorRotateDir_L);	// ���񐧌�
		vd_RunStraight(STRAIGHT_HALFSECTION, SEARCH_SPEED);			// ���i����(�����ɉ�������)
	}
}

/*==============================================================================*/
/*  �^�C������(���i)			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		i_DriveDistance		�^�C���쓮����			*/
/*			f_TargetSpeed		�ڕW���x(�����E�����̐ݒ�)	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_RunStraight(int i_DriveDistance, float f_TargetSpeed)
{	
	/* ���[�^�̋쓮�����̐ݒ� */
	MOT_CWCCW_R = MOT_FORWARD;	// �E�ԗ֋쓮����
	MOT_CWCCW_L = MOT_FORWARD;	// ���ԗ֋쓮����
	
	/* ���s����(mm)���i�ނ̂ɕK�v�ȃX�e�b�s���O���[�^�̖ڕW�X�e�b�v�����Z�o */
	/* �c�X�e�b�s���O���[�^�[��1��]400�����A�E�ƍ��̃��[�^�[�̕��ς��g���đ��s�����𔻒肷�� */
	int obj_step = LEN2STEP(i_DriveDistance);	// 1��]400�X�e�b�v�B1�X�e�b�v
	
	/* ����ݒ� */
	con_wall.enable = true;		// ���i����PID���䂷��
	
	/* �����x�ݒ� */
	max_speed  = SEARCH_SPEED;
	r_accel = accel;								//�����x
	
	/* ���O�̐����Ԃɂ���đ��x��ݒ� */
	if(STRAIGHT == i_PreviousDrive)	
	{	
		speed = SEARCH_SPEED;		// ���i�̏ꍇ
	}
	else if (START == i_PreviousDrive)
	{
		speed = MIN_SPEED;
	}
	else
	{
		speed = MIN_SPEED;		// �^�[������܂��̓X�^�[�g�̏ꍇ
	}

	if(speed < f_TargetSpeed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = f_TargetSpeed;
	}
	
	/* ���[�^�[�쓮 */
	step_r = step_l = 0;			// �X�e�b�s���O���[�^�[�̃X�e�b�v���J�E���g�����Z�b�g
	
	vd_StartMotorControl();			// ���[�^�[��]�J�n
	
	// �����J�n���ׂ��ʒu�ɒB����܂ő҂�
	while( (i_DriveDistance - STEP2LEN(step_r + step_l) ) > ( ( (f_TargetSpeed * f_TargetSpeed) - (speed * speed) ) / (-2*1000*accel) ));
	
	r_accel = -accel;			// �����J�n
	
	while( (step_r + step_l) < obj_step);	// �ڕW�n�_�܂ő��s�c�X�e�b�v���͊��荞�ݓ��ŉ��Z
	
	vd_StopMotorControl();			// ���[�^�[��]��~
	
	/* ���O�̐����Ԃ̍X�V */
	i_PreviousDrive = STRAIGHT;
}

/*==============================================================================*/
/*  �^�C������(����)			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		i_DriveDistance		�^�C���쓮����			*/
/*  			i_MotorRotateDir_R	�E�ԗ֋쓮����		       	*/
/*  			i_MotorRotateDir_L	���ԗ֋쓮����			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_RunRotate(int i_DriveDistance, int i_MotorRotateDir_R, int i_MotorRotateDir_L)
{	
	/* ���[�^�̋쓮�����̐ݒ� ���] or �t�] */
	MOT_CWCCW_R = i_MotorRotateDir_R;	// �E�ԗ֋쓮����
	MOT_CWCCW_L = i_MotorRotateDir_L;	// ���ԗ֋쓮����
	
	/* �ڕW�X�e�b�v�Z�o */
	/*  �^�C���̉~���ƃ^�[���p�x����K�v�ȃX�e�b�v�����Z�o 				*/
	/*  ��. 90�x����̏ꍇ�A���E�ʁX�̕����Ƀ^�C����1��]�����邱�ƂŐ���ł���	*/
	int obj_step  = LEN2STEP(i_DriveDistance * TREAD_CIRCUIT);
	
	/* ����ݒ� */
	int tar_speed   = MIN_SPEED;	// �ڕW���x(�Œ�)�c30mm/s
	con_wall.enable = false;	// ���M�n���񒆂�PID�����؂�
	
	r_accel = TURN_ACCEL;		// ��]�̉����x������
	max_speed = TURN_SPEED;		
	min_speed = MIN_SPEED;
	speed = MIN_SPEED;		// ���x�����Z�b�g
	
	/* ���[�^�[���� */
	step_r = step_l = 0;		// �X�e�b�s���O���[�^�[�̃X�e�b�v���J�E���g�����Z�b�g
	vd_Wait_ms(250);			// �����Ȃ���Ǝp���������̂ŁA�����ҋ@

	vd_StartMotorControl();		// ���[�^�[��]�J�n
	
	// �����J�n���ׂ��ʒu�ɒB����܂ő҂�
	while( ((i_DriveDistance * TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed * tar_speed) - (speed * speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;			// �����J�n
	
	while((step_r + step_l) < obj_step);	// ��~����ʒu�ɒB����܂ő҂�
		
	vd_StopMotorControl();			// ���[�^�[��]��~

	vd_Wait_ms(250);			// �^�[���㏭���҂�
	
	/* ���O�̐����Ԃ̍X�V */
	i_PreviousDrive = TURN;
}