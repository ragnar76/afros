/*	AES.H

	GEM AES Definitions

	Copyright (c) Borland International 1990
	All Rights Reserved.

	mrt 1992 H. Robbers Amsterdam:

	space --> tabs.
	prefixes in structs removed.
	lists of #defines replaced by enums.
	types in aggregates amalgamated.
	VRECT (x,y,jx,jy); juxtapositioned coordinates (x1,y1,x2,y2)

	12-07-93  PC 1.1
	12-04-99  Multi Threading AES and further modernization
				and replace int by short.
	18-04-99  Reinstate prefixes; now under condition.
*/

#if  !defined __AES__
#define __AES__

#include <gempb.h>		/* These hold the basics used in the lib itself */

typedef enum
{
	GAI_WDLG = 0x0001,		/* wdlg_xx()-Funktionen vorhanden */
	GAI_LBOX = 0x0002,		/* lbox_xx()-Funktionen vorhanden */
	GAI_FNTS = 0x0004,		/* fnts_xx()-Funktionen vorhanden */
	GAI_FSEL = 0x0008,		/* neue Dateiauswahl vorhanden */

	GAI_MAGIC= 0x0100,		/* MagiC-AES vorhanden */
	GAI_INFO = 0x0200,		/* appl_getinfo() vorhanden */
	GAI_3D   = 0x0400,		/* 3D-Look vorhanden */
	GAI_CICN = 0x0800,		/* Color-Icons vorhanden */
	GAI_APTERM = 0x1000,	/* AP_TERM wird unterstÅtzt */
	GAI_GSHORTCUT = 0x2000,	/* Objekttyp G_SHORTCUT wird unterstÅtzt */
	GAI_WHITEBAK = 0x4000	/* WHITEBAK objects */
} GAI;

typedef struct
{
	long	magic;							/* muû $87654321 sein */
	void *	membot;							/* Ende der AES-Variablen */
	void *	aes_start;						/* Startadresse */

	long	magic2;							/* ist 'MAGX' */
	long	date;							/* Erstelldatum: ttmmjjjj */
	void (*chgres)( short res, short txt );	/* Auflîsung Ñndern */
	long	(**shel_vector)(void);			/* ROM-Desktop */
	char *	aes_bootdrv;					/* Hierhin kommt DESKTOP.INF */
	short *	vdi_device;					/* vom AES benutzter Treiber */
	void *	reservd1;
	void *	reservd2;
	void *	reservd3;

	short version,						/* Versionsnummer */
	      release;						/* Release-Status */

} AESVARS;

typedef	void *DOSVARS;						/* wird in diesem Source nicht benutzt */

typedef struct
{
	long		config_status;
	DOSVARS *	dosvars;
	AESVARS *	aesvars;
} MAGX_COOKIE;

/* MultiTOS Drag&Drop definitions */

typedef enum
{
	DD_OK,
	DD_NAK,
	DD_EXT,
	DD_LEN,

	DD_TIMEOUT = 4000,			/* Timeout in ms */
	DD_EXTSIZE = 32,			/* LÑnge des Formatfelds */
	DD_NAMEMAX = 128,			/* maximale LÑnge eines Formatnamens */

	DD_NUMEXTS = 8,				/* Anzahl der Formate */
	DD_HDRMIN  = 9,				/* minimale LÑnge des Drag&Drop-Headers */

	DD_HDRMAX  = ( 8 + DD_NAMEMAX )	/* maximale LÑnge */
} DD_S;

#define DD_FNAME	"u:/pipe/dragdrop.aa"

/****** Application definitions *****************************************/

typedef struct
{
	short	dst_apid;
	short	unique_flg;
	void *	attached_mem;
	short *	msgbuf;
} XAESMSG;

short G_decl G_nv(appl_init);
short G_decl G_n(appl_read)		( short ap_rid, short ap_rlength, void *ap_rpbuff dglob);
short G_decl G_n(appl_write)	( short ap_wid, short ap_wlength, void *ap_wpbuff dglob);
short G_decl G_n(appl_find)		( const char *ap_fpname  dglob);
short G_decl G_n(appl_tplay)	( void *ap_tpmem, short ap_tpnum, short ap_tpscale  dglob);
short G_decl G_n(appl_trecord)	( void *ap_trmem, short ap_trcount  dglob);
short G_decl G_nv(appl_exit);
short G_decl G_n(appl_search)	( short ap_smode, char *ap_sname, short *ap_stype,
								  short *ap_sid  dglob);
short G_decl G_n(appl_getinfo)	( short ap_gtype, short *ap_gout1, short *ap_gout2,
								  short *ap_gout3, short *ap_gout4  dglob);
short G_decl G_n(appl_control)	( short ap_id, short what, void *out);

#define appl_bvset ( disks, harddisks ) /* Funktion ignorieren (GEM fÅr Dose): void appl_bvset( short disks, short harddisks ); */

#define vq_aes() ( appl_init() >= 0 )	/* WORD	vq_aes( void ); */

/****** Event definitions ***********************************************/

