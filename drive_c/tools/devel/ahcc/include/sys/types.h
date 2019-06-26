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

/*      TYPES.H
 *
 *      Dummy POSIX sys/types.h header for compatibility:
 *      http://pubs.opengroup.org/onlinepubs/007908799/xsh/systypes.h.html
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

/* sys/types.h typedefs types used by in POSIX stat struct, but
 * as AHCC stat struct uses just ints & size_t, this is enough:
 */
#include <stddef.h>

#endif
