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

#if  __AHCC__

	#ifdef	_ASSERT_H

	# undef	_ASSERT_H
	# undef	assert

	#endif

	#define	_ASSERT_H	1

/* If NDEBUG is defined, do nothing.
   If not, and EXPRESSION is zero, print an error message and abort.  */

	#ifdef	NDEBUG

	# define assert(expr) ((void)0)

	#else 			/* Not NDEBUG.  */

	void _Assert(void *);

	# define _VAL(x) #x
	# define assert(test) ((test) || (_Bool)_Assert(__FILE__ ":" _VAL(__LINE__) " " #test))

	#endif		/* NDEBUG */

#else		/* Pure C */

	#if !defined( __ASSERT )
	#define __ASSERT

	#if !defined(NDEBUG)

	#if     !defined(__STDLIB)
	#include <stdlib.h>
	#endif

	#if     !defined( __STDIO )
	#include <stdio.h>
	#endif

	#define assert( expr )\
		((void)((expr)||(fprintf( stderr, \
		"\nAssertion failed: %s, file %s, line %d\n",\
		 #expr, __FILE__, __LINE__ ),\
		 ((short (*)(void))abort)())))
	#else

	#define assert( expr )

	#endif		/* NDEBUG */

	#endif		/* __ASSERT */
#endif