typedef enum
{
	MN_SELECTED		=10,
	WM_REDRAW		=20,
	WM_TOPPED,
	WM_CLOSED,
	WM_FULLED,
	WM_ARROWED,
	WM_HSLID,
	WM_VSLID,
	WM_SIZED,
	WM_MOVED,
	WM_NEWTOP,
	WM_UNTOPPED		=30,	/* GEM  2.x	*/
	WM_ONTOP,    			/* AES 4.0	*/
	WM_UNKNOWN,				/* AES 4.1	*/
	WM_BACK,				/* WINX 	*/
	WM_BOTTOMED = WM_BACK,	/* AES 4.1	*/
	WM_ICONIFY,				/* AES 4.1 	*/
	WM_UNICONIFY,			/* AES 4.1	*/
	WM_ALLICONIFY,			/* AES 4.1	*/
	WM_TOOLBAR,				/* AES 4.1	*/
	AC_OPEN			=40,
	AC_CLOSE,
	CT_UPDATE		=50,
	CT_MOVE,
	CT_NEWTOP,
	CT_KEY,
	AP_TERM			=50,
	AP_TFAIL,
	AP_RESCHG		=57,
	SHUT_COMPLETED	=60,
	RESCH_COMPLETED,
	AP_DRAGDROP		=63,
	SH_WDRAW		=72,	/* MultiTOS    */
	SC_CHANGED		=80,	/* MultiTOS    */
	PRN_CHANGED		=82,
	FNT_CHANGED,
	THR_EXIT		=88,	/* MagiC 4.5	*/
	PA_EXIT,				/* MagiC 3     */
	CH_EXIT			=90,	/* MultiTOS    */
	WM_M_BDROPPED	=100,	/* KAOS 1.4    */
	SM_M_SPECIAL,			/* MAG!X       */
	SM_M_RES2,				/* MAG!X       */
	SM_M_RES3,				/* MAG!X       */
	SM_M_RES4,				/* MAG!X       */
	SM_M_RES5,				/* MAG!X       */
	SM_M_RES6,				/* MAG!X       */
	SM_M_RES7,				/* MAG!X       */
	SM_M_RES8,				/* MAG!X       */
	SM_M_RES9,				/* MAG!X       */
	WM_SHADED		=22360,	/* [WM_SHADED apid 0 win 0 0 0 0] */
	WM_UNSHADED		=22361	/* [WM_UNSHADED apid 0 win 0 0 0 0] */
} MESAG_TY;

/* SM_M_SPECIAL codes */

#define SMC_TIDY_UP		0	/* MagiC 2  	*/
#define SMC_TERMINATE	1	/* MagiC 2  	*/
#define SMC_SWITCH		2	/* MagiC 2  	*/
#define SMC_FREEZE		3	/* MagiC 2  	*/
#define SMC_UNFREEZE	4	/* MagiC 2  	*/
#define SMC_RES5		5	/* MagiC 2  	*/
#define SMC_UNHIDEALL	6	/* MagiC 3.1	*/
#define SMC_HIDEOTHERS	7	/* MagiC 3.1	*/
#define SMC_HIDEACT		8	/* MagiC 3.1	*/
/* Keybord states */

typedef enum
{
	K_RSHIFT=0x0001,
	K_LSHIFT=0x0002,
	K_CTRL  =0x0004,
	K_ALT   =0x0008
} K_STATE;

typedef struct rect
{
	short x,y,w,h;
} GRECT, RECT;

#if !G_MODIFIED
short G_decl G_nv(evnt_keybd);
short G_decl G_n(evnt_button)( short ev_bclicks, short ev_bmask, short ev_bstate,
				short *ev_bmx, short *ev_bmy, short *ev_bbutton,
				short *ev_bkstate dglob);
short G_decl G_n(evnt_mouse)( short ev_moflags, short ev_mox, short ev_moy,
				short ev_mowidth, short ev_moheight, short *ev_momx,
				short *ev_momy, short *ev_mobutton,
				short *ev_mokstate dglob);
short G_decl G_n(evnt_mesag)( short *ev_mgpbuff dglob );
short G_decl G_n(evnt_timer)( short ev_tlocount, short ev_thicount dglob );
short G_decl G_n(evnt_multi)( short ev_mflags, short ev_mbclicks, short ev_mbmask,
				short ev_mbstate, short ev_mm1flags, short ev_mm1x,
				short ev_mm1y, short ev_mm1width, short ev_mm1height,
				short ev_mm2flags, short ev_mm2x, short ev_mm2y,
				short ev_mm2width, short ev_mm2height,
				short *ev_mmgpbuff, short ev_mtlocount,
				short ev_mthicount, short *ev_mmox, short *ev_mmoy,
				short *ev_mmbutton, short *ev_mmokstate,
				short *ev_mkreturn, short *ev_mbreturn dglob );
short G_decl G_n(evnt_dclick)( short ev_dnew, short ev_dgetset dglob );
#else
short G_decl G_nv(evnt_keybd);
short G_decl G_n(evnt_button)(short clks,short mask,short state,
				EVNTDATA *ev dglob);
short G_decl G_n(evnt_mouse)(short flags, GRECT *g, EVNTDATA *ev dglob);
short G_decl G_n(evnt_mesag)(short *ev_mgpbuff dglob );
short G_decl G_n(evnt_timer)(unsigned long ms dglob);
short G_decl G_n(evnt_multi)(short flags,short clks,short mask,short state,
				short m1flags,GRECT *g1,
				short m2flags,GRECT *g2,
				short *msgpipe,
				unsigned long ms,
				EVNTDATA *ev,
				short *toets,short *oclks dglob);
