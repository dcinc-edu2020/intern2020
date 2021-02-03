/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "search_maze.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
t_position	g_Position;
t_wall		g_Wall[MAZESIZE_X][MAZESIZE_Y];		// 迷路の壁情報を格納する構造体配列
t_mapFlag 	g_MapFlag[MAZESIZE_X][MAZESIZE_Y];	// 全てのマスの属性を保持する配列
unsigned int	g_Map[MAZESIZE_X][MAZESIZE_Y];		// 歩数マップ用の配列
unsigned int	g_MapSearched[MAZESIZE_X][MAZESIZE_Y];	// 歩数マップ用の配列

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
void init_maze(void);
void search_all_maze(int goal_x, int goal_y);
void create_map(int x_coordinate, int y_coordinate);
void init_map(int x_coordinate, int y_coordinate);
int get_priority(int x_coordinate, int y_coordinate, t_direction dir);
int judgment_nextdir(int x_coordinate, int y_coordinate, t_direction *next_dir);
void set_wall(int x_coordinate, int y_coordinate);
t_bool get_unexplores(int *x_coordinate, int *y_coordinate);

extern void tire_control(int rotation_direction_R, int rotation_direction_L, int drive_distance);
extern void go_rotate(int drive_distance, int rotation_direction_R, int rotation_direction_L);
extern void go_straight(int drive_distance, float tar_speed);
/*==============================================================================*/
/*  迷路情報の初期化			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_maze(void)
{
	int x,y;
	
	/* 迷路の全体の壁情報を未定義に設定 */
	for(x = 0; x < MAZESIZE_X; x++)
	{
		for(y = 0; y < MAZESIZE_Y; y++)
		{
			
			g_Wall[x][y].north = UNKNOWN;
			g_Wall[x][y].east  = UNKNOWN;
			g_Wall[x][y].south = UNKNOWN;
			g_Wall[x][y].west  = UNKNOWN;
			
			g_MapSearched[x][y] = UNEXPLORED;	// 全て座標を未探索にセット
		}
	}
	
	/* 迷路の四方の外壁情報の設定 */
	for(x = 0; x < MAZESIZE_X; x++)
	{
		g_Wall[x][0].south = WALL;		// 四方の壁を追加する(南)
		g_Wall[x][MAZESIZE_Y-1].north = WALL;	// 四方の壁を追加する(北)
	}
	for(y = 0; y < MAZESIZE_Y; y++)
	{
		g_Wall[0][y].west = WALL;		// 四方の壁を追加する(西)
		g_Wall[MAZESIZE_X-1][y].east = WALL;	// 四方の壁を追加する(東)
	}
	
	/* スタート地点(初期座標(0,0))の壁情報の設定 */
	g_Wall[0][0].east = WALL;				// スタート地点の右の壁を追加する
	g_Wall[1][0].west = WALL;
	g_MapSearched[0][0] = EXPLORED;
}
/*==============================================================================*/
/* 迷路の全探索				                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void search_all_maze(int goal_x, int goal_y)
{
	
	/* 探索速度の設定 */
	accel = SEARCH_ACCEL;
		
	/* 初期位置(0,0)から次に行く方向を判定 */
	t_direction next_direction;

	int next_drive;
	
	next_drive = judgment_nextdir(goal_x, goal_y, &next_direction);
	
	/* 判定した方向に進む */
	switch(next_drive)
	{
		case north:
			//straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			go_straight(STRAIGHT_HALFSECTION, SEARCH_SPEED);		// 0.5区画進む
			//g_Position.y++;							// 北を向いた時はY座標を増やす
			break;
		case east:
			//rotate(right,1);
			//straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			go_rotate(TURN_90,MOT_BACK, MOT_FORWARD);			// 右に90度旋回
			//g_Position.x++;							// 東を向いた時はX座標を増やす
			break;
		case south:
			//rotate(left,2);
			//straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			go_rotate(TURN_180,MOT_BACK, MOT_FORWARD);			// 後ろに向く(180度ターン)
			//g_Position.y--;							// 南を向いた時はY座標を減らす
			break;
		case west:
			rotate(left,1);
			straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			//go_rotate(TURN_90,MOT_FORWARD, MOT_BACK);			// 左に90度旋回
			//g_Position.x--;							// 西を向いたときはX座標を減らす
			break;
	}
	
	g_Position.dir = next_direction;	// 方向を更新
	
	switch(g_Position.dir)
	{
		case north:
			g_Position.y++;							// 北を向いた時はY座標を増やす
			break;
		case east:
			g_Position.x++;							// 東を向いた時はX座標を増やす
			break;
		case south:
			g_Position.y--;							// 南を向いた時はY座標を減らす
			break;
		case west:
			g_Position.x--;							// 西を向いたときはX座標を減らす
			break;
	}

	
	/* ゴール座標(goal_x, goal_y)に向かって迷路探索 */
	while( (g_Position.x != goal_x) || (g_Position.y != goal_y))
	{
		set_wall(g_Position.x, g_Position.y);			// 壁情報をセット
		
		/* 次に行く方向を判定 */
		next_drive = judgment_nextdir(goal_x, goal_y, &next_direction);
	
		/* 判定した方向に進む */
		switch(next_drive)
		{
			case north:
				go_straight(STRAIGHT_SECTION, SEARCH_SPEED);			// 1区画進む
				//g_Position.y++;							// 北を向いた時はY座標を増やす
				break;
			case east:
				tire_control(MOT_BACK, MOT_FORWARD, TURN_90);			// 右に90度旋回
				//g_Position.x++;							// 東を向いた時はX座標を増やす
				break;
			case south:
				tire_control(MOT_BACK, MOT_FORWARD, TURN_180);			// 後ろに向く(180度ターン)
				//g_Position.y--;							// 南を向いた時はY座標を減らす
				break;
			case west:
				tire_control(MOT_FORWARD, MOT_BACK, TURN_90);			// 左に90度旋回
				//g_Position.x--;							// 西を向いたときはX座標を減らす
				break;
		}
		
		g_Position.dir = next_direction;	// 方向を更新
		
		switch(g_Position.dir)
		{
			case north:
				g_Position.y++;							// 北を向いた時はY座標を増やす
				break;
			case east:
				g_Position.x++;							// 東を向いた時はX座標を増やす
				break;
			case south:
				g_Position.y--;							// 南を向いた時はY座標を減らす
				break;
			case west:
				g_Position.x--;							// 西を向いたときはX座標を減らす
				break;
		}
	}
	
	set_wall(g_Position.x,g_Position.y);				// 壁情報をセット
	go_straight(STRAIGHT_HALFSECTION, MIN_SPEED);			// ゴール.　0.5区画進む
}
/*==============================================================================*/
/* 進行方角判定				                                        */
/* 										*/
/* 目標(ゴール)座標X,Yに向かう場合、次に行くべき方向を判定する			*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate		目標(ゴール)位置のX座標		*/
/*			y_coordinate		目標(ゴール)位置のY座標		*/
/*			next_dir		次に行くべき方向		*/
/*  Return   :         	judgment_nextdir	進行方向			*/
/*==============================================================================*/
int judgment_nextdir(int x_coordinate, int y_coordinate, t_direction *next_dir)	
{
	int priority	 = 0;		// 進行方向の優先度
	int tmp_priority = 0;		// 進行方向の優先度(一時的)
	int min_step	 = 255;		// 最小歩数を255歩(mapがunsigned char型なので)に設定
	
	/* 歩数マップの作成 */
	create_map(x_coordinate, y_coordinate);
		
	/* 行くべき方向の判定 */
	if((g_Wall[g_Position.x][g_Position.y].north & MASK_SEARCH) == NOWALL)	// 北に壁がなければ
	{
		tmp_priority = get_priority(g_Position.x, g_Position.y + 1, north);	// 優先度を算出
		if(g_Map[g_Position.x][g_Position.y+1] < min_step)			// 一番歩数が小さい方向を見つける
		{
			min_step = g_Map[g_Position.x][g_Position.y+1];			// ひとまず北が歩数が小さい事にする
			*next_dir = north;						// 方向を保存
			priority = tmp_priority;					// 優先度を保存
		}
		else if(g_Map[g_Position.x][g_Position.y+1] == min_step)		// 歩数が同じ場合は優先度から判断する
		{
			if(priority < tmp_priority )		// 優先度を評価
			{
				*next_dir = north;		// 方向を更新
				priority = tmp_priority;	// 優先度を保存
			}
		}
	}
	
	if((g_Wall[g_Position.x][g_Position.y].east & MASK_SEARCH) == NOWALL)	// 東に壁がなければ
	{
		tmp_priority = get_priority(g_Position.x + 1, g_Position.y, east);	// 優先度を算出
		if(g_Map[g_Position.x + 1][g_Position.y] < min_step)			// 一番歩数が小さい方向を見つける
		{
			min_step = g_Map[g_Position.x+1][g_Position.y];			// ひとまず東が歩数が小さい事にする
			*next_dir = east;						// 方向を保存
			priority = tmp_priority;					// 優先度を保存
		}
		else if(g_Map[g_Position.x + 1][g_Position.y] == min_step)		// 歩数が同じ場合、優先度から判断
		{
			if(priority < tmp_priority)		// 優先度を評価
			{
				*next_dir = east;		// 方向を保存
				priority = tmp_priority;	// 優先度を保存
			}
		}
	}
	
	if((g_Wall[g_Position.x][g_Position.y].south & MASK_SEARCH) == NOWALL)	// 南に壁がなければ
	{
		tmp_priority = get_priority(g_Position.x, g_Position.y - 1, south);	// 優先度を算出
		if(g_Map[g_Position.x][g_Position.y - 1] < min_step)			// 一番歩数が小さい方向を見つける
		{
			min_step = g_Map[g_Position.x][g_Position.y-1];			// ひとまず南が歩数が小さい事にする
			*next_dir = south;						// 方向を保存
			priority = tmp_priority;					// 優先度を保存
		}
		else if(g_Map[g_Position.x][g_Position.y - 1] == min_step)		// 歩数が同じ場合、優先度で評価
		{
			if(priority < tmp_priority)		// 優先度を評価
			{
				*next_dir = south;		// 方向を保存
				priority = tmp_priority;	// 優先度を保存
			}
		}
	}
	
	if((g_Wall[g_Position.x][g_Position.y].west & MASK_SEARCH) == NOWALL)	// 西に壁がなければ
	{
		tmp_priority = get_priority(g_Position.x - 1, g_Position.y, west);	// 優先度を算出
		if(g_Map[g_Position.x-1][g_Position.y] < min_step)			// 一番歩数が小さい方向を見つける
		{
			min_step = g_Map[g_Position.x-1][g_Position.y];			// 西が歩数が小さい
			*next_dir = west;						// 方向を保存
			priority = tmp_priority;					// 優先度を保存
		}
		else if(g_Map[g_Position.x - 1][g_Position.y] == min_step)		// 歩数が同じ場合、優先度で評価
		{
			*next_dir = west;			// 方向を保存
			priority = tmp_priority;		// 優先度を保存
		}
	}

	return ( (int)((4 + *next_dir - g_Position.dir) % 4) );
}

