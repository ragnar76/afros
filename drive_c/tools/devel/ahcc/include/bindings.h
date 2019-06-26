
/* bindings.h to be used by AHCC compiling MiNT */

#define TRAP(a)   cdecl __syscall__(a)
#define GEM_DOS(b) cdecl __syscall__( 1,b)
#define BIOS(b)   cdecl __syscall__(13,b)
#define XBIOS(b)  cdecl __syscall__(14,b)

long    TRAP( 1)	gemdos( void, ... );
long    TRAP(13)	bios  ( void, ... );
long    TRAP(14)	xbios ( void, ... );

/****** Tos *************************************************************/

void    GEM_DOS(0)	Pterm0( void );
long    GEM_DOS(1)	Cconin( void );
void    GEM_DOS(2)	Cconout( int   c );
int     GEM_DOS(3)	Cauxin( void );
void    GEM_DOS(4)	Cauxout( int   c );
int     GEM_DOS(5)	Cprnout( int   c );
long    GEM_DOS(6)	Crawio( int   w );
long    GEM_DOS(7)	Crawcin( void );
long    GEM_DOS(8)	Cnecin( void );
int     GEM_DOS(9)	Cconws( const char *buf );
/* void    GEM_DOS(10)	Cconrs( LINE *buf ); not suitable for MiNT */
int     GEM_DOS(11)	Cconis( void );
long    GEM_DOS(14)	Dsetdrv( int   drv );
int     GEM_DOS(16)	Cconos( void );
int     GEM_DOS(17)	Cprnos( void );
int     GEM_DOS(18)	Cauxis( void );
int     GEM_DOS(19)	Cauxos( void );
int     GEM_DOS(25)	Dgetdrv( void );
void    GEM_DOS(26)	Fsetdta( DTABUF *buf );
long    GEM_DOS(32)	Super( void *stack );
unsigned int   GEM_DOS(42)	Tgetdate( void );
unsigned int   GEM_DOS(43)	Tsetdate( unsigned int   date );
unsigned int   GEM_DOS(44)	Tgettime( void );
unsigned int   GEM_DOS(45)	Tsettime( unsigned int   time );
DTABUF  *  GEM_DOS(47)	Fgetdta( void );
int     GEM_DOS(48)	Sversion( void );
void    GEM_DOS(49)	Ptermres( long keepcnt, int   retcode );
int     GEM_DOS(54)	Dfree( long *buf, int   driveno );
int     GEM_DOS(57)	Dcreate( const char *path );
int     GEM_DOS(58)	Ddelete( const char *path );
int     GEM_DOS(59)	Dsetpath( const char *path );
long    GEM_DOS(60)	Fcreate( const char *filename, int   attr );
long    GEM_DOS(61)	Fopen( const char *filename, int   mo );
int     GEM_DOS(62)	Fclose( int   handle );
long    GEM_DOS(63)	Fread( int   handle, long count, void *buf );
long    GEM_DOS(64)	Fwrite( int   handle, long count, void *buf );
int     GEM_DOS(65)	Fdelete( const char *filename );
long    GEM_DOS(66)	Fseek( long offset, int   handle, int   seekmode );
int     GEM_DOS(67)	Fattrib( const char *filename, int   wflag, int   attrib );
long    GEM_DOS(69)	Fdup( int   handle );
int     GEM_DOS(70)	Fforce( int   stch, int   nonstdh );
int     GEM_DOS(71)	Dgetpath( char *path, int   driveno );
void *  GEM_DOS(72)	Malloc( long number );
int     GEM_DOS(73)	Mfree( void *block );
int     GEM_DOS(74)	Mshrink( int   zero, void *block, long newsiz );
long    GEM_DOS(75)	Pexec( int   mo, char *ptr1, void *ptr2, void *ptr3 );
void    GEM_DOS(76)	Pterm( int   retcode );
int     GEM_DOS(78)	Fsfirst( const char *filename, int  attr );
int     GEM_DOS(79)	Fsnext( void );
int     GEM_DOS(86)	Frename( int  zero, const char *oldname, const char *newname );
int     GEM_DOS(87)	Fdatime( void *timeptr, int  handle, int  wflag );
int     GEM_DOS(0x119)	Pdomain( int  newdom );
void *  GEM_DOS(0x112)	Psignal( int  sig, void *handler );