short G_decl G_n(evnt_dclicks)(short new,short getset dglob);
#endif
#if G_EXT
void G_n(EVNT_multi)( short evtypes, short nclicks, short bmask, short bstate,
				MOBLK *m1, MOBLK *m2, G_ul ms,
				EVNT *event dglob );
#endif

/* this is our special invention to increase evnt_multi performance */

typedef struct /* Special type for EventMulti */
{
	/* input parameters */
	short flags, bclicks, bmask, bstate,
	      m1flags, m1x, m1y, m1width, m1height,
	      m2flags, m2x, m2y, m2width, m2height,
	      tlocount, thicount;
	/* output parameters */
	short wich,
	      mox, moy,
	      mobutton, mokstate,
	      kreturn, breturn;
	/* message buffer */
	short mgpbuf[8];
} EVENT;

short G_decl G_n(EvntMulti)( EVENT *evnt_struct dglob);


/****** Object definitions **********************************************/
typedef enum
{
	G_MIN=20,
	G_BOX=G_MIN,
	G_TEXT,
	G_BOXTEXT,
	G_IMAGE,
	G_USERDEF,
	G_IBOX,
	G_BUTTON,
	G_BOXCHAR,
	G_STRING,
	G_FTEXT,
	G_FBOXTEXT,
	G_ICON,
	G_TITLE,
	G_CICON,

/* HR: for completeness */

	G_SWBUTTON,		/* MAG!X       */
	G_POPUP,		/* MAG!X       */
	G_WINTITLE,		/* MagiC 3.1	*/
	G_EDIT,
	G_SHORTCUT,		/* MagiC 6 */
	G_SLIST,		/* XaAES extended object - scrolling list */
	G_UNKNOWN,
	G_MAX			/* Maximum number of object types */
} OBJECT_TY;

/* Object flags */

typedef enum
{
	NONE	  =0x0000,
	SELECTABLE=0x0001,
	DEFAULT	  =0x0002,
	EXIT      =0x0004,
	EDITABLE  =0x0008,
	RBUTTON	  =0x0010,
	LASTOB    =0x0020,
	TOUCHEXIT =0x0040,
	HIDETREE  =0x0080,
	INDIRECT  =0x0100,
	FL3DNONE  =0x0000,
	FL3DIND   =0x0200,	/* 3D Indicator			  AES 4.0		*/
	FL3DBAK   =0x0400,	/* 3D Background		  AES 4.0		*/
	FL3DACT   =0x0600,	/* 3D Activator			  AES 4.0		*/
	FL3DMASK  =0x0600,
	SUBMENU   =0x0800
} OBJECT_FLAG;

/* Object states */

typedef enum
{
	NORMAL	=0x00,
	SELECTED=0x01,
	CROSSED =0x02,
	CHECKED =0x04,
	DISABLED=0x08,
	OUTLINED=0x10,
	SHADOWED=0x20,
	WHITEBAK=0x40,		/* TOS     & MagiC */
	DRAW3D  =0x80		/* GEM 2.x         */
} OBJECT_STATE;

/* objc_sysvar */

typedef enum
{
	LK3DIND		=1,	/* AES 4.0     */
	LK3DACT,		/* AES 4.0     */
	INDBUTCOL,		/* AES 4.0     */
	ACTBUTCOL,		/* AES 4.0     */
	BACKGRCOL,		/* AES 4.0     */
	AD3DVALUE,		/* AES 4.0     */
	MX_ENABLE3D	=10	/* MagiC 3.0   */
} OB_SYSVAR;

/* Object colors */
#if !defined __COLORS
#define __COLORS		/*	using AES-colors and BGI-colors
							is not possible	*/

typedef enum
{
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	CYAN,
	YELLOW,
	MAGENTA,
	LWHITE,
	LBLACK,
	LRED,
	LGREEN,
	LBLUE,
	LCYAN,
	LYELLOW,
	LMAGENTA
} AES_COLOR;
#endif

#define ROOT		0
#define MAX_LEN		81		/* max string length */
#define MAX_DEPTH	8		/* max depth of search or draw */


#define IBM			3		/* font types */
#define SMALL		5

typedef enum
{
	ED_START,				/* editable text field definitions */
	ED_INIT,
	ED_CHAR,
	ED_END
} EDOB_TY;

typedef enum
{
	TE_LEFT,				/* editable text justification */
	TE_RIGHT,
	TE_CNTR
} TE_JUST;

typedef struct orect
{
	struct orect * link;
	short x,y,w,h;
} ORECT;

typedef struct
{
	short x,y,
	      jx,jy;		/* VDI rectangle */
} VRECT;

/* Object structures */

typedef struct
{
	char *	text,		/* ptr to text (must be 1st)	*/
		 *	tmplt,		/* ptr to template				*/
		 *	valid;		/* ptr to validation			*/
	short	font,		/* font							*/
			junk1,		/* junk							*/
			just,		/* justification: left, right...*/
			color,		/* color information			*/
			junk2,		/* junk							*/
			thickness,	/* border thickness				*/
			txtlen,		/* text string length			*/
			tmplen;		/* template string length		*/
} TEDINFO;

