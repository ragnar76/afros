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

#if ! __bool_true_false_are_defined		/* always defined by AHCC itself */

	typedef enum
	{
		false = 0,
		true
	} _Bool, bool;

#	define __bool_true_false_are_defined 1

#elif __AHCC__
	/* AHCC has builtin boolean constants 'false' and 'true'.
	   and basic boolean type _Bool (C99) */

	typedef _Bool bool;

#endif

#if ! defined FALSE

#	define FALSE false
#	define TRUE  true

#endif
