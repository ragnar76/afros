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

#ifndef _SIGNAL_H
#define _SIGNAL_H

#define	__NSIG		32		/* number of signals recognized */

enum
{
	SIGNULL,			/* not really a signal */
	SIGHUP,				/* hangup signal */
	SIGINT,				/* sent by ^C */
	SIGQUIT,			/* quit signal */
	SIGILL,				/* illegal instruction */
	SIGTRAP,			/* trace trap */
	SIGABRT,			/* abort signal */
	SIGIOT = SIGABRT,
	SIGPRIV,			/* privilege violation */
	SIGEMT = SIGPRIV,
	SIGFPE,				/* divide by zero */
	SIGKILL,			/* cannot be ignored */
	SIGBUS,				/* bus error */
	SIGSEGV,			/* illegal memory reference */
	SIGSYS,				/* bad argument to a system call */
	SIGPIPE,			/* broken pipe */
	SIGALRM,			/* alarm clock */
	SIGTERM,			/* software termination signal */

	SIGURG,				/* urgent condition on I/O channel */
	SIGSTOP,			/* stop signal not from terminal */
	SIGTSTP,			/* stop signal from terminal */
	SIGCONT,			/* continue stopped process */
	SIGCHLD,			/* child stopped or exited */
	SIGTTIN,			/* read by background process */
	SIGTTOU,			/* write by background process */
	SIGIO,				/* I/O possible on a descriptor */
	SIGXCPU,			/* CPU time exhausted */
	SIGXFSZ,			/* file size limited exceeded */
	SIGVTALRM,			/* virtual timer alarm */
	SIGPROF,			/* profiling timer expired */
	SIGWINCH,			/* window size changed */
	SIGUSR1,			/* user signal 1 */
	SIGUSR2,			/* user signal 2 */
	SIGPWR,				/* power failure (restart) */
	NSIG
};

#ifndef BADSIG
#define BADSIG		SIG_ERR
#endif

typedef void cdecl (*__Sigfunc) (short signum);
typedef short sig_atomic_t;

#define       SIG_DFL	((__Sigfunc)0L)
#define       SIG_IGN	((__Sigfunc)1L)
#define       SIG_ERR	((__Sigfunc)-1L)

#define SignalBad	SIG_ERR
#define SignalDefault	SIG_DFL
#define SignalIgnore	SIG_IGN

__Sigfunc	signal	(short sig, __Sigfunc func);
__Sigfunc	__signal	(short sig, __Sigfunc func);
short 	raise	(short sig);
short 	kill	(short, short);
short 	__kill	(short, short);
short 	killpg	(short, short);
short 	__killpg	(short, short);

#define _SIGSET_INDEX(__sig)	(__sig / 32)
#define _SIGSET_BITPOS(__sig)	(__sig % 32)
#define _SIGSET_MAX_INDEX	(__NSIG / 32)

typedef struct
{
  long __sigset_data[_SIGSET_MAX_INDEX + 1];
} sigset_t;

#ifdef __MINT__
struct sigaction
{
	__Sigfunc	sa_handler;	/* pointer to signal handler */
	sigset_t	sa_mask;	/* additional signals masked during delivery */
	short 		sa_flags;	/* signal specific flags */
/* signal flags */
#define SA_NOCLDSTOP	1	/* don't send SIGCHLD when they stop */
};

#ifdef __USE_BSD
#ifdef __MSHORT__
long	sigsetmask		(long mask);
long	__sigsetmask	(long mask);
long	sigblock		(long mask);
long	__sigblock		(long mask);
#else
short 	sigsetmask		(long mask);
short 	__sigsetmask	(long mask);
short 	sigblock		(long mask);
short 	__sigblock		(long mask);
#endif
/* a mask for signals */
#define sigmask(__sig) (1L << (__sig))
#endif /* BSD */

short	sigaction		(short, const struct sigaction *, struct sigaction *);
short	__sigaction		(short, const struct sigaction *, struct sigaction *);
short	sigaddset		(sigset_t *set, short signo);
short	sigdelset		(sigset_t *set, short signo);
short	sigemptyset		(sigset_t *set);
short	sigfillset		(sigset_t *set);
short	sigismember		(sigset_t *set, short signo);
void	sigpause		(long mask);
void	__sigpause		(long mask);
short	sigpending		(sigset_t *set);
short	__sigpending	(sigset_t *set);
short	sigprocmask		(short how, const sigset_t *set, sigset_t *oset);
void	sigreturn		(void);
void	__sigreturn		(void);
short	sigsuspend		(const sigset_t *sigmask);

/* values for "how" parameter to sigprocmask() */
#define SIG_BLOCK	0
#define SIG_UNBLOCK	1
#define SIG_SETMASK	2

#endif /* __MINT__ */

#endif /* _SIGNAL_H */