typedef struct
{
	short *	mask,
		  *	data;
	char *	text;
	short	ch,
			xchar,
			ychar,
			xicon,
			yicon,
			wicon,
			hicon,
			xtext,
			ytext,
			wtext,
			htext;
} ICONBLK;

typedef struct cicon_data
{
	short	num_planes;
	short *	col_data;
	short *	col_mask;
	short *	sel_data;
	short *	sel_mask;
	struct cicon_data *	next_res;
} CICON;


typedef struct cicon_blk
{
	ICONBLK	monoblk;
	CICON *	mainlist;
} CICONBLK;

typedef struct
{
	short *	data,		/* ptr to bit forms data	*/
			wb,			/* width of form in bytes	*/
			hl,			/* height in lines			*/
			x,			/* source x in bit form		*/
			y,			/* source y in bit form		*/
			color;		/* foreground color			*/
} BITBLK;


struct __parmblk;

#if !((defined  __STDC__) && CDECL)
/*	   using this structure is not possible
 *      if ANSI keywords only is ON, and __Cdecl is non empty
 */
typedef struct
{
	short __Cdecl	(*ub_code)(struct __parmblk *parmblock);
	long			ub_parm;
} USERBLK;
#endif

typedef struct
{
	unsigned character   :  8;
	signed   framesize   :  8;
	unsigned framecol    :  4,
			 textcol     :  4,
			 textmode    :  1,
			 fillpattern :  3,
			 interiorcol :  4;
} bfobspec;

typedef union obspecptr
{
	long				index;
	union obspecptr *	indirect;
	bfobspec			obspec;
	TEDINFO *			tedinfo;
	ICONBLK *			iconblk;
	CICONBLK *			ciconblk;
	BITBLK *			bitblk;
#if !((defined  __STDC__) && CDECL)
/*	   using this structure is not possible
 *      if ANSI keywords only is ON, and __Cdecl is non empty
 */
	USERBLK *			userblk;
#endif
	char *				free_string;
} OBSPEC;

typedef struct
{
	short	next,		/* -> object's next sibling     */
			head,		/* -> head of object's children */
			tail;		/* -> tail of object's children */
	unsigned
	short	type,			/* object type: BOX, CHAR,...   */
			flags,		/* object flags                 */
			state;		/* state: SELECTED, OPEN, ...   */
	OBSPEC	spec;		/* "out": -> anything else      */
/* The following is in fact a GRECT, but is too offten used to change it */
	short	x,			/* upper left corner of object  */
			y,			/* upper left corner of object  */
			w,			/* object width                 */
			h;			/* object height                */
} OBJECT;

typedef struct __parmblk
{
	OBJECT  *tree;
	short	obj,
			prevstate,
			currstate;
	GRECT	size,
			clip;
	union
	{
		long	parm;
		char *	text;
	} P;
} PARMBLK;

typedef struct
{
	OBJECT *	tree;
	short		menu;
	short		item;
	short		scroll;
	short		keystate;
} MENU;

typedef struct
{
	long	Display;
	long	Drag;
	long	Delay;
	long	Speed;
	short	Height;
} MN_SET;

typedef struct
{
	char *	string;			/* etwa "TOS|KAOS|MAG!X"			*/
	short	num,			/* Nr. der aktuellen Zeichenkette	*/
			maxnum;			/* maximal erlaubtes <num>			*/
} SWINFO;

typedef struct
{
     OBJECT *	tree;		/* Popup- MenÅ					*/
     short		obnum;		/* aktuelles Objekt von <tree>	*/
} POPINFO;

#define FORM_MAX 15

typedef struct
{
	short	ty,		/* type: 's', 'r', 'd' or 'l' */
			l;		/* l = max lengte reply or default if zero */
	char *	pr;		/* prompt */
	void *	rep;	/* reply */
} FORM_INPUT;

/****** Menu definitions ************************************************/

/* menu_bar modes */

typedef enum
{
	MENU_HIDE,					/* TOS         */
	MENU_SHOW,					/* TOS         */
	MENU_INSTL = 100			/* MAG!X       */
} MBAR_DO;

short G_decl G_n(menu_bar)( OBJECT *me_btree, MBAR_DO me_bshow dglob);
short G_decl G_n(menu_icheck)( OBJECT *me_ctree, short me_citem, short me_ccheck dglob);
short G_decl G_n(menu_ienable)( OBJECT *me_etree, short me_eitem, short me_eenable dglob);
short G_decl G_n(menu_tnormal)( OBJECT *me_ntree, short me_ntitle, short me_nnormal dglob);
short G_decl G_n(menu_text)( OBJECT *me_ttree, short me_titem, const char *me_ttext dglob);
short G_decl G_n(menu_register)( short me_rapid, const char *me_rpstring dglob);
short G_decl G_n(menu_popup)( MENU *me_menu, short me_xpos, short me_ypos, MENU *me_mdata dglob);
short G_decl G_n(form_popup)( OBJECT *tree, short x, short y dglob);
short G_decl form_menu(char *title, char **mt);
short G_decl form_input(char *title, FORM_INPUT *r);
#if G_EXT
short G_decl G_n(menu_click)(short val, short setflag dglob);
short G_decl G_n(menu_attach)( short me_flag, OBJECT *me_tree, short me_item, MENU *me_mdata dglob);
short G_decl G_n(menu_istart)( short me_flag, OBJECT *me_tree, short me_imenu, short me_item dglob);
short G_decl G_n(menu_settings)( short me_flag, MN_SET *me_values dglob);
#endif

