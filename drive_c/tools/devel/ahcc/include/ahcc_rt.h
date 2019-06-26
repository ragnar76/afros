/* Copyright (c) 2006 by H. Robbers.
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

/* This file is invoked by AHCC before any byte is compiled.
   Its purpose is a flexible way of handling all kinds of AHCC
   specific, mostly non standard, stuff.
   The file is read automatically without the need for a #include
 */

/* Aint & Auint are defined such that you will always get 2-byte
   ints independent of __INT4__ setting.
   It is mainly intended for use with AHCCLIB header files.
   AHCCLIB is a 16-bit int library, but you can have a 32-bit
   int application.
*/

#ifndef AHCC_RUN_H
#define AHCC_RUN_H

#if __ABC__ || __AHCC__

	#define operator __OP__
	#define cast __UC__

	#if __INT4__
		typedef short Aint;
		typedef unsigned short Auint;
	#else
		typedef int Aint;
		typedef unsigned int Auint;

	#endif

	#if __COLDFIRE__
		typedef long CFi;
		typedef unsigned long CFui;
	#else
		typedef int CFi;
		typedef unsigned int CFui;
	#endif

	#if (__68020__ || __COLDFIRE__)
		#if __LONGLONG__
		/* long long stuff; routines in ahcclib\ll.s */

			#define ll long long

			ll operator + (ll, ll) _lladd;	/*  */
			ll operator - (ll, ll) _llsub;	/*  */
			ll operator * (ll, ll) _llmul;	/*  */
			ll operator / (ll, ll) _lldiv;	/*  */
			ll operator % (ll, ll) _llmod;
			ll operator & (ll, ll) _lland;	/*  */
			ll operator | (ll, ll) _llor;	/*  */
			ll operator ^ (ll, ll) _lleor;	/*  */
			ll operator << (ll, ll) _llshl;
			ll operator >> (ll, ll) _llshr;

			_Bool operator == (ll, ll) _lleq;		/*  */
			_Bool operator != (ll, ll) _llne;		/*  */
			_Bool operator <  (ll, ll) _lllt;		/*  */
			_Bool operator >  (ll, ll) _llgt;		/*  */
			_Bool operator >= (ll, ll) _llge;		/*  */
			_Bool operator <= (ll, ll) _llle;		/*  */

			ll operator - (ll) _llneg;

			ll cast	(char)			_b2ll;		/*  */
			ll cast (unsigned char) _ub2ll;		/*  */
			ll cast	(short)			_s2ll;		/*  */
			ll cast (unsigned short) _us2ll;	/*  */
			ll cast	(long)			_l2ll;		/*  */
			ll cast (unsigned long) _ul2ll;		/*  */

			ll cast	(float)		_f2ll;
			float cast (ll)		_ll2f;
			ll cast	(double)	_d2ll;
			double cast(ll) 	_ll2d;

			#undef ll
		#endif
	#else
/*		#message long multiply, mod and divide handled by software	*/
		#define __HAVE_SW_LONG_MUL_DIV__ 1
		/* The operands are casted before the existence of these operator
		   overloads are examined, so the below will suffice. */
		unsigned long operator / (unsigned long, unsigned long) _uldiv;
		         long operator / (         long,          long) _ldiv;
		unsigned long operator * (unsigned long, unsigned long) _ulmul;
		         long operator * (         long,          long) _lmul;
		unsigned long operator % (unsigned long, unsigned long) _ulmod;
		         long operator % (         long,          long) _lmod;
	#endif

	#undef operator
	#undef cast
#endif

typedef void VpV(void);

#endif
