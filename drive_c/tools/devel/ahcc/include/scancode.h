/********************************/
/* file scancode.h              */
/* Holger Weets & Frank Specht  */
/* letzte Aenderung: 28.01.90   */
/* back to UK  HR:   15.04.92   */
/********************************/
#ifndef __SCANCODE_H
#define __SCANCODE_H

typedef enum
{
	CNTRL_A =	0x1e01,
	CNTRL_B =	0x3002,
	CNTRL_C =	0x2e03,
	CNTRL_D =	0x2004,
	CNTRL_E =	0x1205,
	CNTRL_F =	0x2106,
	CNTRL_G =	0x2207,
	CNTRL_H =	0x2308,
	CNTRL_I =	0x1709,
	CNTRL_J =	0x240a,
	CNTRL_K =	0x250b,
	CNTRL_L =	0x260c,
	CNTRL_M =	0x320d,
	CNTRL_N =	0x310e,
	CNTRL_O =	0x180f,
	CNTRL_P =	0x1910,
	CNTRL_Q =	0x1011,
	CNTRL_R =	0x1312,
	CNTRL_S =	0x1f13,
	CNTRL_T =	0x1414,
	CNTRL_U =	0x1615,
	CNTRL_V =	0x2f16,
	CNTRL_W =	0x1117,
	CNTRL_X =	0x2d18,
	CNTRL_Y =	0x1519,		/* 4'92 */
	CNTRL_Z =	0x2c1a,		/* 4'92 */
	CNTRL_AE =	0X2804,
	CNTRL_OE =	0x2714,
	CNTRL_UE =	0x1a01,
	CNTRL_1 =	0x0211,
	CNTRL_2 =	0x0300,
	CNTRL_3 =	0x0413,
	CNTRL_4 =	0x0514,
	CNTRL_5 =	0x0615,
	CNTRL_6 =	0x071e,
	CNTRL_7 =	0x0817,
	CNTRL_8 =	0x0918,
	CNTRL_9 =	0x0a19,
	CNTRL_0 =	0x0b10,
	CNTRL_CL =	0x7300,
	CNTRL_CR =	0x7400,
	CNTRL_HOME =	0x7700,
	CNTRL_DEL =	0x531F,
	CNTRL_SP  =	0x3900,

	ALT_A   =	0x1e00,
	ALT_B   =	0x3000,
	ALT_C   =	0x2e00,
	ALT_D   =	0x2000,
	ALT_E   =	0x1200,
	ALT_F   =	0x2100,
	ALT_G   =	0x2200,
	ALT_H   =	0x2300,
	ALT_I   =	0x1700,
	ALT_J   =	0x2400,
	ALT_K   =	0x2500,
	ALT_L   =	0x2600,
	ALT_M   =	0x3200,
	ALT_N   =	0x3100,
	ALT_O   =	0x1800,
	ALT_P   =	0x1900,
	ALT_Q   =	0x1000,
	ALT_R   =	0x1300,
	ALT_S   =	0x1f00,
	ALT_T   =	0x1400,
	ALT_U   =	0x1600,
	ALT_V   =	0x2f00,
	ALT_W   =	0x1100,
	ALT_X   =	0x2d00,
	ALT_Y   =	0x2c00,
	ALT_Z   =	0x1500,
	ALT_AE  =	0x285d,
	ALT_OE  =	0x275b,
	ALT_UE  =	0x1a40,
	ALT_1   =	0x7800,	 /* ab TOS x.06 allein alpha blok */
	ALT_2   =	0x7900,
	ALT_3   =	0x7a00,
	ALT_4   =	0x7b00,
	ALT_5   =	0x7c00,
	ALT_6   =	0x7d00,
	ALT_7   =	0x7e00,
	ALT_8   =	0x7f00,
	ALT_9   =	-0x8000,
	ALT_0   =	-0x7f00,

	SH_ALT_AE   =	0x287d,
	SH_ALT_OE   =	0x277b,
	SH_ALT_UE   =	0x1a5c,

	ESCAPE  =  0x011b,
	BACKSPACE   =	0x0e08,
	DELETE  =	0x537f,
	INSERT  =	0x5200,
	SHFT_INS	=	0x5230,
	RETURN  =	0x1c0d,
	ENTER   =	0x720d,
	CUR_UP  =	0x4800,
	SHFT_CU =	0x4838,
	CUR_LEFT =	0x4b00,
	SHFT_CL =	0x4b34,
	CUR_RIGHT   =	0x4d00,
	SHFT_CR =	0x4d36,
	CUR_DOWN =	0x5000,
	SHFT_CD =	0x5032,
	HOME    =	0x4700,
	SHFT_HOME   =	0x4737,
	UNDO    =	0x6100,
	TAB     =	0x0f09,
	HELP    =	0x6200,
	F1      =	0x3b00,
	SHFT_F1 =	0x5400,
	F2      =	0x3c00,
	SHFT_F2 =	0x5500,
	F3      =	0x3d00,
	SHFT_F3 =	0x5600,
	F4      =	0x3e00,
	SHFT_F4 =	0x5700,
	F5      =	0x3f00,
	SHFT_F5 =	0x5800,
	F6      =	0x4000,
	SHFT_F6 =	0x5900,
	F7      =	0x4100,
	SHFT_F7 =	0x5a00,
	F8      =	0x4200,
	SHFT_F8 =	0x5b00,
	F9      =  0x4300,
	SHFT_F9 =	0x5c00,
	F10     =	0x4400,
	SHFT_F10	=	0x5d00
} SCANCODE;

#endif