/****** TOS 030 Gemdos Extension ****************************************/

void *  GEM_DOS(68)	Mxalloc( long number, int  mo );
long    GEM_DOS(20)	Maddalt( void *start, long size );

/****** Network Gemdos Extension ****************************************/

long    GEM_DOS(92)	Flock( int  handle, int  mo, long start, long length );

/****** Bios ************************************************************/

/* void    BIOS( 0)	Getmpb( void *ptr ); */
int     BIOS( 1)	Bconstat( int  dev );
long    BIOS( 2)	Bconin( int  dev );
long    BIOS( 3)	Bconout( int  dev, int  c );
long    BIOS( 4)	Rwabs( int  rwflag, void *buf, int  cnt, int  recnr, int  dev );
void    (* BIOS(5)	Setexc( int  number, void (*exchdlr)() )) ();
long    BIOS( 6)	Tickcal( void );
void *	BIOS( 7)	Getbpb( int  dev );
long    BIOS( 8)	Bcostat( int  dev );
long    BIOS( 9)	Mediach( int  dev );
long    BIOS(10)	Drvmap( void );
long    BIOS(11)	Kbshift( int  mo );
long    BIOS(12)	Lrwabs( int  rwflag, void *buf, int  cnt, int  recnr, int  dev );

/****** XBios ***********************************************************/

/*void    XBIOS(0)	Initmouse( int  type, MOUSE *par, void (*mousevec)() ); */
void *	XBIOS(1)	Ssbrk( int  count );
void *  XBIOS(2)	Physbase( void );
void *	XBIOS(3)	Logbase( void );
int     XBIOS(4)	Getrez( void );
void    XBIOS(5)	Setscreen( void *laddr, void *paddr, int  rez );
void    XBIOS(6)	Setpalette( void *pallptr );
int     XBIOS(7)	Setcolor( int  colornum, int  color );
int     XBIOS(8)	Floprd( void *buf, void *filler, int  devno, int  sectno,
               int  trackno, int  sideno, int  count );
int     XBIOS(9)	Flopwr( void *buf, void *filler, int  devno, int  sectno,
               int  trackno, int  sideno, int  count );
int     XBIOS(10)	Flopfmt( void *buf, void *filler, int  devno, int  spt, int  trackno,
                int  sideno, int  interlv, long magic, int  virgin );
void    XBIOS(12)	Midiws( int  cnt, void *ptr );
void    XBIOS(13)	Mfpint( int  erno, void (*vector)() );
void *	XBIOS(14)	Iorec( int  dev );
long    XBIOS(15)	Rsconf( int  baud, int  ctr, int  ucr, int  rsr, int  tsr, int  scr );
struct keytab *XBIOS(16)	Keytbl( void *unshift, void *shift, void *capslock );
long    XBIOS(17)	Random( void );
void    XBIOS(18)	Protobt( void *buf, long serialno, int  disktype, int  execflag );
int     XBIOS(19)	Flopver( void *buf, void *filler, int  devno, int  sectno,
                int  trackno, int  sideno, int  count );
