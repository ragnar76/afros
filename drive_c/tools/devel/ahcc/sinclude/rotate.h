/* Copyright (c) 2014 by H. Robbers.
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

/* Also usable with Pure C */
#ifndef ROTATE_H
#define ROTATE_H

#if __COLDFIRE__
/* rotate macros for Coldfire compatible code */
#define __rorb(a,n) (((unsigned char)a>>n)|((unsigned char)a<<((sizeof(a)*8)-n)))
#define __ror (a,n) (((unsigned  int)a>>n)|((unsigned  int)a<<((sizeof(a)*8)-n)))
#define __rorl(a,n) (((unsigned long)a>>n)|((unsigned long)a<<((sizeof(a)*8)-n)))

#define __rolb(a,n) (((unsigned char)a<<n)|((unsigned char)a>>((sizeof(a)*8)-n)))
#define __rol (a,n) (((unsigned  int)a<<n)|((unsigned  int)a>>((sizeof(a)*8)-n)))
#define __roll(a,n) (((unsigned long)a<<n)|((unsigned long)a>>((sizeof(a)*8)-n)))
#else
/* rotate macros for M68K code */
int rorb(char a, int n) 0161070;
int ror (int  a, int n) 0161170;
int rorl(long a, int n) 0161270;

int rolb(char a, int n) 0161470;
int rol (int  a, int n) 0161570;
int roll(long a, int n) 0161670;

#endif

#endif