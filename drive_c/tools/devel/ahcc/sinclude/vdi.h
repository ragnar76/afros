/*      VDI.H

        GEM VDI Definitions

        Copyright (c) Borland International 1990
        All Rights Reserved.
*/


#if  !defined( __VDI__ )
#define __VDI__
#define VDI_H

typedef struct
{
    short    contrl[15];
    short    intin[132];
    short    intout[140];
    short    ptsin[145];
    short    ptsout[145];
} VDIPARBLK;

typedef struct
{
    short    *contrl;
    short    *intin;
    short    *ptsin;
    short    *intout;
    short    *ptsout;
} VDIPB;

extern  VDIPARBLK _VDIParBlk;

void vdi( VDIPB *vdipb );


/****** Control definitions *********************************************/

void    v_opnwk(short *work_in, short *handle,short *work_out);
void    v_clswk( short handle );
void    v_opnvwk(short *work_in,short *handle,short *work_out);
void    v_clsvwk( short handle );
void    v_clrwk( short handle );
void    v_updwk( short handle );
short             vst_load_fonts( short handle, short select );
void    vst_unload_fonts( short handle, short select );
void    vs_clip( short handle, short clip_flag, short *pxyarray );


/****** Output definitions **********************************************/

void    v_pline( short handle, short count, short *pxyarray );
void    v_pmarker( short handle, short count, short *pxyarray );
void    v_gtext( short handle, short x, short y, char *string );
void    v_fillarea( short handle, short count, short *pxyarray );
void    v_cellarray( short handle, short *pxyarray, short row_length,
                     short el_used, short num_rows, short wrt_mode,
                     short *colarray );
void    v_contourfill( short handle, short x, short y, short index );
void    vr_recfl( short handle, short *pxyarray );
void    v_bar( short handle, short *pxyarray );
void    v_arc( short handle, short x, short y, short radius,
               short begang, short endang );
void    v_pieslice( short handle, short x, short y, short radius,
                    short begang, short endang );
void    v_circle( short handle, short x, short y, short radius );
void    v_ellarc( short handle, short x, short y, short xradius,
                  short yradius, short begang, short endang );
void    v_ellpie( short handle, short x, short y, short xradius,
                  short yradius, short begang, short endang );
void    v_ellipse( short handle, short x, short y, short xradius,
                   short yradius  );
void    v_rbox  ( short handle, short *pxyarray );
void    v_rfbox ( short handle, short *pxyarray );
void    v_justified( short handle,short x, short y, char *string,
                     short length, short word_space,
                     short char_space );


/****** Attribute definitions *****************************************/

#define IP_HOLLOW       0
#define IP_1PATT        1
#define IP_2PATT        2
#define IP_3PATT        3
#define IP_4PATT        4
#define IP_5PATT        5
#define IP_6PATT        6
#define IP_SOLID        7


/* gsx modes */

#define MD_REPLACE      1
#define MD_TRANS        2
#define MD_XOR          3
#define MD_ERASE        4


/* gsx styles */

#define FIS_HOLLOW      0
#define FIS_SOLID       1
#define FIS_PATTERN     2
#define FIS_HATCH       3
#define FIS_USER        4


/* bit blt rules */

#define ALL_WHITE        0
#define S_AND_D          1
#define S_AND_NOTD       2
#define S_ONLY           3
#define NOTS_AND_D       4
#define D_ONLY           5
#define S_XOR_D          6
#define S_OR_D           7
#define NOT_SORD         8
#define NOT_SXORD        9
#define D_INVERT        10
#define NOT_D           11
#define S_OR_NOTD       12
#define NOTS_OR_D       13
#define NOT_SANDD       14
#define ALL_BLACK       15


/* linetypes */

#define SOLID           1
#define LONGDASH        2
#define DOT             3
#define DASHDOT         4
#define DASH            5
#define DASH2DOT        6
#define USERLINE        7

#define SQUARE          0
#define ARROWED         1
#define ROUND           2

/* Lattice C should better use the TF_xxx-constants anyway... */
#define THICKENED	0x01
#define SHADED		0x02
#define SKEWED		0x04
#define UNDERLINED	0x08
#define OUTLINE		0x10
#define SHADOW		0x20

short     vswr_mode( short handle, short mo );
void    vs_color( short handle, short index, short *rgb_in );
short     vsl_type( short handle, short style );
void    vsl_udsty( short handle, short pattern );
short     vsl_width( short handle, short width );
short     vsl_color( short handle, short color_index );
void    vsl_ends( short handle, short beg_style, short end_style );
short     vsm_type( short handle, short symbol );
short     vsm_height( short handle, short height );
short     vsm_color( short handle, short color_index );
void    vst_height( short handle, short height, short *char_width,
                    short *char_height, short *cell_width,
                    short *cell_height );
short     vst_point( short handle, short point, short *char_width,
                    short *char_height, short *cell_width,
                    short *cell_height );
