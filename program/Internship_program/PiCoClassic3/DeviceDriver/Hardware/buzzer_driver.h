/*==============================================================================*/
/* Buzzer Driver Header File							*/
/*==============================================================================*/
#ifndef _BUZZER_DRIVER_H
#define _BUZZER_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* uU[ */
#define BUZZER		(PORTB.PODR.BIT.B3)	// uU[

/* VXeέθόg */
#define INC_FREQ	(2000)			// [hͺΑ΅½ΙΒη·ΉΜόg
#define DEC_FREQ	(1000)			// [hͺΈ­΅½ΙΒη·ΉΜόg

/* ΉKΜόg */
#define BZ_FREQ_REST    (0)			// x
#define BZ_FREQ_LA0     (440)			// iAjΜόg
#define BZ_FREQ_SI0     (494)			// ViBjΜόg
#define BZ_FREQ_DO      (523)			// hiCjΜόg
#define BZ_FREQ_RE      (587)			// iDjΜόg
#define BZ_FREQ_MI      (659)			// ~iEjΜόg
#define BZ_FREQ_FA      (698)			// t@iFjΜόg
#define BZ_FREQ_SO      (784)			// \iGjΜόg
#define BZ_FREQ_LA      (880)			// iAjΜόg
#define BZ_FREQ_SI      (988)			// ViBjΜόg
#define BZ_FREQ_DO2     (1047)			// hiCjΜόg
#define BZ_FREQ_RE2     (1174)			// iDjΜόg
#define BZ_FREQ_MI2     (1318)			// ~iEjΜόg
#define BZ_FREQ_FA2     (1396)			// t@iFjΜόg
#define BZ_FREQ_SO2     (1568)			// \iGjΜόg
#define BZ_FREQ_LA2     (1760)			// iAjΜόg
#define BZ_FREQ_SI2     (1976)			// ViBjΜόg
#define BZ_FREQ_DO3     (2094)			// hiCjΜόg

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void set_buzzer_freq(unsigned short frequency);		// uU[όgέθ
void buzzer_on(void);					// uU[­UJn
void buzzer_off(void);					// uU[­Uβ~

#endif