/*==============================================================================*/
/* 優先度算出				                                        */
/* 										*/
/* 座標X,Yと、向いている方角dirから優先度を算出する				*/
/*   ・未探索が一番優先度が高い.(4)						*/
/*   ・自分の向きと行きたい方向から、前(2)横(1)後(0)として優先度を付加する	*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	目標(ゴール)位置のX座標		       	*/
/*			y_coordinate	目標(ゴール)位置のY座標			*/
/*			dir		現在向いている方角			*/
/*  Return   :         	get_priority	優先度(0～4)				*/
/*==============================================================================*/
int get_priority(int x_coordinate, int y_coordinate, t_direction dir)
{	
	int priority = 0;	// 優先度を記録する変数

	/* 優先度算出 */
	if(g_Position.dir == dir)			// 行きたい方向が現在の進行方向と同じ場合
	{
		priority = 2;	// 前
	}
	else if( ((4+g_Position.dir-dir)%4) == 2)	// 行きたい方向が現在の進行方向と逆の場合
	{
		priority = 0;	// 後
	}
	else						// それ以外(左右どちらか)の場合
	{
		priority = 1;	// 横
	}
	
	if(	(g_Wall[x_coordinate][y_coordinate].north == UNKNOWN) 		// どこかの壁情報が不明のままであれば
	     || (g_Wall[x_coordinate][y_coordinate].east  == UNKNOWN)
	     || (g_Wall[x_coordinate][y_coordinate].south == UNKNOWN)
	     || (g_Wall[x_coordinate][y_coordinate].west  == UNKNOWN))
	{
		priority += 4;	// 未探索の場合、優先度をさらに付加
	}
	
	return priority;
}

