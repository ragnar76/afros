/*      STDDEF.H

        Standard Type Definition Includes

        Copyright (c) Borland International 1990
        All Rights Reserved.
*/


#if !defined( __STDDEF )
#define __STDDEF

typedef unsigned long   size_t;
#ifndef _COMPILER_H
typedef unsigned long	__SIZE_TYPEDEF__;
#endif
typedef long            ptrdiff_t;
#define _SIZE_T

#if __AHCC__
#define offsetof(type, ident) __offsetof__ type.ident
#else
#define offsetof(type,ident)   ((size_t)&(((type *)0)->ident))
#endif

#ifndef NULL
#define NULL 0L
#endif

#endif
