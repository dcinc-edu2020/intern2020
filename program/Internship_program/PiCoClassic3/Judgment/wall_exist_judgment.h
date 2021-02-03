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
extern int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance);	// OÇm
extern int i_ExistsLeftWall(short s_l_Distance);			// ¶Çm
extern int i_ExistsRightWall(short s_r_Distance);			// EÇm

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* Çª é©Û©Ìèl */
#define THRESHOLD_R	(TH_SEN_R)	// EÇ»èpèl
#define THRESHOLD_L	(TH_SEN_L)	// ¶Ç»èpèl
#define THRESHOLD_FR	(TH_SEN_FR)	// EOÇ»èpèl
#define THRESHOLD_FL	(TH_SEN_FL)	// ¶OÇ»èpèl

#endif
