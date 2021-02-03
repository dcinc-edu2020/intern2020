/* slalom.h */
#ifndef _SLALOM_H
#define _SLALOM_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "motor_driver.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/

/* �X�����[���O���p�p�����[�^ */
#define OFFSET_SECTION		(10)				// 10[mm] �c�J�[�u�O��ɓ����I�t�Z�b�g���(���i)
#define ACTUAL_RADIUS		(90-OFFSET_SECTION)		// 80[mm] �c���ۂɑ��s����~�ʋO���̔��a
#define ACTUAL_ARC		(ACTUAL_RADIUS * 2 * PI) / 4	// ��125.7[mm] �c���ۂɑ��s����~�ʂ̋���

#define INNER_STEP_SLALOM	()
#define OUTER_STEP_SLALOM	()

#endif