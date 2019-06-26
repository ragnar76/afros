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

#if !defined( __STDDEF )
#define __STDDEF

typedef unsigned long   size_t;
#ifndef _COMPILER_H
typedef unsigned long	__SIZE_TYPEDEF__;
#endif
typedef long            ptrdiff_t;
#define _SIZE_T

#if __AHCC__
#define offsetof(type, ident) __offsetof__ type.ident
#else
#define offsetof(type,ident)   ((size_t)&(((type *)0)->ident))
#endif

/* test autodepend: change this line */

#ifndef NULL
#define NULL 0L
#endif

#endif
