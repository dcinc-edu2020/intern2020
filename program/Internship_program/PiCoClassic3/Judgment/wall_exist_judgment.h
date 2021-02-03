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
extern int i_ExistsFrontWall(short s_fl_Distance, short s_fr_Distance);	// 前壁検知
extern int i_ExistsLeftWall(short s_l_Distance);			// 左壁検知
extern int i_ExistsRightWall(short s_r_Distance);			// 右壁検知

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 壁があるか否かの閾値 */
#define THRESHOLD_R	(TH_SEN_R)	// 右壁判定用閾値
#define THRESHOLD_L	(TH_SEN_L)	// 左壁判定用閾値
#define THRESHOLD_FR	(TH_SEN_FR)	// 右前壁判定用閾値
#define THRESHOLD_FL	(TH_SEN_FL)	// 左前壁判定用閾値

#endif
