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
void vd_Judgement(void);	// 判断

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  判断				                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_Judgement(void)
{
	int iExist_RightWall;	// 壁検知判定結果
	int iExist_LeftWall;
	int iExist_FrontWall;
	int iIsGoal;		// ゴール判定結果
	
	/* 壁検知 */
	iExist_FrontWall = i_ExistsFrontWall(sen_fl.value, sen_fr.value);	// 前壁検知
	iExist_RightWall = i_ExistsRightWall(sen_r.value);			// 右壁検知
	iExist_LeftWall  = i_ExistsLeftWall(sen_l.value);			// 左壁検知

	/* ゴール検知 */ 
	iIsGoal = i_IsGoalJudgment(iExist_FrontWall, iExist_LeftWall, iExist_RightWall);
	
	/* 走行モード決定 */
	vd_Judgment_RunMode(iExist_FrontWall, iExist_LeftWall, iExist_RightWall, iIsGoal);
	
	/* 走行駆動 */
	vd_Judgment_DriveMode();
}