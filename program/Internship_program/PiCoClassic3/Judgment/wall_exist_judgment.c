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
int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance);	// �O�ǌ��m
int i_ExistsLeftWall(short s_l_Distance);				// ���ǌ��m
int i_ExistsRightWall(short s_r_Distance);				// �E�ǌ��m

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  �O�ǌ��m				                                        */
/* 										*/
/*  ���E�̑O�����W��������A�O�ǂ̗L���𔻒f����				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		s_fl_Distance		���O�����W����		       	*/
/*  			s_fr_Distance		�E�O�����W����			*/
/*  Return   :         	i_ExistsFrontWall	�O�ǗL��			*/
/*			(TRUE / FALSE)					        */
/*==============================================================================*/
int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance)
{
	int iExistsWall = FALSE;
		
	// �O�ǂ̗L���𔻒f
	if( (s_fl_Distance < THRESHOLD_FL) && (s_fr_Distance < THRESHOLD_FR) )
	{
		iExistsWall =  FALSE;		// �ǖ���
	}
	else
	{
		iExistsWall =  TRUE;		// �ǗL��
	}
	
	return iExistsWall;
}

/*==============================================================================*/
/*  ���ǌ��m				                                        */
/* 										*/
/*  �������W��������A���ǂ̗L���𔻒f����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		s_l_Distance		�������W����		       	*/
/*  Return   :         	i_ExistsLeftWall	���ǗL��			*/
/*			(TRUE / FALSE)					        */
/*==============================================================================*/
int i_ExistsLeftWall(short s_l_Distance)
{
	int iExistsWall = FALSE;
	
	// ���ǂ̗L���𔻒f
	if(s_l_Distance < THRESHOLD_L)
	{
		iExistsWall = FALSE;		// �ǖ���
	}
	else
	{
		iExistsWall = TRUE;		// �ǗL��
	}
	
	return iExistsWall;
}

/*==============================================================================*/
/*  �E�ǌ��m				                                        */
/* 										*/
/*  �E�Ǖ��W��������A�E�ǂ̗L���𔻒f����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		s_r_Distance		�E�����W����		       	*/
/*  Return   :         	i_ExistsRightWall	�E�ǗL��			*/
/*			(TRUE / FALSE)					        */
/*==============================================================================*/
int i_ExistsRightWall(short s_r_Distance)
{
	int iExistsWall = FALSE;
	
	// �E�ǂ̗L���𔻒f
	if(s_r_Distance < THRESHOLD_R)	
	{
		iExistsWall = FALSE;		// �ǖ���
	}
	else
	{
		iExistsWall = TRUE;		// �ǗL��
	}
	
	return iExistsWall;
}