/* signal handling */

#include <trap.h>

#ifndef __NINT_H
#define __NINT_H

#define NSIG       31       /* number of signals recognized   */

#ifndef _SIGNAL_H
#define _SIGNAL_H
#define SIGNULL     0       /* not really a signal             */
#define SIGHUP      1       /* hangup signal                   */
#define SIGINT      2       /* sent by ^C                      */
#define SIGQUIT     3       /* quit signal                     */
#define SIGILL      4       /* illegal instruction             */
#define SIGTRAP     5       /* trace trap                      */
#define SIGABRT     6       /* abort signal                    */
#define SIGPRIV     7       /* privilege violation             */
#define SIGFPE      8       /* divide by zero                  */
#define SIGKILL     9       /* cannot be ignored               */
#define SIGBUS     10       /* bus error                       */
#define SIGSEGV    11       /* illegal memory reference        */
#define SIGSYS     12       /* bad argument to a system call   */
#define SIGPIPE    13       /* broken pipe                     */
#define SIGALRM    14       /* alarm clock                     */
#define SIGTERM    15       /* software termination signal     */
#define SIGURG     16       /* urgent condition on I/O channel */
#define SIGSTOP    17       /* stop signal not from terminal   */
#define SIGTSTP    18       /* stop signal from terminal       */
#define SIGCONT    19       /* continue stopped process        */
#define SIGCHLD    20       /* child stopped or exited         */
#define SIGTTIN    21       /* read by background process      */
#define SIGTTOU    22       /* write by background process     */
#define SIGIO      23       /* I/O possible on a descriptor    */
#define SIGXCPU    24       /* CPU time exhausted              */
#define SIGXFSZ    25       /* file size limited exceeded      */
#define SIGVTALRM  26       /* virtual timer alarm             */
#define SIGPROF    27       /* profiling timer expired         */
#define SIGWINCH   28       /* window size changed             */
#define SIGUSR1    29       /* user signal 1                   */
#define SIGUSR2    30       /* user signal 2                   */

#define SIG_DFL    0        /* default signal handler          */
#define SIG_IGN    1        /* ignore the signal               */
#endif

/* file types */
#define S_IFMT  0170000     /* mask to select file type */
#define S_IFCHR 0020000     /* BIOS special file */
#define S_IFDIR 0040000     /* directory file */
#define S_IFREG 0100000     /* regular file */
#define S_IFIFO 0120000     /* FIFO */
#define S_IMEM  0140000     /* memory region or process */
#define S_IFLNK 0160000     /* symbolic link */

/* special bits: setuid, setgid, sticky bit */
#define S_ISUID 0004000
#define S_ISGID 0002000
#define S_ISVTX 0001000

/* file access modes for user, group, and other*/
#define S_IRUSR 0000400
#define S_IWUSR 0000200
#define S_IXUSR 0000100
#define S_IRGRP 0000040
#define S_IWGRP 0000020
#define S_IXGRP 0000010
#define S_IROTH 0000004
#define S_IWOTH 0000002
#define S_IXOTH 0000001
#define DEFAULT_DIRMODE (0777)
#if 0
#define DEFAULT_MODE    (0666)
#endif

typedef struct
{
        long     msg1;
        long     msg2;
        short    pid;
} __MSG;

typedef struct xattr
{
	unsigned short	mode;
	long	index;
	unsigned short	dev;
	unsigned short	rdev;		/* "real" device */
	unsigned short	nlink;
	unsigned short	uid;
	unsigned short	gid;
	long	size;
	long	blksize;
	long	nblocks;
	unsigned short	mtime, mdate;
	unsigned short	atime, adate;
	unsigned short	ctime, cdate;
	short	attr;
} XATTR;


#define SA_NOCLDSTOP    1

typedef struct
{
        void    (*sa_handler)( long sig );
        long    sa_mask;
        short   sa_flags;
} SIGACTION;


