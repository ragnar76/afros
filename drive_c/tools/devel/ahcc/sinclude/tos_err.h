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

/* From the mintlib modified by Henk Robbers <h.rbbers@chello.nl> */

#if !defined _TOS_ERR_H
# define _TOS_ERR_H 1         /* Allow multiple inclusion.  */

#define DEFENUM 1

enum
{
#include "mint_err.h"
	_NE_MAX
};


#endif