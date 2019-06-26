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
    short   blocktype;
    long    blocksize;
    void    *blockaddr;
} DSPBLOCK;


long    locksnd( void );
long    unlocksnd( void );
long    soundcmd( short mo, short data );
long    setbuffer( short reg, void *begaddr, void *endaddr );
long    setmode( short mo );
long    settracks( short playtracks, short rectracks );
long    setmontracks( short montrack );
long    setinterrupt( short src_inter, short cause );
long    buffoper( short mo );
long    dsptristate( short dspxmit, short dsprec );
long    gpio( short mo, short data );
long    devconnect( short src, short dst, short srcclk, short prescale,
                    short protocol );
long    sndstatus( short reset );
long    buffptr( long *ptr );

short     Dsp_LoadProg( char *file, short ability, char *buffer );
long    Dsp_LodToBinary( char *file, char *codeptr );
void    Dsp_DoBlock( char *data_in, long size_in, char *data_out,
                     long size_out );
void    Dsp_BlkHandShake( char *data_in, long size_in, char *data_out,
                          long size_out );
void    Dsp_BlkUnpacked( long *data_in, long size_in, long *data_out,
                         long size_out );
void    Dsp_InStream( char *data_in, long block_size, long num_blocks,
                      long *blocks_done );
void    Dsp_OutStream( char *data_out, long block_size, long num_blocks,
                       long *blocks_done );
void    Dsp_IOStream( char *data_in, char *data_out, long block_insize,
                      long block_outsize, long num_blocks,
                      long *blocks_done );
void    Dsp_RemoveInterrupts( short mask );
short     Dsp_GetWordSize( void );
short     Dsp_Lock( void );
void    Dsp_Unlock( void );
void    Dsp_Available( long *xavailable, long *yavailable );
short     Dsp_Reserve( long xreserve, long yreserve );
void    Dsp_ExecProg( char *codeptr, long codesize, short ability );
void    Dsp_ExecBoot( char *codeptr, long codesize, short ability );
void    Dsp_TriggerHC( short vector );
short     Dsp_RequestUniqueAbility( void );
short     Dsp_GetProgAbility( void );
void    Dsp_FlushSubroutines( void );
short     Dsp_LoadSubroutine( char *codeptr, long codesize, short ability );
short     Dsp_InqSubrAbility( short ability );
short     Dsp_RunSubroutine( short handle );
short     Dsp_Hf0( short flag );
short     Dsp_Hf1( short flag );
short     Dsp_Hf2( void );
short     Dsp_Hf3( void );
void    Dsp_BlkWords( void *data_in, long size_in, void *data_out,
                      long size_out );
void    Dsp_BlkBytes( void *data_in, long size_in, void *data_out,
                      long size_out );
char    Dsp_HStat( void );
void    Dsp_SetVectors( void (*receiver)( ), long (*transmitter)( ));
void    Dsp_MultBlocks( long numsend, long numreceive,
                        DSPBLOCK *sendblocks, DSPBLOCK *receiveblocks );
short     Vsetmode( short modecode );
short     mon_type( void );
long    VgetSize( short mo );
void    VsetSync( short flag );
void    VsetRGB( short index, short count, long *array );
void    VgetRGB( short index, short count, long *array );
void    VsetMask( short ormask, short andmask, short overlay );
