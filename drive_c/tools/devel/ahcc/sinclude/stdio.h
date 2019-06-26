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

/* stdio.h */

#if !defined( __STDIO_H_ )
#define __STDIO_H_

#include <stdarg.h>

#if !defined( __STDDEF )
#include <stddef.h>
#endif

typedef unsigned long   fpos_t;

#include <errno.h>

/* old
typedef	struct
{
	short		     _cnt;		/* # of bytes in buffer */
	unsigned char	*_ptr;		/* current buffer pointer */
	unsigned char	*_base;		/* base of file buffer */
	unsigned short	_flag;		/* file status flags */
	short		    _file;		/* file handle */
	size_t		    _bsiz;		/* buffer size */
	unsigned char	_ch;		/* tiny buffer, for "unbuffered" i/o */
}
FILE;
*/
/* Try to make Pure C and AHCC FILE structure alike */
typedef	struct
{
	unsigned char	*BufPtr;	/* current buffer pointer */
	long		     _cnt;		/* # of bytes in buffer */
	unsigned char	*BufStart;	/* base of file buffer */
	size_t		    _bsiz;		/* buffer size */
	short		    Handle;		/* file handle */
	unsigned char	Flags,Mode;		/* file status flags, file mode */
	unsigned char	ChrBuf;		/* tiny buffer, for "unbuffered" i/o */
	char ungetFlag;
}
FILE;

typedef short InFunc(void *ip);
typedef short OutFunc(char c, void *op);

typedef short UnFunc(short c, void *ip);

/****** FileIo constants ************************************************/

#define OPEN_MAX		32
#define FOPEN_MAX		32
#define FILENAME_MAX	128
#define PATH_MAX		132
#define BUFSIZ			1024
#define EOF				(-1)		/* end of file */
#undef EOS
#define	EOS				'\0'		/* end-of-string indicator */

#define O_RDONLY	0x00
#define O_WRONLY	0x01
#define O_RDWR		0x02
#define O_APPEND	0x08
#define O_CREAT		0x20
#define O_TRUNC		0x40
#define O_EXCL		0x80

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

#define TMP_MAX		65535
#define L_tmpnam	13

/* Mode flags */
#define _IOFBF      0		/* full buffering */
#define _IOLBF      1		/* line buffering */
#define _IONBF      2		/* no buffering */

extern	FILE	_iob[];

/*	standard streams	*/
#define stdin       (&_StdInF)
#define stdout      (&_StdOutF)
#define stderr      (&_StdErrF)
#define stdprn      (&_StdPrnF)
#define stdaux      (&_StdAuxF)

/*	External data	*/

extern FILE         _StdInF;
extern FILE         _StdOutF;
extern FILE         _StdErrF;
extern FILE         _StdPrnF;
extern FILE         _StdAuxF;

/*	StreamIO routines	*/

FILE *	fopen		( const char *filename, const char *mo );
FILE *	freopen		( const char *filename, const char *mo, FILE *stream );
FILE *	tmpfile		( void );
void	clearerr	( FILE *stream );
short	fclose		( FILE *stream );
short	feof		( FILE *stream );
short	ferror		( FILE *stream );
short	fflush		( FILE *stream );
short	fgetc		( FILE *stream );
short	fgetpos		( FILE *stream, fpos_t *pos );
short	fprintf		( FILE *stream, const char *format, ... );
short	d_fprintf		( FILE *stream, const char *format, ... );
short	fscanf		( FILE *stream, const char *format, ... );
short	fseek		( FILE *stream, long offset, short mo );
void	rewind		( FILE *stream);
short	fsetpos		( FILE *stream, const fpos_t *pos );
long	ftell		( FILE *stream );
void	setbuf		( FILE *stream, void *buf );
short	setvbuf		( FILE *stream, void *, short , size_t  );
short	vfprintf	( FILE *stream, const char *format, va_list param );
short	vfscanf		( FILE *stream, const char *format, va_list param );
short	fileno		( FILE *stream );

size_t	fread		( 				void *buf, size_t elem_Siz, size_t count,
					  FILE *stream );
char *	fgets		( 				char *str, short n,
					  FILE *stream );
size_t	fwrite		( 				const void *buf, size_t elem_Siz, size_t count,
					  FILE *stream );
short	fputc		( 				short ch,
					  FILE *stream );
short	fputs		( 				const char *str,
					  FILE *stream );

/*	other IO routines	*/

char *	gets		( char *str );
void	perror		( char *s );
void	perrorf		(char *fmt, ...);
short	d_printf	( const char *format, ... );	/* HR used when debugging */
short	printf		( const char *format, ... );
short	puts		( const char *str );
short	scanf		( const char *format, ... );
short	sprintf		( char *string, const char *format, ... );
short	sscanf		( const char *string, const char *format, ... );
char *	tmpnam		( char *s );
short	vprintf		( const char *format, va_list param );
short	vsprintf	( char *string, const char *format, va_list param );
short	vscanf		( const char *format, va_list param );
short	vsscanf		( char *string, const char *format, va_list param );

/*	FileIo macros	*/

#define getc( c )     fgetc( c )
#define getchar()     fgetc( stdin )
#define ungetchar( c) fungetc(c, stdin)
#define putc( c, s )  fputc( c, s )
#define putchar( c )  fputc( c, stdout )
#define	exists(f )    access( f, 0x00 )

/*	GEMDOS Handle level FileIO routines	*/

short	open		( const char *filename, short access, ... );
short	close		( short handle );
short	creat		( const char *filename, ...);
size_t	read		( short handle, void *buf, size_t nbyte );
size_t	write		( short handle, const void *buf, size_t nbyte );
size_t	lseek		( short handle, size_t offset, short mo );
short	remove		( const char *filename );
short	unlink		( const char *filename );
short	rename		( const char *oldname, const char *newname );

/* In dlibs, not in PC */
FILE *	fopenp		( const char *filename, const char *mode );
FILE *	fdopen		( short h, const char *mode );
char *	fullpath	( char *full, const char *part );
char *	findfile	( const char *afn, const char *ext );
char *	pfindfile	( const char *path, const char *afn, const char *ext );
short	fungetc		( short c, FILE *fp );
short	ungetc		( short c, FILE *fp );
short	cprintf		( const char *fmt, ... );
void	cputs		( char *data );
short	getw		( FILE *fp );
short	putw		( short n, FILE *fp );
long	getl		( FILE *fp);
long	putl		( long n, FILE *fp );
size_t	tell		( short h );
short	rmdir		( const char *pathname );
short	mkdir		( const char *pathname );
short	dup			( short handle);
short	dup2		( short handle1, short handle2 );
short	_tttty		( FILE *fp );
char *_splitpath
(
	const char *src,
	char *drive,
	char *path,
	char *file,
	char *ext
);

short	printf_dmode( short );

#ifndef ERROR
#define	ERROR		(-1)		/* general error condition */
#endif

#endif