void    XBIOS(20)	Scrdmp( void );
int     XBIOS(21)	Cursconf( int  func, int  rate );
void    XBIOS(22)	Settime( unsigned long time );
unsigned
long	XBIOS(23)	Gettime( void );
void    XBIOS(24)	Bioskeys( void );
void    XBIOS(25)	Ikbdws( int  count, void *ptr );
void    XBIOS(26)	Jdisint( int  number );
void    XBIOS(27)	Jenabint( int  number );
char    XBIOS(28)	Giaccess( char data, int  regno );
void    XBIOS(29)	Offgibit( int  bitno );
void    XBIOS(30)	Ongibit( int  bitno );
void    XBIOS(31)	Xbtimer( int  timer, int  control, int  data, void (*vector)() );
void *  XBIOS(32)	Dosound( void *buf );
int     XBIOS(33)	Setprt( int  config );
void *	XBIOS(34)Kbdvbase( void );
int     XBIOS(35)	Kbrate( int  initial, int  repeat );
/* void    XBIOS(36)	Prtblk( PBDEF *par ); */
void    XBIOS(37)	Vsync( void );
typedef unsigned long Supfunc(void);
long    XBIOS(38)	Supexec( Supfunc * );
void    XBIOS(39)	Puntaes( void );
int     XBIOS(41)	Floprate( int  devno, int  newrate );
int     XBIOS(64)	Blitmode( int  mo );

/* TOS030 XBios */
int    XBIOS(42)	DMAread( long sector, int  count, void *buffer, int  devno );
int    XBIOS(43)	DMAwrite( long sector, int  count, void *buffer, int  devno );
long   XBIOS(44)	Bconmap( int  devno );
int    XBIOS(46)	NVMaccess( int  opcode, int  start, int  count, void *buffer );
int    XBIOS(80)	Esetshift( int  shftMode );
int    XBIOS(81)	Egetshift( void );
int    XBIOS(82)	EsetBank( int  bankNum );
int    XBIOS(83)	EsetColor( int  colorNum, int  color );
void   XBIOS(84)	EsetPalette( int  colorNum, int  count, int  *palettePtr );
void   XBIOS(85)	EgetPalette( int  colorNum, int  count, int  *palettePtr );
int    XBIOS(86)	EsetGray( int  swtch );
int    XBIOS(87)	EsetSmear( int  swtch );


