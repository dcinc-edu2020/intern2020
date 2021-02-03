/*==============================================================================*/
/* MotorDriver Header File							*/
/*==============================================================================*/
#ifndef _MOTOR_DRIVER_H
#define _MOTOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "iodefine.h"
#include "portdef.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
extern void vd_InitMotor(void);			// モーター制御用パラメータ初期化
extern void vd_MotorPowerON(void);		// モーター励磁
extern void vd_MotorPowerOFF(void);		// モーター脱力
extern void vd_StartMotorControl(void);		// モーター回転開始
extern void vd_StopMotorControl(void);		// モーター回転停止

/*------------------------------------------------------------------------------*/
/* Variable Externs								*/
/*------------------------------------------------------------------------------*/
extern	unsigned int	step_r;			// 右モーターステップ数(割り込み内でカウントアップ)
extern	unsigned int	step_l;			// 左モーターステップ数(割り込み内でカウントアップ)
extern	float		accel;			// 加速度(設定値→符号なし)
extern	float		r_accel;		// 加速度(実際の値→符号あり)
extern	float		max_speed;		// 最高速度(設定値)
extern	float		min_speed;		// 最低速度(設定値)
extern	float		speed;			// 速度(現在の値)

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 物理的なパラメータ */
#define TIRE_DIAMETER	(48.0)			// タイヤの直径 [mm]
#define TREAD_WIDTH	(65.0+4.2)		// トレッド幅 [mm]
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)	// 超信地旋回の時にタイヤが動く距離

#define MIN_SPEED	(30)			// 最低速度.ジェネラルレジスタが16bitであることと、MTUの動作周波数から求められる値がおおよそ18mm/sなので、余裕を持って30mm/s

#define PI 		(3.141592653589793)	// 円周率

/* モータ駆動用パラメータ */
#define MOT_FORWARD	(0)	//モータドライバのCWCCW端子にLOWを出力すると前進する
#define MOT_BACK	(1)	//モータドライバのCWCCW端子にHIGHを出力するとバックする

/* 関数マクロ */
#define TIRE_CIRCUIT	(PI*TIRE_DIAMETER)			//タイヤの円周を直径から算出(PIは円周率)
#define SPEED2GREG(v)	(7500/(((v)/TIRE_CIRCUIT)))		//スピードからジェネラルレジスタの値を計算

#define LEN2STEP(l)	(2*400*(l)/TIRE_CIRCUIT)		//走行距離(mm)からステッピングモータのステップ数を算出
#define STEP2LEN(s) 	(TIRE_CIRCUIT*(s)/(2*400))		//ステッピングモータのステップ数から走行距離を算出


#endif