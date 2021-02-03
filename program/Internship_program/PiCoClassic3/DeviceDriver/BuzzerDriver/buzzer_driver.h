/* buzzer_driver.h */
#ifndef _BUZZER_DRIVER_H
#define _BUZZER_DRIVER_H

#include "portdef.h"
#include "iodefine.h"

#include "common.h"

#define SET_BUZZER_FREQ(f)	MTU0.TGRB=(unsigned short)(12000000/(f));MTU0.TGRA=(unsigned short)(6000000/(f))	//�u�U�[�̔��U���g�����Z�o���āA�ݒ�

#define ENABLE_BUZZER		PORTB.PMR.BIT.B3=1;MTU.TSTR.BIT.CST0=1	//�u�U�[�̔��U���J�n
#define DISABLE_BUZZER		PORTB.PMR.BIT.B3=0;MTU.TSTR.BIT.CST0=0	//�u�U�[�̔��U���~

extern void drv_bz(void);
 
//�u�U�[MTU�|�[�g
#define MTU_BZ              MTU2.TSTR.BIT.CST2   //�u�U�[�pMTU
//�u�U�[MTU���U��
#define MTU_BZ_CLOCK        24000000              //�u�U�[�pMTU�̔��U���i24MHz�j
//�u�U�[MTU���W�X�^
//#define MTU_BZ_CYCLE        MTU22.TGRB            //�u�U�[������ݒ�
//#define MTU_BZ_PULSWIDTH    MTU22.TGRA            //�u�U�[�p���X����ݒ�

//�u�U�[ ON/OFF
#define BZ_ON           1                      //�u�U�[ ON
#define BZ_OFF          0                      //�u�U�[ OFF
//���K�̎��g��
#define BZ_FREQ_REST    0                      // �x��
#define BZ_FREQ_LA0     440                    // ���iA�j�̎��g��
#define BZ_FREQ_SI0     494                    // �V�iB�j�̎��g��
#define BZ_FREQ_DO      523                    // �h�iC�j�̎��g��
#define BZ_FREQ_RE      587                    // ���iD�j�̎��g��
#define BZ_FREQ_MI      659                    // �~�iE�j�̎��g��
#define BZ_FREQ_FA      698                    // �t�@�iF�j�̎��g��
#define BZ_FREQ_SO      784                    // �\�iG�j�̎��g��
#define BZ_FREQ_LA      880                    // ���iA�j�̎��g��
#define BZ_FREQ_SI      988                    // �V�iB�j�̎��g��
#define BZ_FREQ_DO2     1047                   // �h�iC�j�̎��g��
#define BZ_FREQ_RE2     1174                   // ���iD�j�̎��g��
#define BZ_FREQ_MI2     1318                   // �~�iE�j�̎��g��
#define BZ_FREQ_FA2     1396                   // �t�@�iF�j�̎��g��
#define BZ_FREQ_SO2     1568                   // �\�iG�j�̎��g��
#define BZ_FREQ_LA2     1760                   // ���iA�j�̎��g��
#define BZ_FREQ_SI2     1976                   // �V�iB�j�̎��g��
#define BZ_FREQ_DO3     2094                   // �h�iC�j�̎��g��

#endif