/* Object prototypes */

short G_decl G_n(objc_add)( OBJECT *ob_atree, short ob_aparent, short ob_achild dglob);
short G_decl G_n(objc_delete)( OBJECT *ob_dltree, short ob_dlobject dglob);
short G_decl G_n(objc_draw)( OBJECT *ob_drtree, short ob_drstartob,
               short ob_drdepth, short ob_drxclip, short ob_dryclip,
               short ob_drwclip, short ob_drhclip dglob);
short G_decl G_n(objc_find)( OBJECT *ob_ftree, short ob_fstartob, short ob_fdepth,
               short ob_fmx, short ob_fmy dglob);
short G_decl G_n(objc_offset)( OBJECT *ob_oftree, short ob_ofobject,
                 short *ob_ofxoff, short *ob_ofyoff dglob);
short G_decl G_n(objc_order)( OBJECT *ob_ortree, short ob_orobject,
                short ob_ornewpos dglob);
short G_decl G_n(objc_edit)( OBJECT *ob_edtree, short ob_edobject,
               short ob_edchar, short *ob_edidx, short ob_edkind dglob);
#if G_EXT
short G_decl G_n(objc_xedit)(void *tree,short item,short edchar,short *idx,short kind,
			GRECT *r dglob);
#endif
#if !G_MODIFIED
short G_decl G_n(objc_change)( OBJECT *ob_ctree, short ob_cobject,
				short ob_cresvd, short ob_cxclip, short ob_cyclip,
				short ob_cwclip, short ob_chclip,
				short ob_cnewstate, short ob_credraw dglob);
#else
short G_decl G_n(objc_change)(void *tree,
				short item,short resvd,GRECT *r,short newst,short redraw dglob);
#endif
short G_decl G_n(objc_sysvar)
			   (short mo, short which, short ival1,
				short ival2, short *oval1, short *oval2 dglob);


/****** Form definitions ************************************************/

typedef enum
{
	FMD_START,
	FMD_GROW,
	FMD_SHRINK,
	FMD_FINISH
} FMD_TY;

typedef struct	/* form_xdo definitions */
{
	char	scancode;
	char	nclicks;
	short	objnr;
} SCANX;

typedef struct
{
	SCANX *	unsh;
	SCANX *	shift;
	SCANX *	ctrl;
 	SCANX *	alt;
	void *	resvd;
} XDO_INF;

typedef struct _xted /* scrollable textedit objects */
{
	char *	tmplt;
	char *	valid;
	short	vislen;
	short	scroll;
} XTED;

short G_decl G_n(form_do)( OBJECT *fo_dotree, short fo_dostartob dglob);
#if G_EXT
short G_decl G_n(form_xdo)(OBJECT *tree, short item, short *curob, XDO_INF *scantab, void *flyinf dglob);
short	G_decl G_n(form_xdial)(short subfn, GRECT *lg, GRECT *bg, void **flyinf dglob);
#endif
#if !G_MODIFIED
short G_decl G_n(form_dial)(short flag,short lx,short ly,short lw,short lh,
                                   short tx,short ty,short tw,short th dglob);
#else
short	G_decl G_n(form_dial)(short subfn, GRECT *lg, GRECT *bg dglob);
#endif
#if G_EXT
short	G_decl G_n(form_xdial)(short subfn, GRECT *lg,
				GRECT *bg, void **flyinf dglob);
#endif
short G_decl G_n(form_alert)( short fo_adefbttn, const char *fo_astring dglob);
short G_decl G_n(form_error)( short fo_enum dglob);
short G_decl G_n(form_center)( OBJECT *fo_ctree, short *fo_cx, short *fo_cy,
                 short *fo_cw, short *fo_ch dglob);
short G_decl G_n(form_keybd)( OBJECT *fo_ktree, short fo_kobject, short fo_kobnext,
                short fo_kchar, short *fo_knxtobject, short *fo_knxtchar dglob);
short G_decl G_n(form_button)( OBJECT *fo_btree, short fo_bobject, short fo_bclicks,
                short *fo_bnxtobj dglob);

/****** Graph definitions ************************************************/


/* Mouse forms */

typedef enum
{
	ARROW,
	TEXT_CRSR,
	BUSYBEE,
	BEE = BUSYBEE,
	HOURGLASS= BUSYBEE,
	POINT_HAND,
	FLAT_HAND,
	THIN_CROSS,
	THICK_CROSS,
	OUTLN_CROSS,
	USER_DEF	= 255,
	M_OFF,
	M_ON,
	M_SAVE,
	M_LAST,
	M_RESTORE
} MOUSE_TY;

/* Mouse form definition block */
typedef struct mfstr
{
	short
		xhot,
		yhot,
		nplanes,
		fg,
		bg,
		mask[16],
		data[16];
} MFORM;

short G_decl G_n(graf_rubberbox)( short gr_rx, short gr_ry, short gr_minwidth,
                    short gr_minheight, short *gr_rlastwidth,
                    short *gr_rlastheight dglob);
