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

/* string.h */

#if !defined( __STRING )
#define __STRING


#if !defined( __STDDEF )
#include <stddef.h>
#endif


char *	strcat		( char *s1, const char *s2 );
char *	strncat		( char *s1, const char *s2, size_t n );
short   strcmp		( const char *s1, const char *s2);
short   stricmp		( const char *s1, const char *s2 );
short   strcmpi		( const char *s1, const char *s2 );
short   strncmp		( const char *s1, const char *s2, size_t n );
short   strnicmp	( const char *s1, const char *s2, size_t n );
short   strncmpi	( const char *s1, const char *s2, size_t n );
char *	strcpy		( char *s1, const char *s2 );
char *	strncpy		( char *s1, const char *s2, size_t n );
char *	strdup		( const char *s );

size_t  strlen		( const char *s );

char *	strchr		( const char *s, short c );
char *	strrchr		( const char *s, short c );

size_t  strspn		( const char *s, const char *set );
size_t  strcspn		( const char *s, const char *set );
char    *strpbrk	( const char *s, const char *set );

char *	strstr		( const char *src, const char *sub );
char *	strtok		( char *str, const char *set );

char *	strupr		( char *s );
char *	strlwr		( char *s );
char *	strrev		( char *s );
char *	strset		( char *s, short c );
char *	strnset		( char *s, short c, size_t n );

char *	stradj		(char *string, short dir);
char *	strerror	( short errnum );

void *	memchr		( const void *ptr, short val, size_t len );
short   memcmp		( const void *ptr1, const void *ptr2, size_t len );
void *	memcpy		( void *dest, const void *src, size_t len );
void *	memmove		( void *dest, const void *src, size_t len );
void *	memset		( void *ptr, short val, size_t len );

#define zero(x) memset(&(x), 0, sizeof(x))
#define pzero(x) memset(x, 0, sizeof(*(x)))
#define rzero(x) memset(x, 0,  sizeof(x))

/* in dlibs, not in PC lib */
short	memicmp		( const char *mem1, const char *mem2, size_t len );
void *	memccpy		( char *dst, const char *src, const char c, short cnt );
char *	stristr		( const char *string, const char *pattern);
short	strirpl		( char *string,const char *ptrn, const char *rpl, short n);
short 	strrpl		( char *string, const char *ptrn, const char *rpl, short n);
char *	strpcpy		( char *dest, char *start, char *e);
ptrdiff_t strpos	( char *string, char symbol);
ptrdiff_t strrpos	( char *string, char symbol);
char *	strrpbrk	( const char *string, const char *set);
char *	substr		( char *dest, char *source, size_t start, size_t e);
char *	subnstr		( char *dest, char *source, size_t start, size_t length);
void	swab		( char *src, char *dst, size_t n);
void *	bzero		( void *dest, size_t len);

#endif
