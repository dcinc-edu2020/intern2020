#include "buzzer_driver.h"

extern void wait_ms(int wtime);

void drv_bz(void);
void ctrl_bz(int i_freq, int i_ms);

/* �~ �� �h �V �� �h �� �V �� �t�@ �\ �~?�� */
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
/*  ���g���A���ԁims�j���w�肵�ău�U�[��炷  */
/*----------------------------------------------*/
/*  IN :int   i_freq   �c ���g��                */
/*      int   i_ms     �c ���ԁims�j            */
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
	SET_BUZZER_FREQ(i_freq);//�u�U�[�̎��g�����h�ɐݒ�
	ENABLE_BUZZER;			//�u�U�[�𔭐U������
	vd_Wait_ms(i_ms);			//1�b�ԁ@�h�̉���炷
	DISABLE_BUZZER;			//�u�U�[�̔��U���~������
}