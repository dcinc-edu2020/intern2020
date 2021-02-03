/* buzzer_driver.h */
#ifndef _BUZZER_DRIVER_H
#define _BUZZER_DRIVER_H

#include "portdef.h"
#include "iodefine.h"

#include "common.h"

#define SET_BUZZER_FREQ(f)	MTU0.TGRB=(unsigned short)(12000000/(f));MTU0.TGRA=(unsigned short)(6000000/(f))	//ブザーの発振周波数を算出して、設定

#define ENABLE_BUZZER		PORTB.PMR.BIT.B3=1;MTU.TSTR.BIT.CST0=1	//ブザーの発振を開始
#define DISABLE_BUZZER		PORTB.PMR.BIT.B3=0;MTU.TSTR.BIT.CST0=0	//ブザーの発振を停止

extern void drv_bz(void);
 
//ブザーMTUポート
#define MTU_BZ              MTU2.TSTR.BIT.CST2   //ブザー用MTU
//ブザーMTU発振数
#define MTU_BZ_CLOCK        24000000              //ブザー用MTUの発振数（24MHz）
//ブザーMTUレジスタ
//#define MTU_BZ_CYCLE        MTU22.TGRB            //ブザー周期を設定
//#define MTU_BZ_PULSWIDTH    MTU22.TGRA            //ブザーパルス幅を設定

//ブザー ON/OFF
#define BZ_ON           1                      //ブザー ON
#define BZ_OFF          0                      //ブザー OFF
//音階の周波数
#define BZ_FREQ_REST    0                      // 休符
#define BZ_FREQ_LA0     440                    // ラ（A）の周波数
#define BZ_FREQ_SI0     494                    // シ（B）の周波数
#define BZ_FREQ_DO      523                    // ド（C）の周波数
#define BZ_FREQ_RE      587                    // レ（D）の周波数
#define BZ_FREQ_MI      659                    // ミ（E）の周波数
#define BZ_FREQ_FA      698                    // ファ（F）の周波数
#define BZ_FREQ_SO      784                    // ソ（G）の周波数
#define BZ_FREQ_LA      880                    // ラ（A）の周波数
#define BZ_FREQ_SI      988                    // シ（B）の周波数
#define BZ_FREQ_DO2     1047                   // ド（C）の周波数
#define BZ_FREQ_RE2     1174                   // レ（D）の周波数
#define BZ_FREQ_MI2     1318                   // ミ（E）の周波数
#define BZ_FREQ_FA2     1396                   // ファ（F）の周波数
#define BZ_FREQ_SO2     1568                   // ソ（G）の周波数
#define BZ_FREQ_LA2     1760                   // ラ（A）の周波数
#define BZ_FREQ_SI2     1976                   // シ（B）の周波数
#define BZ_FREQ_DO3     2094                   // ド（C）の周波数

#endif