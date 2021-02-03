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
extern enum RUN_MODE ge_RunMode;	// 現在の走行モード

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void vd_Judgment_DriveMode(void);	// 走行駆動

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  走行駆動				                                        */
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
			vd_TireControl(MOT_FORWARD, MOT_FORWARD, STRAIGHT_SECTION);	// 1区画進む
			break;
		case TurnRight:
			vd_TireControl(MOT_BACK, MOT_FORWARD, TURN_90);			// 右に90度旋回
			break;
		case TurnLeft:
			vd_TireControl(MOT_FORWARD, MOT_BACK, TURN_90);			// 左に90度旋回
			break;		
		case Stop:
			// その場で停止
			break;
		case Reverse:
			vd_TireControl(MOT_BACK, MOT_FORWARD, TURN_180);		// 後ろに向く(180度ターン)
			break;	
		default:
			break;
	}
}