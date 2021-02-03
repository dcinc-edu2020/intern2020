/*==============================================================================*/
/* SesorDriver Header File							*/
/*==============================================================================*/
#ifndef _SENSOR_DRIVER_H
#define _SENSOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "sensor_driver.h"

/*------------------------------------------------------------------------------*/
/* Type Definitions								*/
/*------------------------------------------------------------------------------*/
/* 真偽値を取り扱う列挙型 */
typedef enum
{
	false = 0,		// 偽
	true = 1,		// 真
}t_bool;

/* センサ構造体 */
typedef struct
{
	short value;		// 現在の値
	short p_value;		// 1mS過去の値
	short error;		// value - ref
	short ref;		// リファレンス値
	short th_wall;		// 壁があるか否かの閾値
	short th_control;	// 制御をかけるか否かの閾値
	t_bool is_wall;		// 壁があるか無いか ( true = 壁あり false = 壁なし )
	t_bool is_control;	// 制御に使うか否か
}t_sensor;

/* 制御構造体 */
typedef struct
{
	float control;		// 最終的な制御量
	float error;		// 偏差
	float p_error;		// 過去の偏差
	float diff;		// 偏差の微分値
	float sum;		// 偏差の積分値
	float sum_max;		// 積分値の制限値
	float kp;		// 比例制御定数
	float kd;		// 微分制御定数
	float ki;		// 積分制御定数
	t_bool enable;		// 制御のon/off
}t_control;

/*------------------------------------------------------------------------------*/
/* Variable Externs								*/
/*------------------------------------------------------------------------------*/
extern	t_sensor	sen_r;		// 右センサ構造体
extern	t_sensor	sen_l;		// 左センサ構造体
extern	t_sensor	sen_fr;		// 右前センサ構造体
extern	t_sensor	sen_fl;		// 左前センサ構造体
extern	t_control	con_wall;	// 制御構造体

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
extern void vd_InitSensor(void);	// センサーパラメータ初期化

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* センサ関連パラメータ */
#define WAITLOOP_SLED	300				// LEDを光らせてからAD変換を開始するまでの時間稼ぎ用定数

// Ver3
#define REF_SEN_R	925				// マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	685				// マウスを迷路中央に置いた時のセンサの値

// Ver2
//#define REF_SEN_R	825				// マウスを迷路中央に置いた時のセンサの値
//#define REF_SEN_L	691				// マウスを迷路中央に置いた時のセンサの値

// Ver1
//#define REF_SEN_R	1703				// マウスを迷路中央に置いた時のセンサの値
//#define REF_SEN_L	1732				// マウスを迷路中央に置いた時のセンサの値

// Ver3
#define TH_SEN_R	344				// 壁があるか否かの閾値
#define TH_SEN_L	268				// 壁があるか否かの閾値
#define TH_SEN_FR	263				// 壁があるか否かの閾値
#define TH_SEN_FL	254				// 壁があるか否かの閾値

// Ver2
//#define TH_SEN_R	314				// 壁があるか否かの閾値
//#define TH_SEN_L	215				// 壁があるか否かの閾値
//#define TH_SEN_FR	191				// 壁があるか否かの閾値
//#define TH_SEN_FL	204				// 壁があるか否かの閾値

// Ver1
//#define TH_SEN_R	1685				// 壁があるか否かの閾値
//#define TH_SEN_L	1697				// 壁があるか否かの閾値
//#define TH_SEN_FR	1698				// 壁があるか否かの閾値
//#define TH_SEN_FL	1698				// 壁があるか否かの閾値

#define CONTH_SEN_R	TH_SEN_R			// 制御をかけるか否かの閾値
#define CONTH_SEN_L	TH_SEN_L			// 制御をかけるか否かの閾値
#define CON_WALL_KP	(0.3)				// 壁センサによる姿勢制御の比例制御の比例定数

/* 関数マクロ */
#define CONV_SEN2WALL(w) ((w) ? WALL : NOWALL)		// センサ情報から壁情報へ変換

#endif