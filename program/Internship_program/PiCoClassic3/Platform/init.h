/* init.h */
#ifndef _INIT_H
#define _INIT_H


#include "portdef.h"
#include "iodefine.h"

#include "sensor_driver.h"
#include "buzzer_driver.h"
#include "search_maze.h"

#include "common.h"

#include "sensor_driver.h"

#define INC_FREQ	(2000)				//モードが増加した時に鳴らす音の周波数
#define DEC_FREQ	(1000)				//モードが減少した時に鳴らす音の周波数

#define IO_OUT	(1)					//PFCのInput/Output レジスタに1を設定すると出力になる
#define IO_IN	(0)					//PFCのInput/Output レジスタに0を設定すると入力になる

void vd_InitAll(void);		//全部初期化(全部を呼び出す)
void init_clock(void);		//CPUの動作周波数を設定
void init_io(void);		//IOポート初期化
void init_cmt(void);		//CMT初期化
void init_mtu(void);		//MTU設定
void init_adc(void);		//AD初期化
//void init_sci(void);		//SCI初期化
extern void init_motor(void);
extern void init_parameters(void);	//パラメータ初期化
extern void init_maze(void);		//迷路情報の初期

extern void wait_ms(int wtime); 

extern t_sensor	sen_r, sen_l, sen_fr, sen_fl;	//センサ構造体

#endif