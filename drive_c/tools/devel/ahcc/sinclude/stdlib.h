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

/* (c) by Henk Robbers <h.robbers@chello.nl> */


#if !defined( __STDLIB )
#define __STDLIB


#if !defined( __STDDEF )
#include <stddef.h>
#endif

#define EXIT_FAILURE    !0
#define EXIT_SUCCESS    0
#define RAND_MAX        32767

typedef struct
{
    short    quot;
    short    rem;
} div_t;

typedef struct
{
    long   quot;
    long   rem;
} ldiv_t;


#ifndef __NO_FLOAT__
double  atof( const char *str );
double  myatof( const char *str );
char    *ecvt( double d, short ndig, short *dec, short *sign );
char    *fcvt( double d, short ndig, short *dec, short *sign );
char    *gcvt( double value, short dec, char * buf );
double  strtod( const char *s,   const char **endptr );
#endif

short   atoi( const char *str );
long    atol( const char *str );


char    *itoa( short value, char *string, short radix );
char    *ltoa( long value, char *string, short radix );
char    *ultoa( unsigned long value, char *string, short radix );
#if 0 /* __68020__ */
char    *lltoa( long long value, char *string, short radix );
char    *ulltoa( /* unsigned */ long long value, char *string, short radix );
#endif
short   abs( short x );
long    labs( long x );
div_t   div( short n, short d );
ldiv_t  ldiv( long n, long d );

short    rand( void );
void    srand( unsigned short seed );

#define random( x ) (rand() % (x))

long    strtol( const char *str, const char **ptr, short base );
unsigned
long	strtoul(const char *str, const char **ptr, short base );

short     system( const char *command );

void    exit( short status );
void    abort( void );
short     atexit( void (*func)( void ) );

char *	getenv(const char *name);
short	putenv(const char *entry);

typedef short StdCompare(const void * p1, const void *p2);

void *	bsearch( const void *key, const void *base,
          size_t nmemb, size_t size,
          StdCompare *compar);
void *	lsearch(void *key, void *base,
		  size_t *num, size_t size,
		  StdCompare *cmp);
void *	lfind(void *key, void *base,
		  size_t *num, size_t size,
		  StdCompare *cmp);
void    qsort( void *base,
		  size_t nmemb, size_t size,
          StdCompare *compar);
void	hsort( void *base,
		  size_t nmemb, size_t size,
		  StdCompare *compar);

char *	ctlcnv(char *string);

short		brk(void *address);
void *	sbrk(size_t amount);

/*
/* maximum and minumum for any type of number */
#define max(x,y)   	(((x)>(y))?(x):(y))
#define	min(x,y)   	(((x)<(y))?(x):(y))

/* swap any objects which can be XORed */
#define	swap(a,b)	((a)=(a)^((b)=(b)^((a)=(a)^(b))))

/* lo and hi byte of a word */
#define	lobyte(x)	(((unsigned char *)&(x))[1])
#define	hibyte(x)	(((unsigned char *)&(x))[0])

/* lo and hi word of a long */
#define	loword(x)	(((unsigned short *)&(x))[1])
#define	hiword(x)	(((unsigned short *)&(x))[0])
*/

#if ! defined (_XA_MEMORY_H)
#include <ahcm.h>		/* HR: A home cooked memory allocator */
#endif

#endif
