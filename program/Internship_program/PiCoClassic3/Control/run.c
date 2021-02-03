
#include "run.h"
#include "portdef.h"



extern void wait_ms(int wtime);

//extern t_control	con_wall;						//����\����

extern float		speed;


void straight(int len, float init_speed, float max_sp, float tar_speed)	//�������s
{
	int obj_step;									//�ڕW�X�e�b�v��

	max_speed  = max_sp;
	r_accel = accel;								//�����x
	
	if(init_speed < MIN_SPEED){
		speed = MIN_SPEED;
	}else{
		speed=init_speed;
	}
	
	//�ڕW���x���Œᑬ�x�������Ȃ��悤�ɂ���
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}
	if(init_speed < tar_speed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = tar_speed;
	}
	
	step_r = step_l = 0;							//�X�e�b�v���J�E���g�̃��Z�b�g
	
	con_wall.enable = true;							//�ǐ����L���ɂ���

	obj_step = LEN2STEP(len);						//�ڕW�X�e�b�v�����Z�o

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;		//�O���ɐi��

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//�J�E���g�X�^�[�g
	
	//�������J�n���n�߂�Ƃ���܂ő҂�(���Ƒ���ׂ���������������ׂ��������Z���Ȃ�����E�E�E)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel;								//��������
	
	while((step_r + step_l) < obj_step)	;			//�ڕW�n�_�܂ő��s
	
	MTU.TSTR.BIT.CST3 = 0;							//���[�^�̃J�E���g���X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;							//���[�^�̃J�E���g���X�g�b�v
	
}

void rotate(t_local_dir dir, int times){			//���M�n����
//����dir[right or left]�����ɁA90�x�~times�x��]����

	int obj_step;									//�ڕW�X�e�b�v
	int tar_speed = MIN_SPEED;						//�ڕW���x(�Œ�)
	
	slalom_enable	= false;		// �X�����[�����s���
	con_wall.enable = false;		//���M�n���񒆂͐����؂�
	
	switch(dir)										//�E�܂�肩���܂�肩�ŁA���[�^��CWCCW��؂�ւ���
	{
		case front:
		case rear:
			return;									//���M�n����Ȃ̂ŁA�O����͖���.

		case right:									//�E�ɉ��悤�ɐݒ�
			MOT_CWCCW_R = MOT_BACK;
			MOT_CWCCW_L = MOT_FORWARD;
			break;

		case left:									//���ɉ��悤�ɐݒ�
			MOT_CWCCW_R = MOT_FORWARD;
			MOT_CWCCW_L = MOT_BACK;
			break;
	}


	//�Œᑬ�x��ݒ�
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	r_accel = TURN_ACCEL;							//��]�̉����x������
	max_speed = TURN_SPEED;
	min_speed = MIN_SPEED;
	speed = MIN_SPEED;								//���x�����Z�b�g
	step_r = step_l = 0;							//�X�e�b�v�������Z�b�g
	
	obj_step = LEN2STEP(times*TREAD_CIRCUIT);		//�ڕW�X�e�b�v���Z�o

	vd_Wait_ms(250);									//�����Ȃ���Ǝp���������̂ŁA�����ҋ@

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//�J�E���g�X�^�[�g
	
	//�����J�n���ׂ��ʒu�ɒB����܂ő҂�
	while( ((times*TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;							//�����J�n
	
	//��~����ʒu�ɒB����܂ő҂�
	while((step_r + step_l) < obj_step)	;
	
	
	//���[�^��~
	MTU.TSTR.BIT.CST3 = 0;							//���[�^�̃J�E���g���X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;							//���[�^�̃J�E���g���X�g�b�v


	//�^�[���㏭���҂�
	vd_Wait_ms(250);
		
}

void rotate2(t_local_dir dir, int times){			//���M�n����
//����dir[right or left]�����ɁA90�x�~times�x��]����

	int obj_step;									//�ڕW�X�e�b�v
	int tar_speed = 500;						//�ڕW���x(�Œ�)
	
	con_wall.enable = false;						//���M�n���񒆂͐����؂�
	
	switch(dir)										//�E�܂�肩���܂�肩�ŁA���[�^��CWCCW��؂�ւ���
	{
		case front:
		case rear:
			return;									//���M�n����Ȃ̂ŁA�O����͖���.

		case right:									//�E�ɉ��悤�ɐݒ�
			MOT_CWCCW_R = MOT_BACK;
			MOT_CWCCW_L = MOT_FORWARD;
			break;

		case left:									//���ɉ��悤�ɐݒ�
			MOT_CWCCW_R = MOT_FORWARD;
			MOT_CWCCW_L = MOT_BACK;
			break;
	}


	//�Œᑬ�x��ݒ�
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	r_accel = TURN_ACCEL;							//��]�̉����x������
	max_speed = TURN_SPEED;
	min_speed = MIN_SPEED;
	speed = MIN_SPEED;								//���x�����Z�b�g
	step_r = step_l = 0;							//�X�e�b�v�������Z�b�g
	
	obj_step = LEN2STEP(times*TREAD_CIRCUIT);		//�ڕW�X�e�b�v���Z�o

	vd_Wait_ms(250);									//�����Ȃ���Ǝp���������̂ŁA�����ҋ@

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//�J�E���g�X�^�[�g
	
	//�����J�n���ׂ��ʒu�ɒB����܂ő҂�
	while( ((times*TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;							//�����J�n
	
	//��~����ʒu�ɒB����܂ő҂�
	while((step_r + step_l) < obj_step)	;
	
	
	//���[�^��~
	MTU.TSTR.BIT.CST3 = 0;							//���[�^�̃J�E���g���X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;							//���[�^�̃J�E���g���X�g�b�v


	//�^�[���㏭���҂�
	vd_Wait_ms(250);
		
}