short G_decl G_n(graf_rubbox)( short gr_rx, short gr_ry, short gr_minwidth,
                    short gr_minheight, short *gr_rlastwidth,
                    short *gr_rlastheight dglob);
#if !G_MODIFIED
short G_decl G_n(graf_dragbox)( short gr_dwidth, short gr_dheight,
                  short gr_dstartx, short gr_dstarty,
                  short gr_dboundx, short gr_dboundy,
                  short gr_dboundw, short gr_dboundh,
                  short *gr_dfinishx, short *gr_dfinishy dglob);
#else
short G_decl G_n(graf_dragbox)(short dw,short dh,short dx,short dy,
                 GRECT *g,
                 short *ex,short *ey dglob);
#endif
short G_decl G_n(graf_movebox)( short gr_mwidth, short gr_mheight,
                  short gr_msourcex, short gr_msourcey,
                  short gr_mdestx, short gr_mdesty dglob);
short G_decl G_n(graf_mbox)( short gr_mwidth, short gr_mheight,
                  short gr_msourcex, short gr_msourcey,
                  short gr_mdestx, short gr_mdesty dglob);
#if !G_MODIFIED
short G_decl G_n(graf_growbox)( short gr_gstx, short gr_gsty,
                  short gr_gstwidth, short gr_gstheight,
                  short gr_gfinx, short gr_gfiny,
                  short gr_gfinwidth, short gr_gfinheight dglob);
short G_decl G_n(graf_shrinkbox)( short gr_sfinx, short gr_sfiny,
                    short gr_sfinwidth, short gr_sfinheight,
                    short gr_sstx, short gr_ssty,
                    short gr_sstwidth, short gr_sstheight dglob);
#else
short G_decl G_n(graf_growbox)(GRECT *sr, GRECT *er dglob);
short G_decl G_n(graf_shrinkbox)(GRECT *sr, GRECT *er dglob);
#endif
short G_decl G_n(graf_watchbox)( OBJECT *gr_wptree, short gr_wobject,
                   short gr_winstate, short gr_woutstate dglob);
short G_decl G_n(graf_slidebox)( OBJECT *gr_slptree, short gr_slparent,
                   short gr_slobject, short gr_slvh dglob);
short G_decl G_n(graf_handle)( short *gr_hwchar, short *gr_hhchar,
                 short *gr_hwbox, short *gr_hhbox dglob);
#if G_EXT
short G_decl G_n(graf_xhandle)(short *wchar,short *hchar,short *wbox,short *hbox,short *device dglob);
#endif
short G_decl G_n(graf_mouse)( short gr_monumber, MFORM *gr_mofaddr dglob);
#if !G_MODIFIED
short G_decl G_n(graf_mkstate)( short *gr_mkmx, short *gr_mkmy,
                  short *gr_mkmstate, short *gr_mkkstate dglob);
#else
short G_decl G_n(graf_mkstate)(EVNTDATA *ev dglob);
#endif

/****** Scrap definitions ***********************************************/

short G_decl scrp_read( char *sc_rpscrap );
short G_decl scrp_write( char *sc_wpscrap );


/****** File selector definitions ***************************************/

short G_decl G_n(fsel_input)( char *fs_iinpath, char *fs_iinsel,
                short *fs_iexbutton dglob);
short G_decl G_n(fsel_exinput)( char *fs_einpath, char *fs_einsel,
                short *fs_eexbutton, char *fs_elabel dglob);


/****** Window definitions **********************************************/

typedef enum
{
	NAME	=0x0001,
	CLOSER	=0x0002,
	FULLER	=0x0004,
	MOVER	=0x0008,
	INFO	=0x0010,
	SIZER	=0x0020,
	UPARROW	=0x0040,
	DNARROW	=0x0080,
	VSLIDE	=0x0100,
	LFARROW	=0x0200,
	RTARROW	=0x0400,
	HSLIDE	=0x0800,
	MENUBAR	=0x1000,		/* XaAES     */
	BACKDROP =0x2000,		/* KAOS 1.4    */
	ICONIFIER=0x4000,		/* AES 4.1     */
	SMALLER  =ICONIFIER,
} WIND_ATTR;

typedef enum
{
	WF_KIND=1,
	WF_NAME,
	WF_INFO,
	WF_WORKXYWH,
	WF_CURRXYWH,
	WF_PREVXYWH,
	WF_FULLXYWH,
	WF_HSLIDE,
	WF_VSLIDE,
	WF_TOP,
	WF_FIRSTXYWH,
	WF_NEXTXYWH,
	WF_RESVD,
	WF_NEWDESK,
	WF_HSLSIZE,
	WF_VSLSIZE,
	WF_SCREEN,
	WF_COLOR,
	WF_DCOLOR,
	WF_OWNER,				/* AES 4       */
	WF_BEVENT = 24,
	WF_BOTTOM,
	WF_ICONIFY,				/* AES 4.1     */
	WF_UNICONIFY,			/* AES 4.1     */
	WF_UNICONIFYXYWH,		/* AES 4.1     */
	WF_TOOLBAR = 30,		/* compatible  */
	WF_FTOOLBAR,
	WF_NTOOLBAR,
	WF_MENU,
	WF_WIDGET,
	WF_WHEEL       = 40,
	WF_M_BACKDROP  = 100,	/* KAOS 1.4    */
	WF_M_OWNER,				/* KAOS 1.4    */
	WF_M_WINDLIST,			/* KAOS 1.4    */
	WF_SHADE       =0x575d,	/* WINX 2.3	*/
	WF_STACK	   =0x575e,	/* WINX 2.3	*/
	WF_TOPALL	   =0x575f,	/* WINX 2.3	*/
	WF_BOTTOMALL   =0x5760	/* WINX 2.3	*/
} WIND_CODE;