/*==============================================================================*/
/* 歩数マップの作成			                                        */
/* 										*/
/* 座標X,Yをゴールとした歩数マップを作成する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	目標(ゴール)位置のX座標		       	*/
/*			y_coordinate	目標(ゴール)位置のY座標			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void create_map(int x_coordinate, int y_coordinate)
{
	int x,y;
	t_bool change_flag;	// Map作成終了を見極めるためのフラグ
	
	/* 歩数マップの初期化 */
	init_map(x_coordinate, y_coordinate);
	
	do
	{
		change_flag = false;
		// 変更がなかった場合にはループを抜ける
		
		/* 迷路の大きさ分ループ(X座標,Y座標) */
		for(x = 0; x < MAZESIZE_X; x++)
		{
			for(y = 0; y < MAZESIZE_Y; y++)
			{
				if(g_Map[x][y] == UNEXPLORED)	// 未探索の場合は次へ
				{
					continue;
				}
				
				if(y < MAZESIZE_Y-1)				// 北：範囲チェック
				{
					if((g_Wall[x][y].north & MASK_SEARCH) == NOWALL)	// 壁がなければ
					{
						if(g_Map[x][y+1] == UNEXPLORED)			// まだ値が入っていなければ
						{
							g_Map[x][y+1] = g_Map[x][y] + 1;	// 値を代入
							change_flag = true;			// 値が更新されたことを示す
						}
					}
				}
			
				if(x < MAZESIZE_X-1)				// 東：範囲チェック
				{
					if((g_Wall[x][y].east & MASK_SEARCH) == NOWALL)		// 壁がなければ
					{
						if(g_Map[x+1][y] == UNEXPLORED)			// まだ値が入っていなければ
						{
							g_Map[x+1][y] = g_Map[x][y] + 1;	// 値を代入
							change_flag = true;			// 値が更新されたことを示す
						}
					}
				}
			
				if(y > 0)					// 南：範囲チェック
				{
					if((g_Wall[x][y].south & MASK_SEARCH) == NOWALL)	// 壁がなければ
					{
						if(g_Map[x][y-1] == UNEXPLORED)			// まだ値が入っていなければ
						{
							g_Map[x][y-1] = g_Map[x][y] + 1;	// 値を代入
							change_flag = true;			// 値が更新されたことを示す
						}
					}
				}
			
				if(x > 0)					// 西：範囲チェック
				{
					if((g_Wall[x][y].west & MASK_SEARCH) == NOWALL)		// 壁がなければ
					{
						if(g_Map[x-1][y] == UNEXPLORED)			// まだ値が入っていなければ
						{
							g_Map[x-1][y] = g_Map[x][y] + 1;	// 値を代入	
							change_flag = true;			// 値が更新されたことを示す
						}
					}
				}	
			}
		}
	}while(change_flag == true);	// 全体を作り終わるまで待つ	
}

