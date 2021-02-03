/*==============================================================================*/
/* Tire Control C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "tire_control.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
int	i_PreviousDrive = START;	// 前回の駆動制御状態

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void vd_TireControl(int i_MotorRotateDir_R, int i_MotorRotateDir_L, int i_DriveDistance);	// タイヤ制御
void vd_RunStraight(int i_DriveDistance, float f_TargetSpeed);					// タイヤ制御(直進)
void vd_RunRotate(int i_DriveDistance, int i_MotorRotateDir_R, int i_MotorRotateDir_L);		// タイヤ制御(旋回)

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  タイヤ制御			                                        	*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		i_MotorRotateDir_R	右車輪駆動方向		       	*/
/*  			i_MotorRotateDir_L	左車輪駆動方向			*/
/*  			i_DriveDistance		タイヤ駆動距離			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_TireControl(int i_MotorRotateDir_R, int i_MotorRotateDir_L, int i_DriveDistance)
{
	/* 制御処理 */
	if(i_MotorRotateDir_R == i_MotorRotateDir_L)	// 左車輪と右車輪の回転方向が同じなら
	{
		/* 直進制御 */
		vd_RunStraight(i_DriveDistance, SEARCH_SPEED);
	}
	else
	{
		/* 旋回制御 */
		vd_RunStraight(STRAIGHT_HALFSECTION, MIN_SPEED);			// 直進制御(旋回前に減速する)
		vd_RunRotate(i_DriveDistance, i_MotorRotateDir_R, i_MotorRotateDir_L);	// 旋回制御
		vd_RunStraight(STRAIGHT_HALFSECTION, SEARCH_SPEED);			// 直進制御(旋回後に加速する)
	}
}

/*==============================================================================*/
/*  タイヤ制御(直進)			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		i_DriveDistance		タイヤ駆動距離			*/
/*			f_TargetSpeed		目標速度(加速・減速の設定)	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_RunStraight(int i_DriveDistance, float f_TargetSpeed)
{	
	/* モータの駆動方向の設定 */
	MOT_CWCCW_R = MOT_FORWARD;	// 右車輪駆動方向
	MOT_CWCCW_L = MOT_FORWARD;	// 左車輪駆動方向
	
	/* 走行距離(mm)分進むのに必要なステッピングモータの目標ステップ数を算出 */
	/* …ステッピングモーターは1回転400分割、右と左のモーターの平均を使って走行距離を判定する */
	int obj_step = LEN2STEP(i_DriveDistance);	// 1回転400ステップ。1ステップ
	
	/* 制御設定 */
	con_wall.enable = true;		// 直進中はPID制御する
	
	/* 加速度設定 */
	max_speed  = SEARCH_SPEED;
	r_accel = accel;								//加速度
	
	/* 直前の制御状態によって速度を設定 */
	if(STRAIGHT == i_PreviousDrive)	
	{	
		speed = SEARCH_SPEED;		// 直進の場合
	}
	else if (START == i_PreviousDrive)
	{
		speed = MIN_SPEED;
	}
	else
	{
		speed = MIN_SPEED;		// ターン直後またはスタートの場合
	}

	if(speed < f_TargetSpeed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = f_TargetSpeed;
	}
	
	/* モーター駆動 */
	step_r = step_l = 0;			// ステッピングモーターのステップ数カウントをリセット
	
	vd_StartMotorControl();			// モーター回転開始
	
	// 減速開始すべき位置に達するまで待つ
	while( (i_DriveDistance - STEP2LEN(step_r + step_l) ) > ( ( (f_TargetSpeed * f_TargetSpeed) - (speed * speed) ) / (-2*1000*accel) ));
	
	r_accel = -accel;			// 減速開始
	
	while( (step_r + step_l) < obj_step);	// 目標地点まで走行…ステップ数は割り込み内で加算
	
	vd_StopMotorControl();			// モーター回転停止
	
	/* 直前の制御状態の更新 */
	i_PreviousDrive = STRAIGHT;
}

/*==============================================================================*/
/*  タイヤ制御(旋回)			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		i_DriveDistance		タイヤ駆動距離			*/
/*  			i_MotorRotateDir_R	右車輪駆動方向		       	*/
/*  			i_MotorRotateDir_L	左車輪駆動方向			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_RunRotate(int i_DriveDistance, int i_MotorRotateDir_R, int i_MotorRotateDir_L)
{	
	/* モータの駆動方向の設定 正転 or 逆転 */
	MOT_CWCCW_R = i_MotorRotateDir_R;	// 右車輪駆動方向
	MOT_CWCCW_L = i_MotorRotateDir_L;	// 左車輪駆動方向
	
	/* 目標ステップ算出 */
	/*  タイヤの円周とターン角度から必要なステップ数を算出 				*/
	/*  例. 90度旋回の場合、左右別々の方向にタイヤを1回転させることで旋回できる	*/
	int obj_step  = LEN2STEP(i_DriveDistance * TREAD_CIRCUIT);
	
	/* 制御設定 */
	int tar_speed   = MIN_SPEED;	// 目標速度(固定)…30mm/s
	con_wall.enable = false;	// 超信地旋回中はPID制御を切る
	
	r_accel = TURN_ACCEL;		// 回転の加速度を決定
	max_speed = TURN_SPEED;		
	min_speed = MIN_SPEED;
	speed = MIN_SPEED;		// 速度をリセット
	
	/* モーター制御 */
	step_r = step_l = 0;		// ステッピングモーターのステップ数カウントをリセット
	vd_Wait_ms(250);			// いきなり回ると姿勢が乱れるので、少し待機

	vd_StartMotorControl();		// モーター回転開始
	
	// 減速開始すべき位置に達するまで待つ
	while( ((i_DriveDistance * TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed * tar_speed) - (speed * speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;			// 減速開始
	
	while((step_r + step_l) < obj_step);	// 停止する位置に達するまで待つ
		
	vd_StopMotorControl();			// モーター回転停止

	vd_Wait_ms(250);			// ターン後少し待つ
	
	/* 直前の制御状態の更新 */
	i_PreviousDrive = TURN;
}