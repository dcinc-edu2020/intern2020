/*==============================================================================*/
/* Judgement Module C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "judgment_module.h"

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void vd_Judgement(void);	// ���f

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  ���f				                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_Judgement(void)
{
	int iExist_RightWall;	// �ǌ��m���茋��
	int iExist_LeftWall;
	int iExist_FrontWall;
	int iIsGoal;		// �S�[�����茋��
	
	/* �ǌ��m */
	iExist_FrontWall = i_ExistsFrontWall(sen_fl.value, sen_fr.value);	// �O�ǌ��m
	iExist_RightWall = i_ExistsRightWall(sen_r.value);			// �E�ǌ��m
	iExist_LeftWall  = i_ExistsLeftWall(sen_l.value);			// ���ǌ��m

	/* �S�[�����m */ 
	iIsGoal = i_IsGoalJudgment(iExist_FrontWall, iExist_LeftWall, iExist_RightWall);
	
	/* ���s���[�h���� */
	vd_Judgment_RunMode(iExist_FrontWall, iExist_LeftWall, iExist_RightWall, iIsGoal);
	
	/* ���s�쓮 */
	vd_Judgment_DriveMode();
}