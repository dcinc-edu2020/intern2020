/*==============================================================================*/
/* Switch Driver C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "iodefine.h"
#include "switch_driver.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* スイッチ状態取得					                        */
/* 										*/
/* 指定されたスイッチのON/OFF状態を取得する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		switch_kind	スイッチ種別（赤/黄/青）		*/
/*  Return   :         	switch_state	スイッチ状態（ON/OFF）			*/
/*==============================================================================*/
int get_switch_state(int switch_kind)
{
	int switch_state = SW_OFF;
	
	switch(switch_kind)
	{
		case MODE_SW_RED:
			switch_state = SW_LEFT;
			break;
		case MODE_SW_YELLOW:
			switch_state = SW_CENTER;
			break;
		case MODE_SW_BLUE:
			switch_state = SW_RIGHT;
			break;
		default:
			break;
	}
	
	return switch_state;
}