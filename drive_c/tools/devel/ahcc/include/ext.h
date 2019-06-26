/* Copyright (c) 2006 by H. Robbers.
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


#if !defined( __EXT )
#define __EXT

#include <time.h>

/* code belonging to these standard headers moved there, ++eero */
#include <sys/stat.h>
#include <unistd.h>

extern int __text, __data, __bss;
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

struct ffblk
{
    char ff_reserved[21];               /* Reserved by TOS */
    char ff_attrib;                     /* Attribute found */
    int  ff_ftime;                      /* File time */
    int  ff_fdate;                      /* File date */
    long ff_fsize;                      /* File size */
    char ff_name[13];                   /* File name found */
};

struct date
{
    int    da_year;                     /* Current year */
    char   da_day;                      /* Day of the month */
    char   da_mon;                      /* Month ( 1 = Jan ) */
};

struct time
{
    unsigned char   ti_min;             /* Minutes */
    unsigned char   ti_hour;            /* Hours */
    unsigned char   ti_hund;            /* Hundredths of seconds */
    unsigned char   ti_sec;             /* Seconds */
};

struct ftime
{
    unsigned ft_hour:   5;
    unsigned ft_min:    6;
    unsigned ft_tsec:   5;
    unsigned ft_year:   7;
    unsigned ft_month:  4;
    unsigned ft_day:    5;
};

struct dfree
{
        unsigned df_avail;
        unsigned df_total;
        unsigned df_bsec;
        unsigned df_sclus;
};


int         getcurdir( int drive, char *path );
int         getdisk( void );
void        getdfree( unsigned char drive, struct dfree *dtable );
int         setdisk( int drive );

int         findfirst( const char *filename, struct ffblk *ffblk, int attrib );
int         findnext( struct ffblk *ffblk );

void        getdate( struct date *dateRec );
void        gettime( struct time *timeRec );
void        setdate( struct date *dateRec );
void        settime( struct time *timeRec );
int         getftime( int handle, struct ftime *ftimep );
int         setftime( int handle, struct ftime *ftimep );

struct tm   *ftimtotm( struct ftime *f );

void        delay( unsigned milliseconds );

int         kbhit( void );
int         getch( void );
int         getche( void );
int         putch( int c);

long        filelength( int handle );

size_t      coreleft( void );

#include <unistd.h>

#endif


/***********************************************************************/
