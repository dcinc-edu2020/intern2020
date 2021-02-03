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

#define INC_FREQ	(2000)				//���[�h�������������ɖ炷���̎��g��
#define DEC_FREQ	(1000)				//���[�h�������������ɖ炷���̎��g��

#define IO_OUT	(1)					//PFC��Input/Output ���W�X�^��1��ݒ肷��Əo�͂ɂȂ�
#define IO_IN	(0)					//PFC��Input/Output ���W�X�^��0��ݒ肷��Ɠ��͂ɂȂ�

void vd_InitAll(void);		//�S��������(�S�����Ăяo��)
void init_clock(void);		//CPU�̓�����g����ݒ�
void init_io(void);		//IO�|�[�g������
void init_cmt(void);		//CMT������
void init_mtu(void);		//MTU�ݒ�
void init_adc(void);		//AD������
//void init_sci(void);		//SCI������
extern void init_motor(void);
extern void init_parameters(void);	//�p�����[�^������
extern void init_maze(void);		//���H���̏���

extern void wait_ms(int wtime); 

extern t_sensor	sen_r, sen_l, sen_fr, sen_fl;	//�Z���T�\����

#endif