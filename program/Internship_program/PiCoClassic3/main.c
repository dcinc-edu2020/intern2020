/*==============================================================================*/
/* Main C File									*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "led_driver.h"
#include "switch_driver.h"
#include "init.h"
#include "scheduler.h"

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void main(void);				// ���C���֐�
void vd_ExecuteSelectMode(int iModeIndex);	// �I�����[�h���s

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ���C���֐�									*/
/* 										*/
/* �e���[�h�I���X�C�b�`�̉������e�ɉ����āA�v���O�����̓���𐧌䂷��		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void main(void)
{
	int iModeIndex = 1;		// �I�����[�h�c���[�h��1�`15�܂�(4��LED�̑g�ݍ��킹��)
	
	/* �S�̏����� */
	vd_InitAll();

	/* ���[�h�I���X�C�b�`�̓��͎�t */	
	while(1)
	{
		vd_Wait_ms(CHATTERING_WAIT*3);		// �`���^�����O�h�~�̑҂�����
		
		vd_MotorPowerOFF();			// �X�e�b�s���O���[�^�[��E��

		DISABLE_BUZZER;				// �u�U�[�̔��U���~������

		while( !(SW_L & SW_C & SW_R) )
		{
			// �X�C�b�`���������܂ő҂�
		}		

		vd_Wait_ms(CHATTERING_WAIT);		// �`���^�����O�h�~�̑҂�����

		vd_DisplayLed(iModeIndex);		// ���݂̃��[�h���ԑ̑O����LED�ɕ\������

		while( (SW_L & SW_C & SW_R))
		{
			// �����ꂩ�̃X�C�b�`���������܂ő҂�
		}
	
		/* �ǂ̃X�C�b�`�������ꂽ������ */
		if(SW_L == SW_ON)				// ���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
		{
			iModeIndex++;
			if(iModeIndex > 15)			// ���[�h��15�Ԃ܂łȂ̂ŁA����𒴂��Ȃ��悤�ɂ���
			{	
				iModeIndex = 15;
			}
			else
			{
				SET_BUZZER_FREQ(INC_FREQ);	// �l�������������̎��g����ݒ�				
				ENABLE_BUZZER;			// �u�U�[�𔭐U������
			}
		}
		else if(SW_R == SW_ON)				// �E�X�C�b�`��������Ă�����O�̃��[�h�ɖ߂�
		{
			iModeIndex--;
			if(iModeIndex < 1)			// ���[�h��1�Ԃ���Ȃ̂ŁA����ȉ��ɂȂ�Ȃ��悤�ɂ���
			{
				iModeIndex = 1;
			}
			else
			{
				SET_BUZZER_FREQ(DEC_FREQ);	// �l�������������̎��g��������
				ENABLE_BUZZER;			// �u�U�[�𔭐U������
			}
		}
		else if(SW_C == SW_ON)				// �����X�C�b�`��������Ă�����A���݂̃��[�h�����s����
		{
			SET_BUZZER_FREQ(DEC_FREQ);		// ����X�C�b�`�������ꂽ�Ƃ��̉���炷
			ENABLE_BUZZER;				// �u�U�[�𔭐U������
			vd_Wait_ms(80);				// �K���ȑ҂�����
			SET_BUZZER_FREQ(INC_FREQ);		// ��(���g��)��ύX����
			vd_Wait_ms(80);				// �K���ȑ҂�����
			DISABLE_BUZZER;				// �u�U�[�̔��U���~������
			
			vd_ExecuteSelectMode(iModeIndex);	// ���݂̃��[�h�����s����
		}
		else
		{
			// None
		}
	}
}

/*==============================================================================*/
/* �I�����[�h���s								*/
/* 										*/
/* �I�����ꂽ���[�h�ԍ��ɏ]���ăv���O���������s����				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_ExecuteSelectMode(int iModeIndex)
{
	/* �X�e�b�s���O���[�^�[��㎥ */
	vd_MotorPowerON();	
	vd_Wait_ms(1000);		// �㎥����܂ŏ����҂�
	
	/* �I�����ꂽ���[�h�ԍ��ɏ]���ăv���O���������s */
	switch(iModeIndex)
	{
		case 1:
			vd_RunLefthand();	// ����@���s
			break;
		case 2:
			break;
		case 3:			
			break;			
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		case 15:
			break;
		default:
			break;	
	}
	
	/* �X�e�b�s���O���[�^�[��E�� */
	vd_MotorPowerOFF();
}
