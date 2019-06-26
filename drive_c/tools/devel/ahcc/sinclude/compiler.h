/* compiler specific defines */
/* this file is guaranteed to be included exactly once if you include
   anything at all. all site-dependent or compiler-dependent stuff
   should go here!!!
 */

#ifndef _COMPILER_H
# define _COMPILER_H 1

#if ! defined __TURBOC__
#error for Pure C, Turbo C or AHCC only
#endif

/* Undefine everything, so we get a clean slate.  */
#undef	__USE_POSIX
#undef	__USE_POSIX2
#undef	__USE_POSIX199309
#undef	__USE_XOPEN
#undef	__USE_XOPEN_EXTENDED
#undef	__USE_BSD
#undef	__USE_SVID
#undef	__USE_MISC
#undef	__USE_GNU
#undef	__USE_REENTRANT
#undef	__FAVOR_BSD
#undef	__KERNEL_STRICT_NAMES
#undef  __USE_MINTLIB

/* general library stuff */
/* __SIZE_TYPEDEF__: 	the type returned by sizeof() */
/* __PTRDIFF_TYPEDEF__: the type of the difference of two pointers */
/* __WCHAR_TYPEDEF__: 	wide character type (i.e. type of L'x') */
/* __EXITING:           the type of a function that exits */
/* __NORETURN:          attribute of a function that exits (gcc >= 2.5) */
/* __CDECL:             function must get parameters on stack */

#define __SIZE_TYPEDEF__ unsigned long
#define __PTRDIFF_TYPEDEF__ long
#define __WCHAR_TYPEDEF__ short
#define __EXITING void
#define __VA_LIST__ char *
#define __CDECL cdecl
#define __cdecl cdecl
#define __TCC_GEMLIB__
#define __NORETURN
#define __EXTERN
#define __PROTO(x) x
#define __P(x) x
#define __NULL 0L

#define _UID_T unsigned short
#define _GID_T unsigned short
#define _PID_T short

/* used in limits.h, stdio.h */
#define	_NFILE		(32)		/* maximum number of open streams */
#define atarist

#define __BEGIN_DECLS
#define __END_DECLS
#define begin_decls __BEGIN_DECLS
#define end_decls __END_DECLS

#endif /* _COMPILER_H */
