/* This file is part of the AHCC C Library.
#if !defined( __CTYPE )
#define __CTYPE

#define	_CTc	0x01		/* control character */
		/*	declarations	*/
			is_alpha, is_alnum,		/* HR: include underline */
			is_open, is_close, is_punct;
#define toascii(c)      ((c) & 0x7f)

#endif

/************************************************************************/
