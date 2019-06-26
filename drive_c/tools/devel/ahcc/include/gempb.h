/* Copyright (c) 1990 - present by H. Robbers.   ANSI upgrade.
 *
 * This file is part of AHCC.
 *
 * AHCC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * AHCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AHCC; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef GEMPB_H
#define GEMPB_H

/* (c) 1990 1999 Henk Robbers Amsterdam
	1990: used in a item_selector of my own (called within trap)
	1999: adapted to modern OS's like MagiC and MiNT,
			added flexibility and compiletime compatability with original binding.

*/

#include <prelude.h>

#if 0
/* define these in your compilers -D options or in the project file */
#define G_MT	0	/* declare as 1 if you generate for Multi Threading version */
#define G_EXT	0	/* declare as 1 if you want extended bindings. */
#define G_MODIFIED	0	/* declare as 1 if you want modified bindings for:
					   evnt_button, evnt_mouse, objc_draw, form_center,
					   form_do, form_dial wind_get.... */
/* define these in your compilers -D options or in the project file */
#define G_STACK	0	/* declare as 1 if you want to compile for systems with
					   parameters all on the stack (faster bindings possible) */
#define PC_GLOB	0	/* declare as 1 if your program uses the global in GEMPARBLK of Pure C */
#endif

#if G_STACK && (sizeof(G_w) == sizeof(G_i))
	#define ON_STACK 1
	#if __TURBOC__ || __AHCC__ || __ABC__
		#define G_decl  cdecl	/* for bindings */
		#define __Cdecl cdecl	/* ALWAYS cdecl	*/
		#define CDECL 1
		#define __WGS_ELLIPSISD__ 1 	/* define this as 1 if you use the 'ellipsis'd version of wind_get & wind_set */
	#else
		#define G_decl	/* or whatever is needed */
		#define __Cdecl
	#endif
#else
	#if __TURBOC__ || __AHCC__ || __ABC__
		#define G_decl			/* for bindings */
		#define __Cdecl cdecl	/* ALWAYS cdecl */
		#define CDECL 1
		#define __WGS_ELLIPSISD__ 1 	/* define this as 1 if you use the 'ellipsis'd version of wind_get & wind_set */
	#else
		#define G_decl	/* or whatever is needed */
		#define __Cdecl
	#endif
#endif

typedef union
{
	void * spec;			/* PC_GEM */
	long l;
	int pi[2];
} private;

/* At last give in to the fact that it is a struct, NOT an array */
typedef struct aes_global
{
	int version,
		count,
		id;
	private *pprivate;
	void  **ptree;
	void *mem;
	int lmem,
		nplanes,
		res1,res2,
		bvdisk,
		bvhard;
} GLOBAL;

#define aes_global (_GemParBlk.glob)

#if G_MT									/* pass global at the user level */
	#define dglob ,GLOBAL *glob
	#define pglob glob
	#define G_n(x) MT_ ## x
	#define G_nv(x) MT_ ## x (GLOBAL *glob)	/* for void x(void) */
#else										/* use implicit global */
	#define dglob
	#if PC_GLOB								/* use PC's _GemParBlk */
		#define pglob 0L
	#else									/* use simple defaults */
		#define pglob &aes_global
	#endif
	#define G_n(x) x
	#define G_nv(x) x(void)
#endif

int __Cdecl G_trap
			(int *	contrl,			/*  4(sp) */
			 GLOBAL *	glob,			/*  8(sp) */
			 int *	intin,			/* 12(sp) */
			 int *	intout,			/* 16(sp) */
			 void *		addrin,			/* 20(sp) */
			 void *		addrout);		/* 24(sp) */

void __Cdecl _trap_vdi
			(int		handle,			/*  4(sp) */
			 int		fu,				/*  6(sp) */
			 int		ii,				/*  8(sp) */
			 int		pi,				/* 10(sp) */
			 int *	contrl,			/* 12(sp) */
			 int *	intin,			/* 16(sp) */
			 int *	ptsin,			/* 20(sp) */
			 int *	intout,			/* 24(sp) */
			 int *	ptsout);		/* 28(sp) */

typedef struct
{
	int	x, y, bstate, kstate;
} EVNTDATA;

typedef struct
{
	int out,
		x,y,
		w,h;
} MOBLK;

typedef enum
{
	MU_KEYBD =0x0001,
	MU_BUTTON=0x0002,
	MU_M1	 =0x0004,
	MU_M2	 =0x0008,
	MU_MESAG =0x0010,
	MU_TIMER =0x0020,
	MU_WHEEL =0x0040,				/* AES 4.09 & XaAES */
	MU_MX    =0x0080,				/* XaAES */
	MU_NORM_KEYBD   =0x0100,		/*   "   */
	MU_DYNAMIC_KEYBD=0x0200			/*                      keybd as a bunch of buttons, includes release of key */
} EVENT_TY;

typedef struct		/* Ereignisstruktur fÅr EVNT_multi(), Fensterdialoge, etc. */
{
	int	mwhich;
	int	mx;
	int	my;
	int	mbutton;
	int	kstate;
	int	key;
	int	mclicks;
	int	reserved[9];
	int	msg[16];
} EVNT;

typedef struct
{
	int	contrl[15];
	GLOBAL	glob;			/* keep the word global reserved for lamguage */
	int	intin[132];
	int	intout[140];
	void *	addrin[16];
	void *	addrout[16];
} GEMPARBLK;

extern  GEMPARBLK _GemParBlk;
extern  int _app,gl_apid,gl_ap_version;

int  vq_aes( void );

/* AESPB is now completely out of sight */

#endif