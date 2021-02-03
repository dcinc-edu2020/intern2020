
#include "run.h"
#include "portdef.h"



extern void wait_ms(int wtime);

//extern t_control	con_wall;						//制御構造体

extern float		speed;


void straight(int len, float init_speed, float max_sp, float tar_speed)	//直線走行
{
	int obj_step;									//目標ステップ数

	max_speed  = max_sp;
	r_accel = accel;								//加速度
	
	if(init_speed < MIN_SPEED){
		speed = MIN_SPEED;
	}else{
		speed=init_speed;
	}
	
	//目標速度が最低速度を下回らないようにする
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}
	if(init_speed < tar_speed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = tar_speed;
	}
	
	step_r = step_l = 0;							//ステップ数カウントのリセット
	
	con_wall.enable = true;							//壁制御を有効にする

	obj_step = LEN2STEP(len);						//目標ステップ数を算出

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;		//前方に進む

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//カウントスタート
	
	//減速を開始し始めるところまで待つ(あと走るべき距離が減速するべき距離より短くなったら・・・)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel;								//減速する
	
	while((step_r + step_l) < obj_step)	;			//目標地点まで走行
	
	MTU.TSTR.BIT.CST3 = 0;							//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;							//モータのカウントをストップ
	
}

void rotate(t_local_dir dir, int times){			//超信地旋回
//引数dir[right or left]方向に、90度×times度回転する

	int obj_step;									//目標ステップ
	int tar_speed = MIN_SPEED;						//目標速度(固定)
	
	slalom_enable	= false;		// スラローム走行状態
	con_wall.enable = false;		//超信地旋回中は制御を切る
	
	switch(dir)										//右まわりか左まわりかで、モータのCWCCWを切り替える
	{
		case front:
		case rear:
			return;									//超信地旋回なので、前や後ろは無い.

		case right:									//右に回るように設定
			MOT_CWCCW_R = MOT_BACK;
			MOT_CWCCW_L = MOT_FORWARD;
			break;

		case left:									//左に回るように設定
			MOT_CWCCW_R = MOT_FORWARD;
			MOT_CWCCW_L = MOT_BACK;
			break;
	}


	//最低速度を設定
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	r_accel = TURN_ACCEL;							//回転の加速度を決定
	max_speed = TURN_SPEED;
	min_speed = MIN_SPEED;
	speed = MIN_SPEED;								//速度をリセット
	step_r = step_l = 0;							//ステップ数をリセット
	
	obj_step = LEN2STEP(times*TREAD_CIRCUIT);		//目標ステップ数算出

	vd_Wait_ms(250);									//いきなり回ると姿勢が乱れるので、少し待機

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//カウントスタート
	
	//減速開始すべき位置に達するまで待つ
	while( ((times*TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;							//減速開始
	
	//停止する位置に達するまで待つ
	while((step_r + step_l) < obj_step)	;
	
	
	//モータ停止
	MTU.TSTR.BIT.CST3 = 0;							//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;							//モータのカウントをストップ


	//ターン後少し待つ
	vd_Wait_ms(250);
		
}

void rotate2(t_local_dir dir, int times){			//超信地旋回
//引数dir[right or left]方向に、90度×times度回転する

	int obj_step;									//目標ステップ
	int tar_speed = 500;						//目標速度(固定)
	
	con_wall.enable = false;						//超信地旋回中は制御を切る
	
	switch(dir)										//右まわりか左まわりかで、モータのCWCCWを切り替える
	{
		case front:
		case rear:
			return;									//超信地旋回なので、前や後ろは無い.

		case right:									//右に回るように設定
			MOT_CWCCW_R = MOT_BACK;
			MOT_CWCCW_L = MOT_FORWARD;
			break;

		case left:									//左に回るように設定
			MOT_CWCCW_R = MOT_FORWARD;
			MOT_CWCCW_L = MOT_BACK;
			break;
	}


	//最低速度を設定
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	r_accel = TURN_ACCEL;							//回転の加速度を決定
	max_speed = TURN_SPEED;
	min_speed = MIN_SPEED;
	speed = MIN_SPEED;								//速度をリセット
	step_r = step_l = 0;							//ステップ数をリセット
	
	obj_step = LEN2STEP(times*TREAD_CIRCUIT);		//目標ステップ数算出

	vd_Wait_ms(250);									//いきなり回ると姿勢が乱れるので、少し待機

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//カウントスタート
	
	//減速開始すべき位置に達するまで待つ
	while( ((times*TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;							//減速開始
	
	//停止する位置に達するまで待つ
	while((step_r + step_l) < obj_step)	;
	
	
	//モータ停止
	MTU.TSTR.BIT.CST3 = 0;							//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;							//モータのカウントをストップ


	//ターン後少し待つ
	vd_Wait_ms(250);
		
}