/*==============================================================================*/
/* 歩数マップの初期化			                                        */
/* 										*/
/* 歩数マップを初期化する。全体を0xff、引数の座標X,Yは0で初期化する		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_map(int x_coordinate, int y_coordinate)
{
	int x,y;
	
	/* 迷路の大きさ分ループ(X座標,Y座標) */
	for(x = 0; x < MAZESIZE_X; x++)				
	{
		for(y = 0; y < MAZESIZE_Y; y++)
		{
			g_Map[x][y] = UNEXPLORED;	// すべて255で埋める(0xff)
		}
	}
	
	/* ゴール座標の歩数を0に設定 */
	g_Map[x_coordinate][y_coordinate] = 0;
}

/*==============================================================================*/
/* 壁情報の記録				                                        */
/* 										*/
/* 引数の座標X,Yに壁情報を書き込む						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	目標位置のX座標		       		*/
/*			y_coordinate	目標位置のY座標				*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_wall(int x_coordinate, int y_coordinate)
{
	/* 壁情報に書き込むデータ */
	int n_write;	// 北
	int s_write;	// 南
	int e_write;	// 東
	int w_write;	// 西
	
	/* 自分の方向に応じて書き込むデータを生成 */
	switch(g_Position.dir){
		case north:	// 北を向いている時
			n_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// 前壁の有無を判断
			e_write = CONV_SEN2WALL(sen_r.is_wall);				// 右壁の有無を判断
			w_write = CONV_SEN2WALL(sen_l.is_wall);				// 左壁の有無を判断
			s_write = NOWALL;						// 後ろは必ず壁がない
			break;
			
		case east:	// 東を向いているとき
			e_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// 前壁の有無を判断
			s_write = CONV_SEN2WALL(sen_r.is_wall);				// 右壁の有無を判断
			n_write = CONV_SEN2WALL(sen_l.is_wall);				// 左壁の有無を判断
			w_write = NOWALL;						// 後ろは必ず壁がない
			break;
			
		case south:	// 南を向いているとき
			s_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// 前壁の有無を判断
			w_write = CONV_SEN2WALL(sen_r.is_wall);				// 右壁の有無を判断
			e_write = CONV_SEN2WALL(sen_l.is_wall);				// 左壁の有無を判断
			n_write = NOWALL;						// 後ろは必ず壁がない
			break;
			
		case west:	// 西を向いているとき
			w_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// 前壁の有無を判断
			n_write = CONV_SEN2WALL(sen_r.is_wall);				// 右壁の有無を判断
			s_write = CONV_SEN2WALL(sen_l.is_wall);				// 左壁の有無を判断
			e_write = NOWALL;						// 後ろは必ず壁がない
			break;
	}
	
	/* 壁情報の書き込み */
	g_Wall[x_coordinate][y_coordinate].north = n_write;	
	g_Wall[x_coordinate][y_coordinate].south = s_write;
	g_Wall[x_coordinate][y_coordinate].east  = e_write;
	g_Wall[x_coordinate][y_coordinate].west  = w_write;
	
	/* 反対側から見た壁情報を書き込み */
	if(y_coordinate < MAZESIZE_Y-1)		// 範囲チェック
	{
		g_Wall[x_coordinate][y_coordinate+1].south = n_write;	// 反対側から見た壁を書き込み
	}
	
	if(x_coordinate < MAZESIZE_X-1)		// 範囲チェック
	{
		g_Wall[x_coordinate+1][y_coordinate].west = e_write;	// 反対側から見た壁を書き込み
	}
	
	if(y_coordinate > 0)			// 範囲チェック
	{
		g_Wall[x_coordinate][y_coordinate-1].north = s_write;	// 反対側から見た壁を書き込み
	}
	
	if(x_coordinate > 0)			// 範囲チェック
	{
		g_Wall[x_coordinate-1][y_coordinate].east = w_write;	// 反対側から見た壁を書き込み
	}
	
	/* 探索座標の記録 */
	g_MapSearched[x_coordinate][y_coordinate] = EXPLORED;
}

/*==============================================================================*/
/* 未探索座標の取得			                                        */
/* 										*/
/* 未探索の座標を引数のX,Yに書き込む						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	目標位置のX座標		       		*/
/*			y_coordinate	目標位置のY座標				*/
/*  Return   :         	true		未探索座標有				*/
/*			false		未探索座標無				*/
/*==============================================================================*/
t_bool get_unexplores(int *x_coordinate, int *y_coordinate)
{
	int x,y;
	t_bool get_result = false;	// 未探索座標取得結果
	
	/* 迷路の大きさ分ループ(X座標,Y座標) */
	for(x = 0; x < MAZESIZE_X; x++)				
	{
		if(get_result == true)	/* 最初に見つけた未探索座標を結果として返す */
		{
			break;
		}
		
		for(y = 0; y < MAZESIZE_Y; y++)
		{
			if(g_MapSearched[x][y] == UNEXPLORED)
			{
				*x_coordinate = x;
				*y_coordinate = y;
				get_result    = true;
				break;
			}
		}
	}
	
	return get_result;
}