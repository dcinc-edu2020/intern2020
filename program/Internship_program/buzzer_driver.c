#include "buzzer_driver.h"

extern void wait_ms(int wtime);

void drv_bz(void);
void ctrl_bz(int i_freq, int i_ms);

/* ミ ラ ド シ ラ ド ラ シ ラ ファ ソ ミ?♪ */
int    g_freq[7] = 
		{BZ_FREQ_SO
         	,BZ_FREQ_SO
                ,BZ_FREQ_SO
                ,BZ_FREQ_FA
		,BZ_FREQ_REST
                ,BZ_FREQ_LA
                ,BZ_FREQ_SO
                };
/************************************************/
/*  周波数、時間（ms）を指定してブザーを鳴らす  */
/*----------------------------------------------*/
/*  IN :int   i_freq   … 周波数                */
/*      int   i_ms     … 時間（ms）            */
/************************************************/
void drv_bz(void)
{
	int temp = 200;
	int i_beat = 1;
	int ms = (i_beat * 60 * 1000 / 2) / temp;
	
	int cnt;
	for(cnt = 0; cnt < 7; cnt++)
	{
		ctrl_bz(g_freq[cnt], (ms * 0.9));
	}
	

}

void ctrl_bz(int i_freq, int i_ms)
{
	SET_BUZZER_FREQ(i_freq);//ブザーの周波数をドに設定
	ENABLE_BUZZER;			//ブザーを発振させる
	vd_Wait_ms(i_ms);			//1秒間　ドの音を鳴らす
	DISABLE_BUZZER;			//ブザーの発振を停止させる
}