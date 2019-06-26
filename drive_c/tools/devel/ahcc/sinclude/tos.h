/*      TOS.H

        Tos Definition Includes

        Copyright (c) Borland International 1990
        All Rights Reserved.

*/


#if !defined( __TOS )
#define __TOS

#include <trap.h>		/* AHCC: __syscall__ */

typedef struct          /* used by Cconrs */
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} LINE;


typedef struct          /* used by Fsetdta, Fgetdta */
{
    char            d_reserved[21];
    unsigned char   d_attrib;
    unsigned short  d_time;
    unsigned short  d_date;
    unsigned long   d_length;
    char            d_fname[14];
} DTA;


typedef struct          /* used by Dfree */
{
    unsigned long   b_free;
    unsigned long   b_total;
    unsigned long   b_secsiz;
    unsigned long   b_clsiz;
} DISKINFO;


typedef struct baspag   /* used by Pexec */
{
        void    *p_lowtpa;
        void    *p_hitpa;
        void    *p_tbase;
        long    p_tlen;
        void    *p_dbase;
        long    p_dlen;
        void    *p_bbase;
        long    p_blen;
        DTA     *p_dta;
        struct baspag *p_parent;
        long    p_resrvd0;
        char    *p_env;
        char    p_stdfh[6];
        char    p_resrvd1;
        char    p_curdrv;
        long    p_resrvd2[18];
        char    p_cmdlin[128];
} BASPAG;


typedef struct          /* used by Getbpb */
{
	short recsiz,
		clsiz,
		clsizb,
		rdlen,
		fsiz,
		fatrec,
		datrec,
		numcl,
		bflags;
	short dntracks,		/* HR 2'97 added */
		dnsides,
		dspc,
		dspt,
		dhidden;
	long dserial;
} BPB;


#ifndef HAVE_DOSTIME
typedef struct
{
        unsigned short time;
        unsigned short date;
} DOSTIME;
#define HAVE_DOSTIME 1
#endif

typedef struct          /* used by Iorec */
{
        void    *ibuf;
        short   ibufsiz;
        short   ibufhd;
        short   ibuftl;
        short   ibuflow;
        short   ibufhi;
} IOREC;


typedef struct          /* used by Kbdvbase */
{
        void    (*kb_midivec)();
        void    (*kb_vkbderr)();
        void    (*kb_vmiderr)();
        void    (*kb_statvec)();
        void    (*kb_mousevec)();
        void    (*kb_clockvec)();
        void    (*kb_joyvec)();
        void    (*kb_midisys)();
        void    (*kb_kbdsys)();
} KBDVBASE;


typedef struct          /* used by Pexec */
{
        unsigned char   length;
        char            command_tail[128];
} COMMAND;


typedef struct          /* used by Initmouse */
{
        char    topmode;
        char    buttons;
        char    x_scale;
        char    y_scale;
        short   x_max;
        short   y_max;
        short   x_start;
        short   y_start;
} MOUSE;


typedef struct          /* used by Prtblk */
{
        void    *pb_scrptr;
        short   pb_offset;
        short   pb_width;
        short   pb_height;
        short   pb_left;
        short   pb_right;
        short   pb_screz;
        short   pb_prrez;
        void    *pb_colptr;
        short   pb_prtype;
        short   pb_prport;
        void    *pb_mask;
} PBDEF;


typedef struct          /* used by Keytbl */
{
        char *unshift;
        char *shift;
        char *capslock;
} KEYTAB;


typedef struct __md
{
        struct __md *m_link;
        void        *m_start;
        long        m_length;
        BASPAG      *m_own;
} MD;


typedef struct          /* used by Getmpb */
{
        MD *mp_mfl;
        MD *mp_mal;
        MD *mp_rover;
} MPB;

typedef struct
{
        short (*Bconstat) ();
        long  (*Bconin) ();
        short (*Bcostat) ();
        void  (*Bconout) ();
        long  (*Rsconf) ();
        IOREC *iorec;
} MAPTAB;

typedef struct
{
        MAPTAB *maptab;
        short  maptabsize;
} BCONMAP;

/* system variable _sysbase (0x4F2L) points to next structure         */
typedef struct _syshdr
{
    unsigned short os_entry;   /* $00 BRA to reset handler             */
    unsigned short os_version; /* $02 TOS version number               */
    void           *os_start;  /* $04 -> reset handler                 */
    struct _syshdr *os_base;   /* $08 -> baseof OS                     */
    void           *os_membot; /* $0c -> end BIOS/GEMDOS/VDI ram usage */
    void           *os_rsv1;   /* $10 << unused,reserved >>            */
    long           *os_magic;  /* $14 -> GEM memoryusage parm. block   */
    long           os_gendat;  /* $18 Date of system build($MMDDYYYY)  */
    short          os_palmode; /* $1c OS configuration bits            */
    short          os_gendatg; /* $1e DOS-format date of systembuild   */
/*
    The next three fields are only available in TOS versions 1.2 and
    greater
*/
    void           *_root;     /* $20 -> base of OS pool               */
    long           *kbshift;   /* $24 -> keyboard shift state variable */
    BASPAG         **_run;     /* $28 -> GEMDOS PID of current process */
    void           *p_rsv2;    /* $2c << unused, reserved >>           */
} SYSHDR;