short     vst_rotation( short handle, short angle );
short     vst_font( short handle, short font );
short     vst_color( short handle, short color_index );
short     vst_effects( short handle, short effect );
void    vst_alignment( short handle, short hor_in, short vert_in,
                       short *hor_out, short *vert_out );
short     vsf_interior( short handle, short style );
short     vsf_style( short handle, short style_index );
short     vsf_color( short handle, short color_index );
short     vsf_perimeter( short handle, short per_vis );
void    vsf_udpat( short handle, short *pfill_pat, short planes );


/****** Raster definitions *********************************************/

typedef struct
{
        void            *fd_addr;
        short             fd_w;
        short             fd_h;
        short             fd_wdwidth;
        short             fd_stand;
        short             fd_nplanes;
        short             fd_r1;
        short             fd_r2;
        short             fd_r3;
} MFDB;

void    vro_cpyfm( short handle, short vr_mode, short *pxyarray,
                   MFDB *psrcMFDB, MFDB *pdesMFDB );
void    vrt_cpyfm( short handle, short vr_mode, short *pxyarray,
                   MFDB *psrcMFDB, MFDB *pdesMFDB,
                   short *color_index );
void    vr_trnfm( short handle, MFDB *psrcMFDB, MFDB *pdesMFDB );
void    v_get_pixel( short handle, short x, short y, short *pel,
                     short *index );


/****** Input definitions **********************************************/

void    vsin_mode( short handle, short dev_type, short mo );
void    vrq_locator( short handle, short x, short y, short *xout,
                     short *yout, short *term );
short     vsm_locator( short handle, short x, short y, short *xout,
                     short *yout, short *term );
void    vrq_valuator( short handle, short valuator_in,
                      short *valuator_out, short *terminator );
void    vsm_valuator( short handle, short val_in, short *val_out,
                      short *term, short *status );
void    vrq_choice( short handle, short ch_in, short *ch_out );
short     vsm_choice( short handle, short *choice );
void    vrq_string( short handle, short max_length, short echo_mode,
                    short *echo_xy, char *string );
short     vsm_string( short handle, short max_length, short echo_mode,
                    short *echo_xy, char *string );
void    vsc_form( short handle, short *pcur_form );
void    vex_timv( short handle, short (*tim_addr)(), short (**otim_addr)(),
                  short *tim_conv );
void    v_show_c( short handle, short reset );
void    v_hide_c( short handle );
void    vq_mouse( short handle, short *pstatus, short *x, short *y );
void    vex_butv( short handle, short (*pusrcode)(), short (**psavcode)() );
void    vex_motv( short handle, short (*pusrcode)(), short (**psavcode)() );
void    vex_curv( short handle, short (*pusrcode)(), short (**psavcode)() );
void    vex_whlv( short handle, short (*pusrcode)(), short (**psavcode)() );		/* HR 111002: wheel support */
void    vq_key_s( short handle, short *pstatus );


/****** Inquire definitions *******************************************/

void    vq_extnd( short handle, short owflag, short *work_out );
short     vq_color( short handle, short color_index,
                  short set_flag, short *rgb );
void    vql_attributes( short handle, short *attrib );
void    vqm_attributes( short handle, short *attrib );
void    vqf_attributes( short handle, short *attrib );
void    vqt_attributes( short handle, short *attrib );
void    vqt_extent( short handle, char *string, short *extent );
short     vqt_width( short handle, short character,
                   short *cell_width, short *left_delta,
                   short *right_delta );
short     vqt_name( short handle, short element_num, char *name );
void    vq_cellarray( short handle, short *pxyarray,
                      short row_length, short num_rows,
                      short *el_used, short *rows_used,
                      short *status, short *colarray );
void    vqin_mode( short handle, short dew_type, short *input_mode );
void    vqt_fontinfo( short handle, short *minADE, short *maxADE,
                      short *distances, short *maxwidth,
                      short *effects );


/****** Escape definitions *********************************************/

void    vq_chcells( short handle, short *rows, short *columns );
void    v_exit_cur( short handle );
void    v_enter_cur( short handle );
void    v_curup( short handle );
void    v_curdown( short handle );
void    v_curright( short handle );
void    v_curleft( short handle );
void    v_curhome( short handle );
void    v_eeos( short handle );
void    v_eeol( short handle );
void    vs_curaddress( short handle, short Row, short Column );
void    v_curaddress( short handle, short Row, short Column );
void    v_curtext( short handle, char *string );
void    v_rvon( short handle );
void    v_rvoff( short handle );
void    vq_curaddress( short handle, short *Row, short *Column );
short     vq_tabstatus( short handle );
void    v_hardcopy( short handle );
void    v_dspcur( short handle, short x, short y );
void    v_rmcur( short handle );
void    v_form_adv( short handle );
void    v_output_window( short handle, short *xyarray );
void    v_clear_disp_list( short handle );
void    v_bit_image( short handle, const char *filename,
                     short aspect, short x_scale, short y_scale,
                     short h_align, short v_align, short *xyarray );