typedef enum
{
	W_BOX ,
	W_TITLE,
	W_CLOSER,
	W_NAME,
	W_FULLER,
	W_INFO,
	W_DATA,
	W_WORK,
	W_SIZER,
	W_VBAR,
	W_UPARROW,
	W_DNARROW,
	W_VSLIDE,
	W_VELEV,
	W_HBAR,
	W_LFARROW,
	W_RTARROW,
	W_HSLIDE,
	W_HELEV,
	W_SMALLER,		/* AES 4.1     */
	W_BOTTOMER		/* MagiC 3     */
} WIND_COMP;

/* wind_set(WF_BEVENT) */

typedef enum
{
	BEVENT_WORK=1,		/* AES 4.0	*/
	BEVENT_INFO,		/* MagiC 6	*/
} BEVENT;

typedef enum
{
	WA_UPPAGE,
	WA_DNPAGE,
	WA_UPLINE,
	WA_DNLINE,
	WA_LFPAGE,
	WA_RTPAGE,
	WA_LFLINE,
	WA_RTLINE,
	WA_WHEEL
} WIND_ARROW;

typedef enum
{
	WC_BORDER,						/* wind calc flags */
	WC_WORK
} WIND_CALC_C;

typedef enum
{
	END_UPDATE,						/* update flags */
	BEG_UPDATE,
	END_MCTRL,
	BEG_MCTRL
} WIND_UPD_FL;

#if !G_MODIFIED
short G_decl G_n(wind_create)( short wi_crkind, short wi_crwx, short wi_crwy,
                 short wi_crww, short wi_crwh dglob);
short G_decl G_n(wind_open)( short wi_ohandle, short wi_owx, short wi_owy,
               short wi_oww, short wi_owh dglob);
short G_decl G_n(wind_calc)( short wi_ctype, short wi_ckind, short wi_cinx,
               short wi_ciny, short wi_cinw, short wi_cinh,
               short *coutx, short *couty, short *coutw,
               short *couth dglob);
#else
short G_decl G_n(wind_create)(short kind, GRECT *r dglob);
short G_decl G_n(wind_open  )(short whl,  GRECT *r dglob);
short G_decl G_n(wind_calc)(short ty,short srt, GRECT *ri, GRECT *ro dglob);
#endif
short G_decl G_n(wind_close)( short wi_clhandle dglob);
short G_decl G_n(wind_delete)( short wi_dhandle dglob);
#if __WGS_ELLIPSISD__
short wind_get( short wi_ghandle, short wi_gfield, ... );
short wind_set( short wi_shandle, short wi_sfield, ... );
#else
short G_decl G_n(wind_get)( short wi_ghandle, short wi_gfield, short, short, short, short dglob);
short G_decl G_n(wind_set)( short wi_shandle, short wi_sfield, short *, short *, short *, short * dglob);
#endif
#if G_EXT
short G_decl G_n(wind_get_grect) (short whl, short srt, GRECT *g dglob);
short G_decl G_n(wind_get_int)   (short whl, short srt, short *g1 dglob);
short G_decl G_n(wind_get_ptr)   (short whl, short srt, void **v dglob);
short G_decl G_n(wind_set_string)(short whl, short srt, char *s dglob);
short G_decl G_n(wind_set_grect) (short whl, short srt, GRECT *r dglob);
short G_decl G_n(wind_set_int)   (short whl, short srt, short i dglob);
short G_decl G_n(wind_set_ptr_int)(short whl,short srt, void *s, short g dglob);
#endif
short G_decl G_n(wind_find)( short wi_fmx, short wi_fmy dglob);
short G_decl G_n(wind_update)( short wi_ubegend dglob);
void G_decl G_nv(wind_new);

short G_decl G_n(wind_get_nargs)(short field);

/****** Resource definitions ********************************************/

typedef enum					/* data structure types */
{
	R_TREE,
	R_OBJECT,
	R_TEDINFO,
	R_ICONBLK,
	R_BITBLK,
	R_STRING,					/* gets pointer to free strings */
	R_IMAGEDATA,				/* gets pointer to free images */
	R_OBSPEC,
	R_TEPTEXT,					/* sub ptrs in TEDINFO */
	R_TEPTMPLT,
	R_TEPVALID,
	R_IBPMASK,					/* sub ptrs in ICONBLK */
	R_IBPDATA,
	R_IPBTEXT,
	R_BIPDATA,					/* sub ptrs in BITBLK */
	R_FRSTR,					/* gets addr of ptr to free strings */
	R_FRIMG,					/* gets addr of ptr to free images  */
} RSH_THING;