int    GEM_DOS(0xff)	Syield( void );
int    GEM_DOS(0x100)	Fpipe( int  *usrh );
int    GEM_DOS(0x104)	Fcntl( int  f, long arg, int  cmd );
long   GEM_DOS(0x105)	Finstat( int  f );
long   GEM_DOS(0x106)	Foutstat( int  f );
long   GEM_DOS(0x107)	Fgetchar( int  f, int  mo );
long   GEM_DOS(0x108)	Fputchar( int  f, long c, int  mo );
long   GEM_DOS(0x109)	Pwait( void );
int    GEM_DOS(0x10a)	Pnice( int  delta );
int    GEM_DOS(0x10b)	Pgetpid( void );
int    GEM_DOS(0x10c)	Pgetppid( void );
int    GEM_DOS(0x10d)	Pgetpgrp( void );
int    GEM_DOS(0x10e)	Psetpgrp( int  pid, int  newgrp );
int    GEM_DOS(0x10f)	Pgetuid( void );
int    GEM_DOS(0x110)	Psetuid( int  id );
int    GEM_DOS(0x111)	Pkill( int  pid, int  sig );
int    GEM_DOS(0x113)	Pvfork( void );
int    GEM_DOS(0x114)	Pgetgid( void );
int    GEM_DOS(0x115)	Psetgid( int  id );
long   GEM_DOS(0x116)	Psigblock( long mask );
long   GEM_DOS(0x117)	Psigsetmask( long mask );
long   GEM_DOS(0x118)	Pusrval( long arg );
void   GEM_DOS(0x11a)	Psigreturn( void );
int    GEM_DOS(0x11b)	Pfork( void );
long   GEM_DOS(0x11c)	Pwait3( int  flag, long *rusage );
int    GEM_DOS(0x11d)	Fselect( unsigned int  timeout, long *rfds, long *wfds, long *xfds );
void   GEM_DOS(0x11e)	Prusage( long *r );
long   GEM_DOS(0x11f)	Psetlimit( int  lim, long value );
long   GEM_DOS(0x120)	Talarm( long secs );
void   GEM_DOS(0x121)	Pause( void );
long   GEM_DOS(0x122)	Sysconf( int  n );
long   GEM_DOS(0x123)	Psigpending( void );
long   GEM_DOS(0x124)	Dpathconf( char *name, int  n );
long   GEM_DOS(0x125)	Pmsg( int  mo, long mbox, void *msg );
long   GEM_DOS(0x126)	Fmidipipe( int  pid, int  in, int  out );
int    GEM_DOS(0x127)	Prenice( int  pid, int  delta );
long   GEM_DOS(0x128)	Dopendir( const char *name, int  flag );
long   GEM_DOS(0x129)	Dreaddir( int  buflen, long dir, char *buf );
long   GEM_DOS(0x12a)	Drewinddir( long dir );
long   GEM_DOS(0x12b)	Dclosedir( long dir );
long   GEM_DOS(0x12c)	Fxattr( int  flag, const char *name, XATTR *buf );
long   GEM_DOS(0x12d)	Flink( char *oldname, char *newname );
long   GEM_DOS(0x12e)	Fsymlink( char *oldname, char *newname );
long   GEM_DOS(0x12f)	Freadlink( int  size, char *buf, char *name );
long   GEM_DOS(0x130)	Dcntl( int  cmd, char *name, long arg );
long   GEM_DOS(0x131)	Fchown( char *name, int  uid, int  gid );
long   GEM_DOS(0x132)	Fchmod( char *name, int  mo );
long   GEM_DOS(0x133)	Pumask( unsigned int  mo );
long   GEM_DOS(0x134)	Psemaphore( int  mo, long id, long timeout );
long   GEM_DOS(0x135)	Dlock( int  mo, int  drive );
void   GEM_DOS(0x136)	Psigpause( unsigned long mask );
/* long   GEM_DOS(0x137)	Psigaction( int  sig, SIGACTION *act, SIGACTION *oact ); */
int    GEM_DOS(0x138)	Pgeteuid( void );
int    GEM_DOS(0x139)	Pgetegid( void );
long   GEM_DOS(0x13b)	Dgetcwd( char *path, int  drv, int  size );
long   GEM_DOS(0x13a)	Pwaitpid( int  pid, int  flag, long *rusage );
long   GEM_DOS(0x13c)	Salert(char *msg);

/* Falcon */

#define VERTFLAG          0x0100
#define STMODES           0x0080
#define OVERSCAN          0x0040
#define PAL               0x0020
#define VGA_FALCON        0x0010
#define TV                0x0000

#define COL80             0x08
#define COL40             0x00

#define BPS16             4
#define BPS8              3
#define BPS4              2
#define BPS2              1
#define BPS1              0

#define NUMCOLS           7


typedef struct
{
    int     blocktype;
    long    blocksize;
    void    *blockaddr;
} DSPBLOCK;


void    XBIOS(  5)	VsetScreen( void *log, void *phys, int mode, int modecode);
int     XBIOS( 88)	VsetMode( int modecode );
int     XBIOS( 89)	mon_type( void );
int     XBIOS( 89)	VgetMonitor( void );
void    XBIOS( 90)	VsetSync( int flag );
long    XBIOS( 91)	VgetSize( int mode );
void    XBIOS( 92)	VsetMask( int ormask, int andmask, int overlay );
void    XBIOS( 93)	VsetRGB( int index, int count, long *array );
void    XBIOS( 94)	VgetRGB( int index, int count, long *array );
int     XBIOS( 95)	VcheckMode( int modecode );
int     XBIOS( 95)	ValidMode( int modecode );

void    XBIOS( 96)	Dsp_DoBlock( char *data_in, long size_in, char *data_out,
                     long size_out );
void    XBIOS( 97)	Dsp_BlkHandShake( char *data_in, long size_in, char *data_out,
                          long size_out );
