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

/*      STAT.H
 *
 *      Useful subset of POSIX sys/stat.h functionality:
 *      http://pubs.opengroup.org/onlinepubs/007908799/xsh/sysstat.h.html
 */
#ifndef _SYS_STAT_H
#define _SYS_STAT_H

/* sys/types.h needs to be included before this as specified
 * by stat()/fstat() manual page(s).
 */

#define S_IFCHR   0020000
#define S_IFDIR   0040000
#define S_IFREG   0100000
#define S_IEXEC   0000100
#define S_IREAD   0000400
#define S_IWRITE  0000200

struct stat
{
    int    st_dev;
    int    st_ino;
    int    st_mode;
    int    st_nlink;
    int    st_uid;
    int    st_gid;
    int    st_rdev;
    size_t st_size;
    long   st_atime;
    long   st_mtime;
    long   st_ctime;
};

int         fstat( int handle, struct stat *statbuf );
int         stat( char *path, struct stat *buff );

#endif
