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
void main(void);				// メイン関数
void vd_ExecuteSelectMode(int iModeIndex);	// 選択モード実行

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* メイン関数									*/
/* 										*/
/* 各モード選択スイッチの押下内容に応じて、プログラムの動作を制御する		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void main(void)
{
	int iModeIndex = 1;		// 選択モード…モードは1～15まで(4つのLEDの組み合わせ分)
	
	/* 全体初期化 */
	vd_InitAll();

	/* モード選択スイッチの入力受付 */	
	while(1)
	{
		vd_Wait_ms(CHATTERING_WAIT*3);		// チャタリング防止の待ち時間
		
		vd_MotorPowerOFF();			// ステッピングモーターを脱力

		DISABLE_BUZZER;				// ブザーの発振を停止させる

		while( !(SW_L & SW_C & SW_R) )
		{
			// スイッチが離されるまで待つ
		}		

		vd_Wait_ms(CHATTERING_WAIT);		// チャタリング防止の待ち時間

		vd_DisplayLed(iModeIndex);		// 現在のモードを車体前方のLEDに表示する

		while( (SW_L & SW_C & SW_R))
		{
			// いずれかのスイッチが押されるまで待つ
		}
	
		/* どのスイッチが押されたか判定 */
		if(SW_L == SW_ON)				// 左スイッチが押されていたら次のモードに進む
		{
			iModeIndex++;
			if(iModeIndex > 15)			// モードは15番までなので、それを超えないようにする
			{	
				iModeIndex = 15;
			}
			else
			{
				SET_BUZZER_FREQ(INC_FREQ);	// 値が増加した時の周波数を設定				
				ENABLE_BUZZER;			// ブザーを発振させる
			}
		}
		else if(SW_R == SW_ON)				// 右スイッチが押されていたら前のモードに戻る
		{
			iModeIndex--;
			if(iModeIndex < 1)			// モードは1番からなので、それ以下にならないようにする
			{
				iModeIndex = 1;
			}
			else
			{
				SET_BUZZER_FREQ(DEC_FREQ);	// 値が減少した時の周波数を決定
				ENABLE_BUZZER;			// ブザーを発振させる
			}
		}
		else if(SW_C == SW_ON)				// 中央スイッチが押されていたら、現在のモードを実行する
		{
			SET_BUZZER_FREQ(DEC_FREQ);		// 決定スイッチが押されたときの音を鳴らす
			ENABLE_BUZZER;				// ブザーを発振させる
			vd_Wait_ms(80);				// 適当な待ち時間
			SET_BUZZER_FREQ(INC_FREQ);		// 音(周波数)を変更する
			vd_Wait_ms(80);				// 適当な待ち時間
			DISABLE_BUZZER;				// ブザーの発振を停止させる
			
			vd_ExecuteSelectMode(iModeIndex);	// 現在のモードを実行する
		}
		else
		{
			// None
		}
	}
}

/*==============================================================================*/
/* 選択モード実行								*/
/* 										*/
/* 選択されたモード番号に従ってプログラムを実行する				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void vd_ExecuteSelectMode(int iModeIndex)
{
	/* ステッピングモーターを励磁 */
	vd_MotorPowerON();	
	vd_Wait_ms(1000);		// 励磁するまで少し待つ
	
	/* 選択されたモード番号に従ってプログラムを実行 */
	switch(iModeIndex)
	{
		case 1:
			vd_RunLefthand();	// 左手法走行
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
	
	/* ステッピングモーターを脱力 */
	vd_MotorPowerOFF();
}
