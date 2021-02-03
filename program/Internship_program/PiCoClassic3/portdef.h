/* portdef.h */
#ifndef _PORTDEF_H
#define _PORTDEF_H

#include "iodefine.h"


#define PORTDEF

#define BUZZER	(PORTB.PODR.BIT.B3)





#define SLED_L	(PORT5.PODR.BIT.B4)		//左センサLED
#define SLED_R	(PORT0.PODR.BIT.B5)		//右センサLED
#define SLED_FL	(PORT2.PODR.BIT.B7)		//左前センサLED
#define SLED_FR	(PORTB.PODR.BIT.B5)		//右前センサLED

#define MOT_POWER	(PORT1.PODR.BIT.B5)
#define MOT_POWER_ON	MOT_POWER = 1	// ステッピングモータを励磁
#define MOT_POWER_OFF	MOT_POWER = 0	// ステッピングモータを脱力

/* モーター駆動方向 */
/* CW：出力軸側から見て時計方向（正転） CCW：出力軸側から見て反時計方向（逆転）*/
#define MOT_CWCCW_R	(PORTC.PODR.BIT.B5)
#define MOT_CWCCW_L	(PORTC.PODR.BIT.B6)

#define BLED0	(PORTB.PODR.BIT.B1)		//バッテリ電圧表示LED 青
#define BLED1	(PORTA.PODR.BIT.B3)		//バッテリ電圧表示LED 赤


#endif