typedef struct rshdr
{
	short	vrsn;		/* RCS version no. */
	unsigned
	short	object,		/* Offset to object[] */
			tedinfo,	/* Offset to tedinfo[] */
			iconblk,	/* Offset to iconblk[] */
			bitblk,		/* Offset to bitblk[] */
			frstr,		/* Offset to free string index */
			string,		/* HR: unused (Offset to first string) */
			imdata,		/* Offset to image data */
			frimg,		/* Offset to free image index */
			trindex;	/* Offset to object tree index */
	short	nobs,		/* Number of objects */
			ntree,		/* Number of trees */
			nted,		/* Number of tedinfos */
			nib,		/* Number of icon blocks */
			nbb,		/* Number of blt blocks */
			nstring,	/* Number of free strings */
			nimages;	/* Number of free images */
	unsigned
	short	rssize;	/* Total bytes in resource */
} RSHDR;

short G_decl G_n(rsrc_load)( const char *re_lpfname dglob);
short G_decl G_nv(rsrc_free);
short G_decl G_n(rsrc_gaddr)( short re_gtype, short re_gindex, void *gaddr dglob);
short G_decl G_n(rsrc_saddr)( short re_stype, short re_sindex, void *saddr dglob);
short G_decl G_n(rsrc_obfix)( OBJECT *re_otree, short re_oobject dglob);
short G_decl G_n(rsrc_rcfix)( RSHDR *rc_header dglob);


/****** Shell definitions ***********************************************/

/* tail for default shell */

typedef struct
{
	short	dummy;                   /* ein Nullwort               */
	long	magic;                   /* 'SHEL', wenn ist Shell     */
	short	isfirst;                 /* erster Aufruf der Shell    */
	long	lasterr;                 /* letzter Fehler             */
	short	wasgr;                   /* Programm war Grafikapp.    */
} SHELTAIL;

/* shel_write modes for parameter "isover" */

typedef enum
{
	SHW_IMMED,			/* PC-GEM 2.x  */
	SHW_CHAIN,			/* TOS         */
	SHW_DOS,			/* PC-GEM 2.x  */
	SHW_PARALLEL=100,	/* MAG!X       */
	SHW_SINGLE			/* MAG!X       */
} SHW_ISOVER;

/* shel_write modes for parameter "doex" */

typedef enum
{
	SHW_NOEXEC,
	SHW_EXEC,
	SHW_EXEC_ACC =3,		/* AES 3.3	*/
	SHW_SHUTDOWN,			/* AES 3.3     */
	SHW_RESCHNG,			/* AES 3.3     */
	SHW_BROADCAST=7,		/* AES 4.0     */
	SHW_INFRECGN =9,		/* AES 4.0     */
	SHW_AESSEND,			/* AES 4.0     */
	SHW_THR_CREATE=20		/* MagiC 4.5	*/
} SHW_DOEX;

/* extended shel_write() modes and parameter structure */

typedef enum
{
	SHW_XMDLIMIT = 256,
	SHW_XMDNICE  = 512,
	SHW_XMDDEFDIR=1024,
	SHW_XMDENV   =2048,
	SHW_XMDFLAGS =4096
} SHW_XMD;

typedef struct {
	char *command;
	long limit;
	long nice;
	char *defdir;
	char *env;
	long flags;		/* ab MagiC 6 */
} XSHW_COMMAND;

#if !((defined  __STDC__) && CDECL)
/*	   using this structure is not possible
 *      if ANSI keywords only is ON, and __Cdecl is non empty
 */
typedef struct {
	long __Cdecl (*procedure)(void *par);
	void *	user_stack;
	unsigned
	long	stacksize;
	short	mo;			/* immer auf 0 setzen! */
	long	res1;		/* immer auf 0L setzen! */
} THREADINFO;
#endif

short G_decl G_n(shel_read)( char *sh_rpcmd, char *sh_rptail dglob);
short G_decl G_n(shel_write)( short sh_wdoex, short sh_wisgr, short sh_wiscr,
							char *sh_wpcmd, char *sh_wptail dglob);
short G_decl G_n(shel_get)( char *sh_gaddr, unsigned short sh_glen dglob);
short G_decl G_n(shel_put)( char *sh_paddr, unsigned short sh_plen dglob);
short G_decl G_n(shel_find)( char *sh_fpbuff dglob);
short G_decl G_n(shel_envrn)( char **sh_epvalue, char *sh_eparm dglob);
#if G_EXT
short G_decl G_n(shel_rdef)( char *fname, char *dir dglob);
short G_decl G_n(shel_wdef)( char *fname, char *dir dglob);

#include <aes_xtnd.h>
#endif

extern short MagX_version,radio_bgcol;
extern bool MagX,MiNT;
extern MAGX_COOKIE *magic;

void	adapt3d_rsrc	( OBJECT *objs, short no_objs, short hor_3d, short ver_3d );
void	   no3d_rsrc	( OBJECT *objs, short no_objs, short ftext_to_fboxtext );
char *	is_userdef_title( OBJECT *obj );
short	get_aes_info	( short version, short *font_id, short *font_height, short *hor_3d, short *ver_3d );
void	substitute_objects( OBJECT *objs, short no_objs, short aes_flags, OBJECT *rslct, OBJECT *rdeslct );
void	substitute_free	(void);
#endif

