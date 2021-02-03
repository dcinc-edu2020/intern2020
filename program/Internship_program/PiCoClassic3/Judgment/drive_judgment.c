/*==============================================================================*/
/* Drive Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "drive_judgment.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
extern enum RUN_MODE ge_RunMode;	// ���݂̑��s���[�h

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void vd_Judgment_DriveMode(void);	// ���s�쓮

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  ���s�쓮				                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_Judgment_DriveMode(void)
{	
	switch(ge_RunMode)
	{
		case Forward:
			vd_TireControl(MOT_FORWARD, MOT_FORWARD, STRAIGHT_SECTION);	// 1���i��
			break;
		case TurnRight:
			vd_TireControl(MOT_BACK, MOT_FORWARD, TURN_90);			// �E��90�x����
			break;
		case TurnLeft:
			vd_TireControl(MOT_FORWARD, MOT_BACK, TURN_90);			// ����90�x����
			break;		
		case Stop:
			// ���̏�Œ�~
			break;
		case Reverse:
			vd_TireControl(MOT_BACK, MOT_FORWARD, TURN_180);		// ���Ɍ���(180�x�^�[��)
			break;	
		default:
			break;
	}
}