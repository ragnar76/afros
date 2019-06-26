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

/* HR: Do away with all this GCC gibberish */

#ifndef __GIBBERISH_H
#define __GIBBERISH_H

#undef __THROW
#define __THROW

#undef __BEGIN_DECLS
#define __BEGIN_DECLS

#undef __END_DECLS
#define __END_DECLS

#undef __PROTO
#define __PROTO(x) x

/* Please add more gibberish here when encountered */

#undef NORETURN
#define NORETURN

#undef inline
#define inline

#endif
