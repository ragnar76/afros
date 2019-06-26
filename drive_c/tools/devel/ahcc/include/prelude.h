/*  (c) 1991-2008 by H. Robbers te Amsterdam
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
#ifndef PRELUDE_H
#define PRELUDE_H

/* HR: the word global should really be kept reserved for (future?)
       use as the opposite of auto, local or static. */

#undef TRUE
#undef FALSE
#undef true
#undef false
#undef NULL
#undef null
#undef NIL
#undef nil

#ifndef __NO_FLOAT__
typedef double real;
#endif

#if ! __ABC__					/* FOR_A 0; Not for 'A' compiler. */
/* These are otherwise builtin */
	#define   and &&			/* ISO646 */
	#define   or  ||			/* ISO646 */
	#define   not !
	#define   eq  ==
	#define   ne  !=
	#define   ge  >=
	#define   le  <=
	#define   mod %
#if ! _PC_
	#define global				/* might clash with declaration in aes.h */
#endif
	#define nil 0L
	#define esac break;
	#define elif else if
	#define od while(1);		/* ; no mistake */

	#ifndef __NO_FLOAT__
		typedef double extended;
		typedef float single;
		typedef struct { double re, im; } complex;
		typedef complex compl;
	#endif
#endif		/* !__ABC__ */

#if ! __bool_true_false_are_defined
/* these are otherwise built in or provided by stdbool.h */
	typedef enum
	{
		false = 0,
		true
	} _Bool, bool;
	#define __bool_true_false_are_defined 1
#elif __AHCC__
	typedef _Bool bool;
#endif

#define othw }else{
#define NULL 0L
#define null 0L
#define NIL 0L
#define FALSE false
#define TRUE true

typedef const char Cchar;
typedef const char * Cstr;
typedef char       * Wstr;
typedef unsigned char uchar;
typedef unsigned short uint, ushort;
typedef unsigned long ulong;

#if __AHCC__
typedef short bits;				/* use these for bitfields */
typedef unsigned short ubits;
#else
/* Pure C doesnt accept short for bit fields */
typedef int bits;				/* use these for bitfields */
typedef unsigned int ubits;
#endif

#define K *1024
#define fall_thru

#define EOS '\0'
#endif
