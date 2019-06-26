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

/*
 *	BASEPAGE.H	Definition of the basepage structure
 */

#ifndef BASEP_H
#define	BASEP_H

typedef struct basep
{
	char		*p_lowtpa;	/* pointer to self (bottom of TPA) */
	char		*p_hitpa;	/* pointer to top of TPA + 1 */
	char		*p_tbase;	/* base of text segment */
	long		p_tlen;		/* length of text segment */
	char		*p_dbase;	/* base of data segment */
	long		p_dlen;		/* length of data segment */
	char		*p_bbase;	/* base of BSS segment */
	long		p_blen;		/* length of BSS segment */
	char		*p_dta;		/* pointer to current DTA */
	struct basep	*p_parent;	/* pointer to parent's basepage */
	char		*p_reserved;	/* reserved for future use */
	char		*p_env;		/* pointer to environment string */
	long		p_undef[20];	/* scratch area... don't touch */
	char		p_cmdlin[128];	/* command line image */
} BASEPAGE;

extern	BASEPAGE	*_base;

#endif BASEP_H
