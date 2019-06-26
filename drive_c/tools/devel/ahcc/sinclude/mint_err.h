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

/* Nota Bene !!!
   These are the (negative) BIOS/XBIOS/GEMDOS replies,
   mot the Unix errno codes.
*/
	deferrno(ENOERR,	0, "no error"),

	deferrno(EERROR,	1, " Generic error"),
	deferrno(EBUSY,		2, " Resource busy"),
	deferrno(EUKCMD,	3, " Unknown command"),
	deferrno(ECRC,		4, " CRC error"),
	deferrno(EBADR,		5, " Bad request"),

	deferrno(ESPIPE,	6, " Illegal seek"),
	deferrno(EMEDIUMTYPE,7, " Wrong medium type"),
	deferrno(ESECTOR,	8, " Sector not found"),
	deferrno(EPAPER,	9, " Paper low"),
	deferrno(EWRITE,	10, " Write fault"),

	deferrno(EREAD,		11, " Read fault"),
	deferrno(EGENERIC,	12, " General mishap"),
	deferrno(EROFS,		13, " Write protect"),
	deferrno(ECHMEDIA,	14, " Media change"),
	deferrno(ENODEV,	15, " No such device"),

	deferrno(EBADSEC,	16, " Bad sectors found"),
	deferrno(ENOMEDIUM,	17, " No medium found"),
	deferrno(EINSERT,	18, " Insert media"),
	deferrno(EDRVNRSP,	19, " Drive not responding"),
	deferrno(ESRCH,		20, " No such process"),

	deferrno(ECHILD,	21, " No child processes"),
	deferrno(EDEADLK,	22, " Resource deadlock would occur"),
	deferrno(ENOTBLK,	23, " Block device required"),
	deferrno(EISDIR,	24, " Is a directory"),
	deferrno(EINVAL,	25, " Invalid argument"),

	deferrno(EFTYPE,	26, " Inappropriate file type or format"),
	deferrno(EILSEQ,	27, " Illegal byte sequence"),

	deferrno(ENOSYS,	32, " Function not implemented"),
	deferrno(ENOENT,	33, " No such file or directory"),
	deferrno(ENOTDIR,	34, " Not a directory"),
	deferrno(EMFILE,	35, " Too many open files"),
	deferrno(ENMFILE, 	35, " no more matching file"),

	deferrno(EACCES,	36, " Permission denied"),
	deferrno(EBADF,		37, " Bad file descriptor"),
	deferrno(EPERM,		38, " Operation not permitted"),
	deferrno(ENOMEM,	39, " Cannot allocate memory"),
	deferrno(EFAULT,	40, " Bad address"),

	deferrno(ENXIO,		46, " No such device or address"),
	deferrno(ERR_47,	47, " error 47"),
	deferrno(EXDEV,		48, " Cross-device link"),
	deferrno(ENMFILES,	49, " No more matching file names"),
	deferrno(ENFILE,	50, " File table overflow"),

	deferrno(ELOCKED,	58, " Locking conflict"),
	deferrno(ENSLOCK,	59, " No such lock"),

	deferrno(EBADARG,	64, " Bad argument"),
	deferrno(EINTERNAL,	65, " Internal error"),

	deferrno(ENOEXEC,	66, " Invalid executable file format"),
	deferrno(ESBLOCK,	67, " Memory block growth failure"),
	deferrno(EBREAK,	68, " Aborted by user"),
	deferrno(EXCPT,		69, " Terminated with bombs"),
	deferrno(ETXTBSY,	70, " Text file busy"),

	deferrno(EFBIG,		71, " File too big"),

	deferrno(ELOOP,		80, " Too many symbolic links"),
	deferrno(EPIPE,		81, " Broken pipe"),
	deferrno(EMLINK,	82, " Too many links"),
	deferrno(ENOTEMPTY,	83, " Directory not empty"),
	deferrno(ERR_84,	84, "error 84"),

	deferrno(EEXIST,	85, " File exists"),
	deferrno(ENAMETOOLONG,86, " Name too long"),
	deferrno(ENOTTY,	87, " Not a tty"),
	deferrno(ERANGE,	88, " Range error"),
	deferrno(EDOM,		89, " Domain error"),

	deferrno(EIO,		90, " I/O error"),
	deferrno(ENOSPC,	91, " No space left on device"),

/* Error number 92-99 reserved for TraPatch.*/

	deferrno(EPROCLIM,	100, " Too many processes for user"),
	deferrno(EUSERS,	101, " Too many users"),
	deferrno(EDQUOT,	102, " Quota exceeded"),
	deferrno(ESTALE,	103, " Stale NFS file handle"),
	deferrno(EREMOTE,	104, " Object is remote"),

	deferrno(EBADRPC,	105, " RPC struct is bad"),
	deferrno(ERPCMISMATCH,106, " RPC version wrong"),
	deferrno(EPROGUNAVAIL,107, " RPC program not available"),
	deferrno(EPROGMISMATCH,108, " RPC program version wrong"),
	deferrno(EPROCUNAVAIL,109, " RPC bad procedure for program"),

	deferrno(ENOLCK,	110, " No locks available"),
	deferrno(EAUTH,		111, " Authentication error"),
	deferrno(ENEEDAUTH,	112, " Need authenticator"),
	deferrno(EBACKGROUND,113, " Inappropriate operation for background process"),
	deferrno(EBADMSG,	114, " Not a data message"),

	deferrno(EIDRM,		115, " Identifier removed"),
	deferrno(EMULTIHOP,	116, " Multihop attempted"),
	deferrno(ENODATA,	117, " No data available"),
	deferrno(ENOLINK,	118, " Link has been severed"),
	deferrno(ENOMSG,	119, " No message of desired type"),

	deferrno(ENOSR,		120, " Out of streams resources"),
	deferrno(ENOSTR,	121, " Device not a stream"),
	deferrno(EOVERFLOW,	122, " Value too large for defined data type"),
	deferrno(EPROTO,	123, " Protocol error"),
	deferrno(ETIME,		124, " Timer expired"),

	deferrno(E2BIG,		125, " Argument list too long"),
	deferrno(ERESTART,	126, " Interrupted system call should be restarted"),
	deferrno(ECHRNG,	127, " Channel number out of range"),
	deferrno(EINTR,		128, " Interrupted function call"),

