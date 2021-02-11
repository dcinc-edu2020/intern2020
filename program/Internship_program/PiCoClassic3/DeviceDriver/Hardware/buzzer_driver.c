/*==============================================================================*/
/* Buzzer Driver C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "buzzer_driver.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ブザー周波数設定								*/
/* 										*/
/* ブザーの周波数を設定する							*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		frequency	ブザー周波数			       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_buzzer_freq(unsigned short frequency)
{
	// ブザーの発振周波数を算出して設定
	MTU0.TGRB = (unsigned short)(12000000 / (frequency));
	MTU0.TGRA = (unsigned short)(6000000  / (frequency));	
	
	return;
}

/*==============================================================================*/
/* ブザー発振開始								*/
/* 										*/
/* ブザーを吹鳴させる								*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void buzzer_on(void)
{
	// ブザーの発振を開始
	PORTB.PMR.BIT.B3  = BZ_ON;
	MTU.TSTR.BIT.CST0 = BZ_ON;	

	return;
}

/*==============================================================================*/
/* ブザー発振停止								*/
/* 										*/
/* ブザー吹鳴を停止させる							*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void buzzer_off(void)
{
	//ブザーの発振を停止
	PORTB.PMR.BIT.B3  = BZ_OFF;
	MTU.TSTR.BIT.CST0 = BZ_OFF;
	
	return;
}

/*==============================================================================*/
/* ブザー吹鳴									*/
/* 										*/
/* 指定した時間・周波数に応じてブザー音を鳴らす					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void sound_buzzer(int frequency, int ms_time)
{
	set_buzzer_freq(frequency);		// 指定した音(周波数)を設定する
	buzzer_on();				// ブザーを発振させる
	wait_ms(ms_time);			// 指定した時間[ms]分鳴らす
	buzzer_off();				// ブザーの発振を停止させる
	
	return;
}