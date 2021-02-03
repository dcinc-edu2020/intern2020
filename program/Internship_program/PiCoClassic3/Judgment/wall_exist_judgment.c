/*==============================================================================*/
/* Wall Exist Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "wall_exist_judgment.h"

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance);	// 前壁検知
int i_ExistsLeftWall(short s_l_Distance);				// 左壁検知
int i_ExistsRightWall(short s_r_Distance);				// 右壁検知

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  前壁検知				                                        */
/* 										*/
/*  左右の前方物標距離から、前壁の有無を判断する				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		s_fl_Distance		左前方物標距離		       	*/
/*  			s_fr_Distance		右前方物標距離			*/
/*  Return   :         	i_ExistsFrontWall	前壁有無			*/
/*			(TRUE / FALSE)					        */
/*==============================================================================*/
int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance)
{
	int iExistsWall = FALSE;
		
	// 前壁の有無を判断
	if( (s_fl_Distance < THRESHOLD_FL) && (s_fr_Distance < THRESHOLD_FR) )
	{
		iExistsWall =  FALSE;		// 壁無し
	}
	else
	{
		iExistsWall =  TRUE;		// 壁有り
	}
	
	return iExistsWall;
}

/*==============================================================================*/
/*  左壁検知				                                        */
/* 										*/
/*  左側物標距離から、左壁の有無を判断する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		s_l_Distance		左側物標距離		       	*/
/*  Return   :         	i_ExistsLeftWall	左壁有無			*/
/*			(TRUE / FALSE)					        */
/*==============================================================================*/
int i_ExistsLeftWall(short s_l_Distance)
{
	int iExistsWall = FALSE;
	
	// 左壁の有無を判断
	if(s_l_Distance < THRESHOLD_L)
	{
		iExistsWall = FALSE;		// 壁無し
	}
	else
	{
		iExistsWall = TRUE;		// 壁有り
	}
	
	return iExistsWall;
}

/*==============================================================================*/
/*  右壁検知				                                        */
/* 										*/
/*  右壁物標距離から、右壁の有無を判断する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		s_r_Distance		右側物標距離		       	*/
/*  Return   :         	i_ExistsRightWall	右壁有無			*/
/*			(TRUE / FALSE)					        */
/*==============================================================================*/
int i_ExistsRightWall(short s_r_Distance)
{
	int iExistsWall = FALSE;
	
	// 右壁の有無を判断
	if(s_r_Distance < THRESHOLD_R)	
	{
		iExistsWall = FALSE;		// 壁無し
	}
	else
	{
		iExistsWall = TRUE;		// 壁有り
	}
	
	return iExistsWall;
}