/* attributes for Fcreate/Fsfirst/Fsnext: */

#define FA_READONLY     0x01
#define FA_HIDDEN       0x02
#define FA_SYSTEM       0x04
#define FA_VOLUME       0x08
#define FA_SUBDIR       0x10
#define FA_ARCHIVE      0x20

/* Fopen modes: */

#define FO_READ         0
#define FO_WRITE        1
#define FO_RW           2

extern BASPAG *_BasPag;
extern long _PgmSize;

long    TRAP( 1)	gemdos( void, ... );
long    TRAP(13)	bios  ( void, ... );
long    TRAP(14)	xbios ( void, ... );

/****** Tos *************************************************************/

void    GEMDOS(0)	Pterm0( void );
long    GEMDOS(1)	Cconin( void );
void    GEMDOS(2)	Cconout( short c );
short   GEMDOS(3)	Cauxin( void );
void    GEMDOS(4)	Cauxout( short c );
short   GEMDOS(5)	Cprnout( short c );
long    GEMDOS(6)	Crawio( short w );
long    GEMDOS(7)	Crawcin( void );
long    GEMDOS(8)	Cnecin( void );
short   GEMDOS(9)	Cconws( const char *buf );
void    GEMDOS(10)	Cconrs( LINE *buf );
short   GEMDOS(11)	Cconis( void );
long    GEMDOS(14)	Dsetdrv( short drv );
short   GEMDOS(16)	Cconos( void );
short   GEMDOS(17)	Cprnos( void );
short   GEMDOS(18)	Cauxis( void );
short   GEMDOS(19)	Cauxos( void );
short   GEMDOS(25)	Dgetdrv( void );
void    GEMDOS(26)	Fsetdta( DTA *buf );
long    GEMDOS(32)	Super( void *stack );
unsigned short GEMDOS(42)	Tgetdate( void );
unsigned short GEMDOS(43)	Tsetdate( unsigned short date );
unsigned short GEMDOS(44)	Tgettime( void );
unsigned short GEMDOS(45)	Tsettime( unsigned short time );
DTA  *  GEMDOS(47)	Fgetdta( void );
short   GEMDOS(48)	Sversion( void );
void    GEMDOS(49)	Ptermres( long keepcnt, short retcode );
short   GEMDOS(54)	Dfree( DISKINFO *buf, short driveno );
short   GEMDOS(57)	Dcreate( const char *path );
short   GEMDOS(58)	Ddelete( const char *path );
short   GEMDOS(59)	Dsetpath( const char *path );
long    GEMDOS(60)	Fcreate( const char *filename, short attr );
long    GEMDOS(61)	Fopen( const char *filename, short mo );
short   GEMDOS(62)	Fclose( short handle );
long    GEMDOS(63)	Fread( short handle, long count, void *buf );
long    GEMDOS(64)	Fwrite( short handle, long count, void *buf );
short   GEMDOS(65)	Fdelete( const char *filename );
long    GEMDOS(66)	Fseek( long offset, short handle, short seekmode );
short   GEMDOS(67)	Fattrib( const char *filename, short wflag, short attrib );
long    GEMDOS(69)	Fdup( short handle );
short   GEMDOS(70)	Fforce( short stch, short nonstdh );
short   GEMDOS(71)	Dgetpath( char *path, short driveno );
void *  GEMDOS(72)	Malloc( long number );
short   GEMDOS(73)	Mfree( void *block );
short   GEMDOS(74)	Mshrink( short zero, void *block, long newsiz );
long    GEMDOS(75)	Pexec( short mo, char *ptr1, void *ptr2, void *ptr3 );
void    GEMDOS(76)	Pterm( short retcode );
short   GEMDOS(78)	Fsfirst( const char *filename, short attr );
short   GEMDOS(79)	Fsnext( void );
short   GEMDOS(86)	Frename( short zero, const char *oldname, const char *newname );
short   GEMDOS(87)	Fdatime( DOSTIME *timeptr, short handle, short wflag );
short   GEMDOS(0x119)	Pdomain( short newdom );
void *  GEMDOS(0x112)	Psignal( short sig, void *handler );

/****** TOS 030 Gemdos Extension ****************************************/

void *  GEMDOS(68)	Mxalloc( long number, short mo );
long    GEMDOS(20)	Maddalt( void *start, long size );

/****** Network Gemdos Extension ****************************************/

long    GEMDOS(92)	Flock( short handle, short mo, long start, long length );

/****** Bios ************************************************************/

