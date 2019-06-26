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

/* time.h */

#if !defined( __TIME )
#define __TIME

#ifndef PRELUDE_H
#include <prelude.h>
#endif

#define CLK_TCK 200
#define CLOCKS_PER_SEC CLK_TCK

#include <stddef.h>

typedef long time_t;
typedef long clock_t;


extern long timezone;
extern short daylight;

#ifndef HAVE_DOSTIME
typedef struct
{
	unsigned short
		time,
		date;
} DOSTIME;
#define HAVE_DOSTIME 1
#endif

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
	ubits ft_hour:   5;
	ubits ft_min:    6;
	ubits ft_tsec:   5;
	ubits ft_year:   7;
	ubits ft_month:  4;
	ubits ft_day:    5;
};
#define HAVE_STRUCT_FT 1
#endif

typedef union
{
	time_t tt;
	DOSTIME dt;
	struct
	{
		ubits hour:   5;
		ubits min:    6;
		ubits tsec:   5;
		ubits year:   7;
		ubits month:  4;
		ubits day:    5;
	} ft;
} FTIME;

struct tm
{
    short tm_sec;   /* seconds after the minute -- [0,  59] */
    short tm_min;   /* minutes after the hour   -- [0,  59] */
    short tm_hour;  /* hours since midnight     -- [0,  23] */
    short tm_mday;  /* day of the month         -- [1,  31] */
    short tm_mon;   /* months since January     -- [0,  11] */
    short tm_year;  /* years since 1900         -- [      ] */
    short tm_wday;  /* day since Sunday         -- [0,   6] */
    short tm_yday;  /* day since January 1      -- [0, 365] */
    short tm_isdst; /* daylight saving time flag            */
};

typedef struct tm _TM;

#define asciitime asctime
char *		asctime	( const struct tm *tblock );
char *		ctime	( const time_t *timer );

struct tm *	gmtime	( const time_t *clock );
struct tm *	localtime( const time_t *clock );

time_t		time	( time_t *timer );
time_t		mktime	( struct tm *timeptr );

clock_t		clock	( void );

size_t		strftime( char *s, size_t max_size, const char *format,
                       const struct tm *timeptr );

#ifndef __NO_FLOAT__
double		difftime( time_t time2, time_t time1 );
#endif

time_t		ftimtosec(FTIME *ft);

void		fttotm	(_TM *t, FTIME *ft);

time_t		date_and_time_to_seconds(_TM *t, short startyear);
_TM *		seconds_to_date_and_time(time_t timer, _TM *t, short startyear);

void		stime	(time_t *rawtime);
short		utime	(char *pathname, time_t *rawtime);

clock_t		start_timer(clock_t *t);
clock_t		time_since(clock_t *t);

#endif
