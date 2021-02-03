/* search_maze.h */
#ifndef _SEARCH_MAZE_H
#define _SEARCH_MAZE_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "motor_driver.h"
#include "tire_control.h"
#include "run.h"

/*------------------------------------------------------------------------------*/
/* Enum Definitions								*/
/*------------------------------------------------------------------------------*/
/* 方角情報 */
typedef enum
{
	north =0,	// 北
	east  =1,	// 東
	south =2,	// 南
	west  =3,	// 西
}t_direction;

/* 自車から見た進行方向 */
//typedef enum
//{
//	north =0,	// 北
//	east  =1,	// 東
//	south =2,	// 南
//	west  =3,	// 西
//}t_direction;

/*------------------------------------------------------------------------------*/
/* Struct Definitions								*/
/*------------------------------------------------------------------------------*/
/* 壁情報を格納する構造体(ビットフィールド) */
typedef struct
{
	unsigned char north	:2;	// 北の壁情報
	unsigned char east	:2;	// 東の壁情報
	unsigned char south	:2;	// 南の壁情報
	unsigned char west	:2;	// 西の壁情報
}t_wall;

/* マイクロマウスの現在の位置情報を示す構造体 */
typedef struct
{
	short x;		// X座標
	short y;		// Y座標
	t_direction dir;	// 現在向いている方角
}t_position;

/* 迷路のマスごとの属性を保持する構造体(ビットフィールド) */
typedef struct
{
	unsigned char isUnknown	:1; // 未知か否か(今回は不使用)
	unsigned char isGoal	:1; // ゴールか否か
	unsigned char padding	:6; // 予備の領域
}t_mapFlag;

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 迷路情報 */
#define MAZESIZE_X	(6)	// 迷路の大きさ(MAZESIZE_X * MAZESIZE_Y)迷路
#define MAZESIZE_Y	(6)	// 迷路の大きさ(MAZESIZE_X * MAZESIZE_Y)迷路

/* 壁情報 */
#define NOWALL		(0)	// 壁がない場合の値
#define WALL		(1)	// 壁がある場合の値
#define UNKNOWN		(2)	// 壁があるかないか判らない状態の場合の値

/* 判定情報 */
#define GOAL		(1)	// ゴールの場合の値
#define MASK_SEARCH	(0x01)	// 探索走行用マスク値.壁情報とこの値のAND値が０（NOWALL）なら壁なしor未探索区間
#define UNEXPLORED	(0xff)	// 未探索の場合の値(255)
#define EXPLORED	(0)	// 探索済みの場合の値(0)

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
extern  t_wall	g_wall[MAZESIZE_X][MAZESIZE_Y];	//壁の情報を格納する構造体配列
extern	t_sensor	sen_r;		// 右センサ構造体
extern	t_sensor	sen_l;		// 左センサ構造体
extern	t_sensor	sen_fr;		// 右前センサ構造体
extern	t_sensor	sen_fl;		// 左前センサ構造体
extern	t_control	con_wall;	// 制御構造体

#endif