void    XBIOS( 98)	Dsp_BlkUnpacked( long *data_in, long size_in, long *data_out,
                         long size_out );
void    XBIOS( 99)	Dsp_InStream( char *data_in, long block_size, long num_blocks,
                      long *blocks_done );
void    XBIOS(100)	Dsp_OutStream( char *data_out, long block_size, long num_blocks,
                       long *blocks_done );
void    XBIOS(101)	Dsp_IOStream( char *data_in, char *data_out, long block_insize,
                      long block_outsize, long num_blocks,
                      long *blocks_done );
void    XBIOS(102)	Dsp_RemoveInterrupts( int mask );
int     XBIOS(103)	Dsp_GetWordSize( void );
int     XBIOS(104)	Dsp_Lock( void );
void    XBIOS(105)	Dsp_Unlock( void );
void    XBIOS(106)	Dsp_Available( long *xavailable, long *yavailable );
int     XBIOS(107)	Dsp_Reserve( long xreserve, long yreserve );
int     XBIOS(108)	Dsp_LoadProg( char *file, int ability, char *buffer );
void    XBIOS(109)	Dsp_ExecProg( char *codeptr, long codesize, int ability );
void    XBIOS(110)	Dsp_ExecBoot( char *codeptr, long codesize, int ability );
long    XBIOS(111)	Dsp_LodToBinary( char *file, char *codeptr );
void    XBIOS(112)	Dsp_TriggerHC( int vector );
int     XBIOS(113)	Dsp_RequestUniqueAbility( void );
int     XBIOS(114)	Dsp_GetProgAbility( void );
void    XBIOS(115)	Dsp_FlushSubroutines( void );
int     XBIOS(116)	Dsp_LoadSubroutine( char *codeptr, long codesize, int ability );
int     XBIOS(117)	Dsp_InqSubrAbility( int ability );
int     XBIOS(118)	Dsp_RunSubroutine( int handle );
int     XBIOS(119)	Dsp_Hf0( int flag );
int     XBIOS(120)	Dsp_Hf1( int flag );
int     XBIOS(121)	Dsp_Hf2( void );
int     XBIOS(122)	Dsp_Hf3( void );
void    XBIOS(123)	Dsp_BlkWords( void *data_in, long size_in, void *data_out,
                      long size_out );
void    XBIOS(124)	Dsp_BlkBytes( void *data_in, long size_in, void *data_out,
                      long size_out );
char    XBIOS(125)	Dsp_HStat( void );
void    XBIOS(126)	Dsp_SetVectors( void (*receiver)( ), long (*transmitter)( ));
void    XBIOS(127)	Dsp_MultBlocks( long numsend, long numreceive,
                        DSPBLOCK *sendblocks, DSPBLOCK *receiveblocks );

long    XBIOS(128)	locksnd( void );
long    XBIOS(129)	unlocksnd( void );
long    XBIOS(130)	soundcmd( int mode, int data );
long    XBIOS(131)	setbuffer( int reg, void *begaddr, void *endaddr );
long    XBIOS(132)	setmode( int mode );
long    XBIOS(133)	settracks( int playtracks, int rectracks );
long    XBIOS(134)	setmontracks( int montrack );
long    XBIOS(135)	setinterrupt( int src_inter, int cause );
long    XBIOS(136)	buffoper( int mode );
long    XBIOS(137)	dsptristate( int dspxmit, int dsprec );
long    XBIOS(138)	gpio( int mode, int data );
long    XBIOS(139)	devconnect( int src, int dst, int srcclk, int prescale,
                    int protocol );
long    XBIOS(140)	sndstatus( int reset );
long    XBIOS(141)	buffptr( long *ptr );

/*		XBIOS(150)	VsetVars ( ?????? );	*/

int     XBIOS(165)	WavePlay( int flags, long rate, void *sptr, long slen );