void    vq_scan( short handle, short *g_slice, short *g_page,
                 short *a_slice, short *a_page, short *div_fac);
void    v_alpha_text( short handle, char *string );
void    vs_palette( short handle, short palette );
void	v_sound( short handle, short frequency, short duration );
short		vs_mute( short handle, short action );
void    vqp_films( short handle, char *film_names );
void    vqp_state( short handle, short *port, char *film_name,
                   short *lightness, short *interlace,
                   short *planes, short *indexes );
void    vsp_state( short handle, short port, short film_num,
                   short lightness, short interlace, short planes,
                   short *indexes );
void    vsp_save( short handle );
void    vsp_message( short handle );
short     vqp_error( short handle );
void    v_meta_extents( short handle, short min_x, short min_y,
                        short max_x, short max_y );
void    v_write_meta( short handle,
                      short num_intin, short *intin,
                      short num_ptsin, short *ptsin );
void    vm_coords( short handle, short llx, short lly, short urx, short ury );
void    vm_filename( short handle, const char *filename );
void    vm_pagesize( short handle, short pgwidth, short pdheight );
void    v_offset( short handle, short offset );
void    v_fontinit( short handle, short fh_high, short fh_low );
void    v_escape2000( short handle, short times );

void    vt_resolution( short handle, short xres, short yres,
                       short *xset, short *yset );
void    vt_axis( short handle, short xres, short yres,
                 short *xset, short *yset );
void    vt_origin( short handle, short xorigin, short yorigin );
void    vq_tdimensions( short handle, short *xdimension, short *ydimension );
void    vt_alignment( short handle, short dx, short dy );
void    vsp_film( short handle, short index, short lightness );
void    vsc_expose( short handle, short state );


#define GDOS_NONE      -2L            /* no GDOS installed           */
#define GDOS_FSM       0x5F46534DL    /* '_FSM' - FSMGDOS installed  */
#define GDOS_FNT       0x5F464E54L    /* '_FNT' - FONTGDOS installed */

short     vq_gdos( void );
long    vq_vgdos( void );

short     v_bez_on( short handle );
void    v_bez_off( short handle );
void    v_set_app_buff( short handle, void *address, short nparagraphs );
void    v_bez( short handle, short count, short *xyarr,
                char *bezarr, short *extent, short *totpts, short *totmoves );
void    v_bez_fill( short handle, short count, short *xyarr,
                     char *bezarr, short *extent, short *totpts,
                     short *totmoves );
short     v_bez_qual( short handle, short prcnt, short *actual );


/****** SpeedoGDOS definitions ********************************************/

typedef long  fix31;

void    vqt_f_extent( short handle, char *string, short *extent );
void    v_ftext( short handle, short x, short y, char *string );
void    v_ftext_offset( short handle, short x, short y, char *string, short *offset );
void    v_killoutline( short handle, void *component );
void    v_getoutline( short handle, short ch, short *xyarray,
                      char *bezarray, short maxverts, short *numverts );
void    vst_scratch( short handle, short mo );
void    vst_error( short handle, short mo, short *errorvar );
void    vqt_advance( short handle, short ch, short *advx, short *advy,
                     short *remx, short *remy );
void    vqt_advance32( short handle, short ch, fix31 *advx, fix31 *advy );
short     vst_arbpt( short handle, short point, short *chwd, short *chht,
                   short *cellwd, short *cellht );
fix31   vst_arbpt32( short handle, fix31 point, short *chwd, short *chht,
                     short *cellwd, short *cellht );
void    vst_charmap( short handle, short mo );
void    v_getbitmap_info( short handle, short ch, fix31 *advx, fix31 *advy,
                          fix31 *xoff, fix31 *yoff, fix31 *width,
                          fix31 *height );
void    vqt_pairkern( short handle, short ch1, short ch2, fix31 *x, fix31 *y );
void    vqt_trackkern( short handle, fix31 *x, fix31 *y );
void    vqt_fontheader( short handle, char *buffer, char *pathname );
void    vst_kern( short handle, short tmode, short pmode, short *tracks,
                  short *pairs );
fix31   vst_setsize32( short handle, fix31 point, short *chwd, short *chht,
                       short *cellwd, short *cellht );
void    vqt_devinfo( short handle, short devnum, short *devexits,
                     char *devstr );
short     v_flushcache( short handle );
void    vqt_cachesize( short handle, short which_cache, long *size );
void    vqt_get_table( short handle, short **map );
short     v_loadcache( short handle, char *filename, short mo );
short     v_savecache( short handle, char *filename );
short     vst_setsize( short handle, short point, short *chwd, short *chht,
                     short *cellwd, short *cellht );
short     vst_skew( short handle, short skew );


#endif

/***********************************************************************/
