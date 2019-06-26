/* This file is part of the AHCC C Library.

   The AHCC C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The AHCC C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/


#ifndef _AHCC_LIMITS_H_
#define _AHCC_LIMITS_H_	1

/* These assume 8-bit char's, 16-bit short int's,
   and 16 or 32-bit int's and 32-bit long int's.  */


#define  CHAR_BIT		 8
#define  INT_BIT		(sizeof(int)*CHAR_BIT)		/* HR */
#define  SHORT_BIT		(sizeof(short)*CHAR_BIT)	/* HR */
#define  LONG_BIT		(sizeof(long)*CHAR_BIT)		/* HR */
#define  SCHAR_MIN		(-128)
#define  SCHAR_MAX		  127
#define  UCHAR_MAX	      255U

#if __CHAR_UNSIGNED__
	#define  CHAR_MIN        0
	#define  CHAR_MAX        UCHAR_MAX
#else
	#define  CHAR_MIN        SCHAR_MIN
	#define  CHAR_MAX        SCHAR_MAX
#endif

#define  MB_LEN_MAX          1

#define  LONG_MIN (-2147483647L-1)
#define  LONG_MAX   2147483647L
#define  ULONG_MAX  4294967295LU
#define  SHRT_MIN      (-32767-1)
#define  SHRT_MAX        32767
#define  USHRT_MAX       65535U

#if sizeof(int) == 2			/* 16 bit int's */
#define  INT_MIN     SHRT_MIN
#define  INT_MAX     SHRT_MAX
#define  UINT_MAX    USHRT_MAX
#else
#define  INT_MIN     LONG_MIN
#define  INT_MAX     LONG_MAX
#define  UINT_MAX    ULONG_MAX
#endif

#if __LONG_LONG__
#define LLONG_MAX 9223372036854775807LL
#define LLONG_MIN (-LLONG_MAX - 1LL)

#define ULLONG_MAX 18446744073709551615ULL
#endif

#endif