void    BIOS( 0)	Getmpb( MPB *ptr );
short   BIOS( 1)	Bconstat( short dev );
long    BIOS( 2)	Bconin( short dev );
long    BIOS( 3)	Bconout( short dev, short c );
long    BIOS( 4)	Rwabs( short rwflag, void *buf, short cnt, short recnr, short dev );
void    (* BIOS(5)	Setexc( short number, void (*exchdlr)() )) ();
long    BIOS( 6)	Tickcal( void );
BPB *	BIOS( 7)	Getbpb( short dev );
long    BIOS( 8)	Bcostat( short dev );
long    BIOS( 9)	Mediach( short dev );
long    BIOS(10)	Drvmap( void );
long    BIOS(11)	Kbshift( short mo );
long    BIOS(12)	Lrwabs( short rwflag, void *buf, short cnt, short recnr, short dev );

/****** XBios ***********************************************************/

void    XBIOS(0)	Initmouse( short , MOUSE *, void (*)() );
void *	XBIOS(1)	Ssbrk( short count );
void *  XBIOS(2)	Physbase( void );
void *	XBIOS(3)	Logbase( void );
short   XBIOS(4)	Getrez( void );
void    XBIOS(5)	Setscreen( void *laddr, void *paddr, short rez );
void    XBIOS(6)	Setpalette( void *pallptr );
short   XBIOS(7)	Setcolor( short colornum, short color );
short   XBIOS(8)	Floprd( void *buf, void *filler, short devno, short sectno,
               short trackno, short sideno, short count );
short   XBIOS(9)	Flopwr( void *buf, void *filler, short devno, short sectno,
               short trackno, short sideno, short count );
short   XBIOS(10)	Flopfmt( void *buf, void *filler, short devno, short spt, short trackno,
                short sideno, short interlv, long magic, short virgin );
void    XBIOS(12)	Midiws( short cnt, void *ptr );
void    XBIOS(13)	Mfpint( short erno, void (*vector)() );
IOREC *	XBIOS(14)	Iorec( short dev );
long    XBIOS(15)	Rsconf( short baud, short ctr, short ucr, short rsr, short tsr, short scr );
KEYTAB *XBIOS(16)	Keytbl( void *unshift, void *shift, void *capslock );
long    XBIOS(17)	Random( void );
void    XBIOS(18)	Protobt( void *buf, long serialno, short disktype, short execflag );
short   XBIOS(19)	Flopver( void *buf, void *filler, short devno, short sectno,
                short trackno, short sideno, short count );
void    XBIOS(20)	Scrdmp( void );
short   XBIOS(21)	Cursconf( short func, short rate );
void    XBIOS(22)	Settime( unsigned long time );
unsigned
long	XBIOS(23)	Gettime( void );
void    XBIOS(24)	Bioskeys( void );
void    XBIOS(25)	Ikbdws( short count, void *ptr );
void    XBIOS(26)	Jdisint( short number );
void    XBIOS(27)	Jenabint( short number );
char    XBIOS(28)	Giaccess( char data, short regno );
void    XBIOS(29)	Offgibit( short bitno );
void    XBIOS(30)	Ongibit( short bitno );
void    XBIOS(31)	Xbtimer( short timer, short control, short data, void (*vector)() );
void *  XBIOS(32)	Dosound( void *buf );
short   XBIOS(33)	Setprt( short config );
KBDVBASE * XBIOS(34)Kbdvbase( void );
short   XBIOS(35)	Kbrate( short initial, short repeat );
void    XBIOS(36)	Prtblk( PBDEF *par );
void    XBIOS(37)	Vsync( void );
typedef long Supfunc(void);
long    XBIOS(38)	Supexec( Supfunc *func);
void    XBIOS(39)	Puntaes( void );
short   XBIOS(41)	Floprate( short devno, short newrate );
short   XBIOS(64)	Blitmode( short mo );

/* TOS030 XBios */
short   XBIOS(42)	DMAread( long sector, short count, void *buffer, short devno );
short   XBIOS(43)	DMAwrite( long sector, short count, void *buffer, short devno );
long    XBIOS(44)	Bconmap( short devno );
short   XBIOS(46)	NVMaccess( short opcode, short start, short count, void *buffer );
short   XBIOS(80)	Esetshift( short shftMode );
short   XBIOS(81)	Egetshift( void );
short   XBIOS(82)	EsetBank( short bankNum );
short   XBIOS(83)	EsetColor( short colorNum, short color );
void    XBIOS(84)	EsetPalette( short colorNum, short count, short *palettePtr );
void    XBIOS(85)	EgetPalette( short colorNum, short count, short *palettePtr );
short   XBIOS(86)	EsetGray( short swtch );
short   XBIOS(87)	EsetSmear( short swtch );

/* MinT Gemdos */
#ifdef __MINT__
#include <mint.h>
#endif

/* Falcon Gemdos*/
#ifdef __FALCON__
#include <falcon.h>
#endif

#endif

/************************************************************************/
