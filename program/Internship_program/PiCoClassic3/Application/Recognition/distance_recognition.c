/*==============================================================================*/
/* Distance Recognition C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "sensor_driver.h"
#include "distance_recognition.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
int rightside_dictance;			// �E�����W����
int leftside_distance;			// �������W����
int front_right_distance;		// �E�O�����W����
int front_left_distance;		// ���O�����W����

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ���W�����v��				                               		*/
/* 										*/
/* �ԑ̑O���E����E�E��ɂ��镨�̂Ƃ̋������v������				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void distance_recognition(void)
{
	/* �E�O�����W�����v�� */
	front_right_distance	= get_distance(SENSOR_FR);

	/* ���O�����W�����v�� */
	front_left_distance	= get_distance(SENSOR_FL);
	
	/* �E�����W�����v�� */
	rightside_dictance	= get_distance(SENSOR_R);
	
	/* �������W�����v�� */
	leftside_distance	= get_distance(SENSOR_L);
	
	return;
}