/*==============================================================================*/
/* Motor Driver C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "iodefine.h"
#include "motor_driver.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* モーター */
#define MOT_POWER	(PORT1.PODR.BIT.B5)
#define MOT_POWER_ON	MOT_POWER = 1		// ステッピングモーターを励磁
#define MOT_POWER_OFF	MOT_POWER = 0		// ステッピングモーターを脱力

#define MOT_CWCCW_R	(PORTC.PODR.BIT.B5)	// 右モーター駆動方向
#define MOT_CWCCW_L	(PORTC.PODR.BIT.B6)	// 左モーター駆動方向

/* 関数マクロ */
#define LEN2STEP(l)	(2*400*(l)/TIRE_CIRCUIT)		//走行距離(mm)からステッピングモータのステップ数を算出
#define STEP2LEN(s) 	(TIRE_CIRCUIT*(s)/(2*400))		//ステッピングモータのステップ数から走行距離を算出

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
unsigned int	step_r;			// 右モーターステップ数(割り込み内でカウントアップ)
unsigned int	step_l;			// 左モーターステップ数(割り込み内でカウントアップ)
float		accel;			// 加速度(設定値→符号なし)
float		r_accel;		// 加速度(実際の値→符号あり)
float		max_speed;		// 最高速度(設定値)
float		min_speed;		// 最低速度(設定値)
float		speed;			// 速度(現在の値)

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* モーター制御用パラメータ初期化			                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_motor(void)
{
	accel	= DEFAULT_ACCEL;
	r_accel = 0;
	speed	= 0;
	max_speed = MAX_SPEED;
	min_speed = MIN_SPEED;
	
	motor_power_off();		// ステッピングモーターを脱力
	
	return;
}

/*==============================================================================*/
/* モーター励磁									*/
/* 										*/
/* ステッピングモーターを励磁する						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void motor_power_on(void)
{
	MOT_POWER_ON;	// ステッピングモータを励磁
	wait_ms(1000);	// 励磁するまで少し待つ
	
	return;
}

/*==============================================================================*/
/* モーター脱力									*/
/* 										*/
/* ステッピングモーターを脱力する						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void motor_power_off(void)
{
	MOT_POWER_OFF;	// ステッピングモータを脱力
	
	return;
}

/*==============================================================================*/
/* 右モーター回転方向設定							*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		motor_direction		ステッピングモーター回転方向	*/
/*			(MOT_FORWARD/MOT_BACK)	CW:正転	/ CCW:逆転		*
/*  Return   :         	-							*/
/*==============================================================================*/
void set_motor_direction_r(int motor_direction)
{
	MOT_CWCCW_R = motor_direction;	// 右車輪駆動方向
	
	return;
}

/*==============================================================================*/
/* 左モーター回転方向設定							*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		motor_direction		ステッピングモーター回転方向	*/
/*			(MOT_FORWARD/MOT_BACK)	CW:正転	/ CCW:逆転		*
/*  Return   :         	-							*/
/*==============================================================================*/
void set_motor_direction_l(int motor_direction)
{
	MOT_CWCCW_L = motor_direction;	// 左車輪駆動方向
	
	return;
}

/*==============================================================================*/
/* モーターステップ数リセット							*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void reset_motor_step(void)
{	
	/* ステッピングモーターのステップ数カウントをリセット */
	step_r = 0;
	step_l = 0;
	
	return;
}
/*==============================================================================*/
/* モーター回転開始			                                        */
/* 										*/
/* ステッピングモーターのPWM制御を開始する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void start_motor_control(void)
{
	/* モーターのステップ数のカウントスタート */
	MTU.TSTR.BIT.CST3 = 1;
	MTU.TSTR.BIT.CST4 = 1;
	
	return;
}

/*==============================================================================*/
/* モーター回転停止			                                        */
/* 										*/
/* ステッピングモーターのPWM制御を停止する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void stop_motor_control(void)
{
	/* モーターのステップ数のカウントストップ */
	MTU.TSTR.BIT.CST3 = 0;
	MTU.TSTR.BIT.CST4 = 0;
	
	return;
}



