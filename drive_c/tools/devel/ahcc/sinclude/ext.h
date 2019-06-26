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

#if !defined( __EXT_H__ )
#define __EXT_H__

#include <time.h>

extern short __text, __data, __bss;
#define _text &__text
#define _data &__data
#define _bss  &__bss

#define FA_UPDATE       0x00
#define FA_RDONLY       0x01
#define FA_HIDDEN       0x02
#define FA_SYSTEM       0x04
#define FA_LABEL        0x08
#define FA_DIREC        0x10
#define FA_ARCH         0x20

#define MAXPATH   119
#define MAXDRIVE  3
#define MAXDIR    102
#define MAXFILE   9
#define MAXEXT    5

/* bits in struct stat mode */
#define S_IFREG   0100000
#define S_IFCHR   0020000
#define S_IFDIR   0040000
#define S_IEXEC   0000100
#define S_IREAD   0000400
#define S_IWRITE  0000200

#if !defined( __STDDEF )
#include <stddef.h>
#endif


struct ffblk
{
    char ff_reserved[21];               /* Reserved by TOS */
    char ff_attrib;                     /* Attribute found */
    short  ff_ftime;                      /* File time */
    short  ff_fdate;                      /* File date */
    long ff_fsize;                      /* File size */
    char ff_name[132];                  /* File name found */
};

#ifndef HAVE_STRUCT_FT
struct date
{
    short  da_year;                     /* Current year */
    char   da_day,                      /* Day of the month */
    	   da_mon;                      /* Month ( 1 = Jan ) */
};

struct time
{
    unsigned char
		min,             /* Minutes */
		hour,            /* Hours */
		hund,            /* Hundredths of seconds */
		sec;             /* Seconds */
};

typedef
struct ftime
{
    unsigned ft_hour:   5;
    unsigned ft_min:    6;
    unsigned ft_tsec:   5;
    unsigned ft_year:   7;
    unsigned ft_month:  4;
    unsigned ft_day:    5;
};
#define HAVE_STRUCT_FT 1
#endif

struct stat
{
    short
	    st_dev,
	    st_ino,
	    st_mode,
	    st_nlink,
	    st_uid,
	    st_gid,
	    st_rdev;
    size_t
    	st_size;
    long
		st_atime,
		st_mtime,
		st_ctime;
};

struct dfree
{
	unsigned short
		df_avail,
		df_total,
		df_bsec,
		df_sclus;
};


short       getcurdir( short drive, char *path );
char        *getcwd( char *buffer, short bufflen );
short       getdisk( void );
void        getdfree( short drive, struct dfree *dtable );
short       setdisk( short drive );

short       findfirst( const char *filename, struct ffblk *ffblk, short attrib );
short       findnext( struct ffblk *ffblk );

void        getdate( struct date *dateRec );
void        gettime( struct time *timeRec );
void        setdate( struct date *dateRec );
void        settime( struct time *timeRec );
short       getftime( short handle, struct ftime *ftimep );
short       setftime( short handle, struct ftime *ftimep );

struct tm   *ftimtotm( struct ftime *f );		/* code in time.c */

void        delay( unsigned long milliseconds );
void        sleep( unsigned short seconds );

short       kbhit( void );
short       getch( void );
short       getche( void );
short       putch( short c);
short       chdir( const char *filename );

short       fstat( short handle, struct stat *statbuf );
short       stat( const char *path, struct stat *buff );
short		access( const char *name, short am );
long		fsize( const char *name );

short       isatty( short handle );
long        filelength( short handle );

size_t      coreleft( void );

short		chmod(const char *filename, short pmode);
short		getpid(void);

#endif
