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
#if defined DEFENUM
#define deferrno(n, s, t) n = s
#elif defined DEFLIST
#define deferrno(n, s, t) {t, #n, n}
#else
#error invalid macro definition
#endif

	deferrno(ENOERR,	0, "no error"),

	deferrno(EPERM,		1,	"file permission denied"),
	deferrno(ENOENT,	2,	"File not found"),
	deferrno(EIO,		5,	"general i/o error"),
	deferrno(EBADF,		9,	"invalid file handle"),
	deferrno(EILLSPE,	10,	"illegal file specification "),
	deferrno(EINVMEM,	11,	"invalid heap block "),
	deferrno(ENOMEM,	12,	"heap overflow"),
	deferrno(EACCES,	13,	"file access mode error"),
	deferrno(EEXIST,	17,	"file already exists"),
	deferrno(EPLFMT,	18,	"program load format error"),
	deferrno(ENODEV,	19,	"device error"),
	deferrno(ENOTDIR,	20,	"path not found"),
	deferrno(EINVAL,	22,	"invalid parameter"),
	deferrno(ENFILE,	23,	"file table overflow"),
	deferrno(EMFILE,	24,	"too many open files"),
	deferrno(ENOSPC,	28,	"disk full"),
	deferrno(ESPIPE,	29,	"seek error"),
	deferrno(EROFS,		30,	"read only device"),
	deferrno(ENOSYS,	32,	"function not implemented"),
	deferrno(EDOM,		33,	"Domain error"),
	deferrno(ERANGE,	34,	"range error"),
	deferrno(ENMFILE,	35,	"no more matching file"),


#undef DEFENUM
#undef DEFLIST
#undef deferrno