/*==============================================================================*/
/* 走行ステップ数取得								*/
/* 										*/
/* 指定された走行距離を走行するために必要なモーターステップ数を算出する		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		distance	走行距離 [mm]				*/
/*  Return   :         	motor_step	走行距離分走るのに必要なステップ数	*/
/*==============================================================================*/
unsigned int get_motor_step(float distance)
{	
	/* 走行距離(mm)からステッピングモータのステップ数を算出			*/
	/*----------------------------------------------------------------------*/
	/* モーター1回転		： 400 [step]				*/
	/* モーター1回転の走行距離	： タイヤ円周(TIRE_CIRCUIT = 直径 * π)	*/
	/* 				　 　⇒ 約 150.8[mm]			*/
	/* 1ステップあたりの走行距離	： 約 150.8[mm] / 400[step]		*/
	/*				　 　⇒ 0.377[mm]			*/
	/*----------------------------------------------------------------------*/
	int motor_step = (400 * (distance) / TIRE_CIRCUIT);
	
	return motor_step;
}

/*==============================================================================*/
/* モーター走行距離取得								*/
/* 										*/
/* ステッピングモータのステップ数から走行距離を算出				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		motor_kind		モーター種別(右/左)		*/
/*  Return   :         	-							*/
/*==============================================================================*/
unsigned int get_mileage_step(int motor_kind)
{
	unsigned int mileage_step = 0;
	
	/* 走行距離 = 1ステップあたりの走行距離(0.377[mm]) × 現在までのカウントステップ数 */
	switch(motor_kind)	
	{
		case MOTOR_RIGHT:
			mileage_step = (TIRE_CIRCUIT / 400) * step_r;
			break;
		case MOTOR_LEFT:
			mileage_step = (TIRE_CIRCUIT / 400) * step_l;
			break;
		default:
			break;
	}
	
	return mileage_step;
}

/*==============================================================================*/
/* 加減速設定									*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		mileage		走行距離 [mm]				*/
/*			taget_speed	目標速度				*/
/*  Return   :         	-							*/
/*==============================================================================*/
void control_accel(int mileage, float target_speed)
{
	/* 減速開始すべき位置に達した場合、加速度をマイナス(減速)に設定する */ 
	if((mileage - STEP2LEN(step_r + step_l) ) < ( ( (target_speed * target_speed) - (speed * speed) ) / (-2*1000*accel) ))
	{
		r_accel = -accel;	// 減速開始
	}
	else
	{
		r_accel = accel;
	}
	
	return;
}
/*==============================================================================*/
/* 加減速設定(旋回)								*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		mileage		走行距離 [mm]				*/
/*			taget_speed	目標速度				*/
/*  Return   :         	-							*/
/*==============================================================================*/
void control_accel_turn(int mileage, float target_speed)
{
	/* 減速開始すべき位置に達した場合、加速度をマイナス(減速)に設定する */ 
	if((mileage - STEP2LEN(step_r + step_l) ) < ( ( (target_speed * target_speed) - (speed * speed) ) / (-2*1000*TURN_ACCEL) ))
	{
		r_accel = -TURN_ACCEL;	// 減速開始
	}
	else
	{
		r_accel = TURN_ACCEL;
	}
	
	return;
}

/*==============================================================================*/
/* 現在速度設定									*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		set_speed		速度 [mm/sec]			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_current_speed(float set_speed)
{
	speed = set_speed;
	
	return;
}
/*==============================================================================*/
/* 最高速度設定									*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		set_speed		速度 [mm/sec]			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_max_speed(float set_speed)
{
	max_speed = set_speed;
	
	return;
}
/*==============================================================================*/
/* 最低速度設定									*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		set_speed		速度 [mm/sec]			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_min_speed(float set_speed)
{
	min_speed = set_speed;
	
	return;
}

/*==============================================================================*/
/* 加速度設定									*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		set_accel		加速度				*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_r_accel(float set_accel)
{
	r_accel = set_accel;
	
	return;
}