/* Falcon XBIOS errors.  */

	deferrno(ESNDLOCKED,129, " Sound system is already locked"),

	deferrno(ESNDNOTLOCK,130, " Sound system is not locked"),
	deferrno(EL2NSYNC,	131, " Level 2 not synchronized"),
	deferrno(EL3HLT,	132, " Level 3 halted"),
	deferrno(EL3RST,	133, " Level 3 reset"),
	deferrno(ELNRNG,	134, " Link number out of range"),

	deferrno(EUNATCH,	135, " Protocol driver not attached"),
	deferrno(ENOCSI,	136, " No CSI structure available"),
	deferrno(EL2HLT,	137, " Level 2 halted"),
	deferrno(EBADE,		138, " Invalid exchange"),
	deferrno(EXFULL,	139, " Exchange full"),

	deferrno(ENOANO,	140, " No anode"),
	deferrno(EBADRQC,	141, " Invalid request code"),
	deferrno(EBADSLT,	142, " Invalid slot"),
	deferrno(EBFONT,	143, " Bad font file format"),
	deferrno(ENONET,	144, " Machine is not on the network"),

	deferrno(ENOPKG,	145, " Package is not installed"),
	deferrno(EADV,		146, " Advertise error"),
	deferrno(ESRMNT,	147, " Srmount error"),
	deferrno(ECOMM,		148, " Communication error on send"),
	deferrno(EDOTDOT,	149, " RFS specific error"),

	deferrno(ELIBACC,	150, " Cannot access a needed shared library"),
	deferrno(ELIBBAD,	151, " Accessing a corrupted shared library"),
	deferrno(ELIBSCN,	152, " .lib section in a.out corrupted"),
	deferrno(ELIBMAX,	153, " Attempting to link too many shared libraries"),
	deferrno(ELIBEXEC,	154, " Cannot exec a shared library directly"),

	deferrno(ESTRPIPE,	155, " Streams pipe error"),
	deferrno(EUCLEAN,	156, " Structure needs cleaning"),
	deferrno(ENOTNAM,	157, " Not a XENIX named type file"),
	deferrno(ENAVAIL,	158, " NO XENIX semaphores available"),
	deferrno(EREMOTEIO,	159, " Remote I/O error"),

	deferrno(EMOUNT,	200, " Mount error"),
	deferrno(ENOTSOCK,	300, " Socket operation on non-socket."),
	deferrno(_NE_BASE,	300, ""),
	deferrno(EDESTADDRREQ,301, " Destination address required"),
	deferrno(EMSGSIZE,	302, " Message too long"),
	deferrno(EPROTOTYPE,303, " Protocol wrong type for socket"),
	deferrno(ENOPROTOOPT,304, " Protocol not available"),

	deferrno(EPROTONOSUPPORT,305, " Protocol not supported"),
	deferrno(ESOCKTNOSUPPORT,306, " Socket type not supported"),
	deferrno(EOPNOTSUPP,	307, " Operation not supported"),
	deferrno(EPFNOSUPPORT,	308, " Protocol family not supported"),
	deferrno(EAFNOSUPPORT,	309, " Address family not supported by protocol"),

	deferrno(EADDRINUSE,	310, " Address already in use"),
	deferrno(EADDRNOTAVAIL,	311, " Cannot assign requested address"),
	deferrno(ENETDOWN,		312, " Network is down"),
	deferrno(ENETUNREACH,	313, " Network is unreachable"),
	deferrno(ENETRESET,		314, " Network dropped conn. because of reset"),

	deferrno(ECONNABORTED,	315, " Software caused connection abort"),
	deferrno(ECONNRESET,	316, " Connection reset by peer"),
	deferrno(EISCONN,		317, " Socket is already connected"),
	deferrno(ENOTCONN,		318, " Socket is not connected"),
	deferrno(ESHUTDOWN,		319, " Cannot send after shutdown"),

	deferrno(ETIMEDOUT,		320, " Connection timed out"),
	deferrno(ECONNREFUSED,	321, " Connection refused"),
	deferrno(EHOSTDOWN,		322, " Host is down"),
	deferrno(EHOSTUNREACH,	323, " No route to host"),
	deferrno(EALREADY,		324, " Operation already in progress"),

	deferrno(EINPROGRESS,	325, " Operation now in progress"),
	deferrno(EAGAIN,		326, " Operation would block"),
	deferrno(EWOULDBLOCK,	326, ""),
	deferrno(ENOBUFS,		327, " No buffer space available"),
	deferrno(ETOOMANYREFS,	328, " Too many references"),

#undef DEFENUM
#undef DEFLIST
#undef deferrno