short   GEMDOS(0xff)	Syield(void);
short   GEMDOS(0x100)	Fpipe( short *usrh );
short   GEMDOS(0x104)	Fcntl( short f, long arg, short cmd );
long    GEMDOS(0x105)	Finstat( short f );
long    GEMDOS(0x106)	Foutstat( short f );
long    GEMDOS(0x107)	Fgetchar( short f, short mo );
long    GEMDOS(0x108)	Fputchar( short f, long c, short mo );
long    GEMDOS(0x109)	Pwait( void );
short   GEMDOS(0x10a)	Pnice( short delta );
short   GEMDOS(0x10b)	Pgetpid( void );
short   GEMDOS(0x10c)	Pgetppid( void );
short   GEMDOS(0x10d)	Pgetpgrp( void );
short   GEMDOS(0x10e)	Psetpgrp( short pid, short newgrp );
short   GEMDOS(0x10f)	Pgetuid( void );
short   GEMDOS(0x110)	Psetuid( short id );
short   GEMDOS(0x111)	Pkill( short pid, short sig );
short   GEMDOS(0x113)	Pvfork( void );
short   GEMDOS(0x114)	Pgetgid( void );
short   GEMDOS(0x115)	Psetgid( short id );
long    GEMDOS(0x116)	Psigblock( long mask );
long    GEMDOS(0x117)	Psigsetmask( long mask );
long    GEMDOS(0x118)	Pusrval( long arg );
void    GEMDOS(0x11a)	Psigreturn( void );
short	GEMDOS(0x11b)	Pfork( void );
long    GEMDOS(0x11c)	Pwait3( short flag, long *rusage );
short   GEMDOS(0x11d)	Fselect( unsigned short timeout, long *rfds, long *wfds, long *xfds );
void    GEMDOS(0x11e)	Prusage( long *r );
long    GEMDOS(0x11f)	Psetlimit( short lim, long value );
long    GEMDOS(0x120)	Talarm( long secs );
void    GEMDOS(0x121)	Pause( void );
long    GEMDOS(0x122)	Sysconf( short n );
long    GEMDOS(0x123)	Psigpending( void );
long    GEMDOS(0x124)	Dpathconf( const char * name, short n );
long    GEMDOS(0x125)	Pmsg( short mo, long mbox, __MSG *msg );
long    GEMDOS(0x126)	Fmidipipe( short pid, short in, short out );
short   GEMDOS(0x127)	Prenice( short pid, short delta );
long    GEMDOS(0x128)	Dopendir( const char *name, short flag );
long    GEMDOS(0x129)	Dreaddir( short buflen, long dir, char *buf );
long    GEMDOS(0x12a)	Drewinddir( long dir );
long    GEMDOS(0x12b)	Dclosedir( long dir );
long    GEMDOS(0x12c)	Fxattr( short flag, const char *name, XATTR *buf );
long    GEMDOS(0x12d)	Flink( char *oldname, char *newname );
long    GEMDOS(0x12e)	Fsymlink( char *oldname, char *newname );
long    GEMDOS(0x12f)	Freadlink( short size, char *buf, char *name );
long    GEMDOS(0x130)	Dcntl( short cmd, char *name, long arg );
long    GEMDOS(0x131)	Fchown( char *name, short uid, short gid );
long    GEMDOS(0x132)	Fchmod( char *name, short mo );
long    GEMDOS(0x133)	Pumask( unsigned short mo );
long    GEMDOS(0x134)	Psemaphore( short mo, long id, long timeout );
long    GEMDOS(0x135)	Dlock( short mo, short drive );
void    GEMDOS(0x136)	Psigpause( unsigned long mask );
long    GEMDOS(0x137)	Psigaction( short sig, SIGACTION *act, SIGACTION *oact );
short   GEMDOS(0x138)	Pgeteuid( void );
short   GEMDOS(0x139)	Pgetegid( void );
long	GEMDOS(0x13b)	Dgetcwd( char *path, short drv, short size );
long    GEMDOS(0x13a)	Pwaitpid( short pid, short flag, long *rusage );
long	GEMDOS(0x13c)	Salert(char *msg);

/* The following are not yet official...
long	GEMDOS(0x13d)	Tmalarm( long secs );
long	GEMDOS(0x13e)	Psigintr( short vec, short sig);
long	GEMDOS(0x13f)	Suptime( long *uptime, long *avenrun);
long	GEMDOS(0x142)	Dxreaddir( short len, long handle, char * buf, long xattr, long *xret );
short	GEMDOS(0x143)	Dseteuid( short id );
short	GEMDOS(0x144)	Dsetegid( short id );
short	GEMDOS(0x145)	Dsetauid( short id );
short	GEMDOS(0x146)	Dgetauid( short id );
long	GEMDOS(0x147)	Pgetgroups( short gidsetlen, _GID_T *gidset );
long	GEMDOS(0x148)	Psetgroups( short gidsetlen, _GID_T *gidset );
long	GEMDOS(0x149)	Tsetitimer( short which, long *interval, long *value, long *ointerval, long *ovalue );
short	GEMDOS(0x14e)	Psetreuid( short rid, short eid );
short	GEMDOS(0x14f)	Psetregid( short rid, short eid );
long	GEMDOS(0x150)	Sync( void );
void	GEMDOS(0x151)	Shutdown( long restart );
char *	GEMDOS(0x152)	Dreadlabel( char *path, char *label, short maxlen );
char *	GEMDOS(0x153)	Dwritelabel( char *path, char *label);
long	GEMDOS(0x154)	Ssystem(short mode, long arg1, long arg2);
#define Ssystem(mode, arg1, arg2) Ssystem(mode, (long)(arg1), (long)(arg2))
long	GEMDOS(0x155)	Tgettimeofday(long tvp, long tzp);
#define Tgettimeofday(tvp, tzp) Tgettimeofday((long)tvp, (long)tzp)
long	GEMDOS(0x156)	Tsettimeofday(long tvp, long tzp);
#define Tsettimeofday(tvp, tzp) Tsettimeofday((long)tvp, (long)tzp)
long	GEMDOS(0x158)	Pgetpriority(short which, short who);
long	GEMDOS(0x159)	Psetpriority(short which, short who, short pri);
*/

#endif
