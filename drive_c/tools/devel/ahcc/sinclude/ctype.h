/* This file is part of the AHCC C Library.   The AHCC C Library is free software; you can redistribute it and/or   modify it under the terms of the GNU Library General Public License as   published by the Free Software Foundation; either version 2 of the   License, or (at your option) any later version.   The AHCC C Library is distributed in the hope that it will be useful,   but WITHOUT ANY WARRANTY; without even the implied warranty of   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   Library General Public License for more details.   You should have received a copy of the GNU Library General Public   License along with the GNU C Library; see the file COPYING.LIB.  If not,   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,   Boston, MA 02111-1307, USA.*//* from dLibs, by Dale Schumacher */
#if !defined( __CTYPE )
#define __CTYPE

#define	_CTc	0x01		/* control character */#define	_CTd	0x02		/* numeric digit */#define	_CTu	0x04		/* upper case */#define	_CTl	0x08		/* lower case */#define	_CTs	0x10		/* whitespace */#define	_CTp	0x20		/* punctuation */#define	_CTx	0x40		/* hexadecimal */#define _CTb	0x80		/* blank */#define _CTg	0x100		/* graph */#define _CTP	0x200		/* print */
		/*	declarations	*/typedef short _CTYPE_c(short c);_CTYPE_c	isalnum, isalpha, iscntrl, isdigit, isgraph, islower,			isprint, ispunct, isspace, isupper, isxdigit,			tolower, toupper,
			is_alpha, is_alnum,		/* HR: include underline */
			is_open, is_close, is_punct;
#define toascii(c)      ((c) & 0x7f)

#endif

/************************************************************************/
