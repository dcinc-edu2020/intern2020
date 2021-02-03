/*==============================================================================*/
/* Wall Exist Judgement Header File						*/
/*==============================================================================*/
#ifndef _WALL_EXIST_JUDGMENT_H
#define _WALL_EXIST_JUDGMENT_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "sensor_driver.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
extern int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance);	// �O�ǌ��m
extern int i_ExistsLeftWall(short s_l_Distance);			// ���ǌ��m
extern int i_ExistsRightWall(short s_r_Distance);			// �E�ǌ��m

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �ǂ����邩�ۂ���臒l */
#define THRESHOLD_R	(TH_SEN_R)	// �E�ǔ���p臒l
#define THRESHOLD_L	(TH_SEN_L)	// ���ǔ���p臒l
#define THRESHOLD_FR	(TH_SEN_FR)	// �E�O�ǔ���p臒l
#define THRESHOLD_FL	(TH_SEN_FL)	// ���O�ǔ���p臒l

#endif
