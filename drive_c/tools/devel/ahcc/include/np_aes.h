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
	12-04-99  Multi Threading AES and further modernization.
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
	void (*chgres)( int res, int txt );	/* Auflîsung Ñndern */
	long	(**shel_vector)(void);			/* ROM-Desktop */
	char *	aes_bootdrv;					/* Hierhin kommt DESKTOP.INF */
	int *	vdi_device;					/* vom AES benutzter Treiber */
	void *	reservd1;
	void *	reservd2;
	void *	reservd3;

	int version,						/* Versionsnummer */
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
	int	dst_apid;
	int	unique_flg;
	void *	attached_mem;
	int *	msgbuf;
} XAESMSG;

int G_decl G_nv(appl_init);
int G_decl G_n(appl_read)		( int ap_rid, int ap_rlength, void *ap_rpbuff dglob);
int G_decl G_n(appl_write)	( int ap_wid, int ap_wlength, void *ap_wpbuff dglob);
int G_decl G_n(appl_find)		( const char *ap_fpname  dglob);
int G_decl G_n(appl_tplay)	( void *ap_tpmem, int ap_tpnum, int ap_tpscale  dglob);
int G_decl G_n(appl_trecord)	( void *ap_trmem, int ap_trcount  dglob);
int G_decl G_nv(appl_exit);
int G_decl G_n(appl_search)	( int ap_smode, char *ap_sname, int *ap_stype,
								  int *ap_sid  dglob);
int G_decl G_n(appl_getinfo)	( int ap_gtype, int *ap_gout1, int *ap_gout2,
								  int *ap_gout3, int *ap_gout4  dglob);
int G_decl G_n(appl_control)	( int ap_id, int what, void *out);

#define appl_bvset ( disks, harddisks ) /* Funktion ignorieren (GEM fÅr Dose): void appl_bvset( int disks, int harddisks ); */

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
	int x,y,w,h;
} GRECT, RECT;

#if !G_MODIFIED
int G_decl G_nv(evnt_keybd);
int G_decl G_n(evnt_button)( int ev_bclicks, int ev_bmask, int ev_bstate,
				int *ev_bmx, int *ev_bmy, int *ev_bbutton,
				int *ev_bkstate dglob);
int G_decl G_n(evnt_mouse)( int ev_moflags, int ev_mox, int ev_moy,
				int ev_mowidth, int ev_moheight, int *ev_momx,
				int *ev_momy, int *ev_mobutton,
				int *ev_mokstate dglob);
int G_decl G_n(evnt_mesag)( int *ev_mgpbuff dglob );
int G_decl G_n(evnt_timer)( int ev_tlocount, int ev_thicount dglob );
int G_decl G_n(evnt_multi)( int ev_mflags, int ev_mbclicks, int ev_mbmask,
				int ev_mbstate, int ev_mm1flags, int ev_mm1x,
				int ev_mm1y, int ev_mm1width, int ev_mm1height,
				int ev_mm2flags, int ev_mm2x, int ev_mm2y,
				int ev_mm2width, int ev_mm2height,
				int *ev_mmgpbuff, int ev_mtlocount,
				int ev_mthicount, int *ev_mmox, int *ev_mmoy,
				int *ev_mmbutton, int *ev_mmokstate,
				int *ev_mkreturn, int *ev_mbreturn dglob );
int G_decl G_n(evnt_dclick)( int ev_dnew, int ev_dgetset dglob );
#else
int G_decl G_nv(evnt_keybd);
int G_decl G_n(evnt_button)(int clks,int mask,int state,
				EVNTDATA *ev dglob);
int G_decl G_n(evnt_mouse)(int flags, GRECT *g, EVNTDATA *ev dglob);
int G_decl G_n(evnt_mesag)(int *ev_mgpbuff dglob );
int G_decl G_n(evnt_timer)(unsigned long ms dglob);
int G_decl G_n(evnt_multi)(int flags,int clks,int mask,int state,
				int m1flags,GRECT *g1,
				int m2flags,GRECT *g2,
				int *msgpipe,
				unsigned long ms,
				EVNTDATA *ev,
				int *toets,int *oclks dglob);
int G_decl G_n(evnt_dclicks)(int new,int getset dglob);
#endif
#if G_EXT
void G_n(EVNT_multi)( int evtypes, int nclicks, int bmask, int bstate,
				MOBLK *m1, MOBLK *m2, G_ul ms,
				EVNT *event dglob );
#endif

/* this is our special invention to increase evnt_multi performance */

typedef struct /* Special type for EventMulti */
{
	/* input parameters */
	int flags, bclicks, bmask, bstate,
	      m1flags, m1x, m1y, m1width, m1height,
	      m2flags, m2x, m2y, m2width, m2height,
	      tlocount, thicount;
	/* output parameters */
	int wich,
	      mox, moy,
	      mobutton, mokstate,
	      kreturn, breturn;
	/* message buffer */
	int mgpbuf[8];
} EVENT;

int G_decl G_n(EvntMulti)( EVENT *evnt_struct dglob);


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
	int x,y,w,h;
} ORECT;

typedef struct
{
	int x,y,
	      jx,jy;		/* VDI rectangle */
} VRECT;

/* Object structures */

typedef struct
{
	char *	text,		/* ptr to text (must be 1st)	*/
		 *	tmplt,		/* ptr to template				*/
		 *	valid;		/* ptr to validation			*/
	int	font,		/* font							*/
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
	int *	mask,
		  *	data;
	char *	text;
	int	ch,
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
	int	num_planes;
	int *	col_data;
	int *	col_mask;
	int *	sel_data;
	int *	sel_mask;
	struct cicon_data *	next_res;
} CICON;


typedef struct cicon_blk
{
	ICONBLK	monoblk;
	CICON *	mainlist;
} CICONBLK;

typedef struct
{
	int *	data,		/* ptr to bit forms data	*/
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
	int __Cdecl	(*ub_code)(struct __parmblk *parmblock);
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
	int	next,		/* -> object's next sibling     */
			head,		/* -> head of object's children */
			tail;		/* -> tail of object's children */
	unsigned
	int	type,			/* object type: BOX, CHAR,...   */
			flags,		/* object flags                 */
			state;		/* state: SELECTED, OPEN, ...   */
	OBSPEC	spec;		/* "out": -> anything else      */
/* The following is in fact a GRECT, but is too offten used to change it */
	int	x,			/* upper left corner of object  */
			y,			/* upper left corner of object  */
			w,			/* object width                 */
			h;			/* object height                */
} OBJECT;

typedef struct __parmblk
{
	OBJECT  *tree;
	int	obj,
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
	int		menu;
	int		item;
	int		scroll;
	int		keystate;
} MENU;

typedef struct
{
	long	Display;
	long	Drag;
	long	Delay;
	long	Speed;
	int	Height;
} MN_SET;

typedef struct
{
	char *	string;			/* etwa "TOS|KAOS|MAG!X"			*/
	int	num,			/* Nr. der aktuellen Zeichenkette	*/
			maxnum;			/* maximal erlaubtes <num>			*/
} SWINFO;

typedef struct
{
     OBJECT *	tree;		/* Popup- MenÅ					*/
     int		obnum;		/* aktuelles Objekt von <tree>	*/
} POPINFO;

#define FORM_MAX 15

typedef struct
{
	int	ty,		/* type: 's', 'r', 'd' or 'l' */
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

int G_decl G_n(menu_bar)( OBJECT *me_btree, MBAR_DO me_bshow dglob);
int G_decl G_n(menu_icheck)( OBJECT *me_ctree, int me_citem, int me_ccheck dglob);
int G_decl G_n(menu_ienable)( OBJECT *me_etree, int me_eitem, int me_eenable dglob);
int G_decl G_n(menu_tnormal)( OBJECT *me_ntree, int me_ntitle, int me_nnormal dglob);
int G_decl G_n(menu_text)( OBJECT *me_ttree, int me_titem, const char *me_ttext dglob);
int G_decl G_n(menu_register)( int me_rapid, const char *me_rpstring dglob);
int G_decl G_n(menu_popup)( MENU *me_menu, int me_xpos, int me_ypos, MENU *me_mdata dglob);
int G_decl G_n(form_popup)( OBJECT *tree, int x, int y dglob);
int G_decl form_menu(char *title, char **mt);
int G_decl form_input(char *title, FORM_INPUT *r);
#if G_EXT
int G_decl G_n(menu_click)(int val, int setflag dglob);
int G_decl G_n(menu_attach)( int me_flag, OBJECT *me_tree, int me_item, MENU *me_mdata dglob);
int G_decl G_n(menu_istart)( int me_flag, OBJECT *me_tree, int me_imenu, int me_item dglob);
int G_decl G_n(menu_settings)( int me_flag, MN_SET *me_values dglob);
#endif

/* Object prototypes */

int G_decl G_n(objc_add)( OBJECT *ob_atree, int ob_aparent, int ob_achild dglob);
int G_decl G_n(objc_delete)( OBJECT *ob_dltree, int ob_dlobject dglob);
int G_decl G_n(objc_draw)( OBJECT *ob_drtree, int ob_drstartob,
               int ob_drdepth, int ob_drxclip, int ob_dryclip,
               int ob_drwclip, int ob_drhclip dglob);
int G_decl G_n(objc_find)( OBJECT *ob_ftree, int ob_fstartob, int ob_fdepth,
               int ob_fmx, int ob_fmy dglob);
int G_decl G_n(objc_offset)( OBJECT *ob_oftree, int ob_ofobject,
                 int *ob_ofxoff, int *ob_ofyoff dglob);
int G_decl G_n(objc_order)( OBJECT *ob_ortree, int ob_orobject,
                int ob_ornewpos dglob);
int G_decl G_n(objc_edit)( OBJECT *ob_edtree, int ob_edobject,
               int ob_edchar, int *ob_edidx, int ob_edkind dglob);
#if G_EXT
int G_decl G_n(objc_xedit)(void *tree,int item,int edchar,int *idx,int kind,
			GRECT *r dglob);
#endif
#if !G_MODIFIED
int G_decl G_n(objc_change)( OBJECT *ob_ctree, int ob_cobject,
				int ob_cresvd, int ob_cxclip, int ob_cyclip,
				int ob_cwclip, int ob_chclip,
				int ob_cnewstate, int ob_credraw dglob);
#else
int G_decl G_n(objc_change)(void *tree,
				int item,int resvd,GRECT *r,int newst,int redraw dglob);
#endif
int G_decl G_n(objc_sysvar)
			   (int mo, int which, int ival1,
				int ival2, int *oval1, int *oval2 dglob);


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
	int	objnr;
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
	int	vislen;
	int	scroll;
} XTED;

int G_decl G_n(form_do)( OBJECT *fo_dotree, int fo_dostartob dglob);
#if G_EXT
int G_decl G_n(form_xdo)(OBJECT *tree, int item, int *curob, XDO_INF *scantab, void *flyinf dglob);
int	G_decl G_n(form_xdial)(int subfn, GRECT *lg, GRECT *bg, void **flyinf dglob);
#endif
#if !G_MODIFIED
int G_decl G_n(form_dial)(int flag,int lx,int ly,int lw,int lh,
                                   int tx,int ty,int tw,int th dglob);
#else
int	G_decl G_n(form_dial)(int subfn, GRECT *lg, GRECT *bg dglob);
#endif
#if G_EXT
int	G_decl G_n(form_xdial)(int subfn, GRECT *lg,
				GRECT *bg, void **flyinf dglob);
#endif
int G_decl G_n(form_alert)( int fo_adefbttn, const char *fo_astring dglob);
int G_decl G_n(form_error)( int fo_enum dglob);
int G_decl G_n(form_center)( OBJECT *fo_ctree, int *fo_cx, int *fo_cy,
                 int *fo_cw, int *fo_ch dglob);
int G_decl G_n(form_keybd)( OBJECT *fo_ktree, int fo_kobject, int fo_kobnext,
                int fo_kchar, int *fo_knxtobject, int *fo_knxtchar dglob);
int G_decl G_n(form_button)( OBJECT *fo_btree, int fo_bobject, int fo_bclicks,
                int *fo_bnxtobj dglob);

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
	int
		xhot,
		yhot,
		nplanes,
		fg,
		bg,
		mask[16],
		data[16];
} MFORM;

int G_decl G_n(graf_rubberbox)( int gr_rx, int gr_ry, int gr_minwidth,
                    int gr_minheight, int *gr_rlastwidth,
                    int *gr_rlastheight dglob);
int G_decl G_n(graf_rubbox)( int gr_rx, int gr_ry, int gr_minwidth,
                    int gr_minheight, int *gr_rlastwidth,
                    int *gr_rlastheight dglob);
#if !G_MODIFIED
int G_decl G_n(graf_dragbox)( int gr_dwidth, int gr_dheight,
                  int gr_dstartx, int gr_dstarty,
                  int gr_dboundx, int gr_dboundy,
                  int gr_dboundw, int gr_dboundh,
                  int *gr_dfinishx, int *gr_dfinishy dglob);
#else
int G_decl G_n(graf_dragbox)(int dw,int dh,int dx,int dy,
                 GRECT *g,
                 int *ex,int *ey dglob);
#endif
int G_decl G_n(graf_movebox)( int gr_mwidth, int gr_mheight,
                  int gr_msourcex, int gr_msourcey,
                  int gr_mdestx, int gr_mdesty dglob);
int G_decl G_n(graf_mbox)( int gr_mwidth, int gr_mheight,
                  int gr_msourcex, int gr_msourcey,
                  int gr_mdestx, int gr_mdesty dglob);
#if !G_MODIFIED
int G_decl G_n(graf_growbox)( int gr_gstx, int gr_gsty,
                  int gr_gstwidth, int gr_gstheight,
                  int gr_gfinx, int gr_gfiny,
                  int gr_gfinwidth, int gr_gfinheight dglob);
int G_decl G_n(graf_shrinkbox)( int gr_sfinx, int gr_sfiny,
                    int gr_sfinwidth, int gr_sfinheight,
                    int gr_sstx, int gr_ssty,
                    int gr_sstwidth, int gr_sstheight dglob);
#else
int G_decl G_n(graf_growbox)(GRECT *sr, GRECT *er dglob);
int G_decl G_n(graf_shrinkbox)(GRECT *sr, GRECT *er dglob);
#endif
int G_decl G_n(graf_watchbox)( OBJECT *gr_wptree, int gr_wobject,
                   int gr_winstate, int gr_woutstate dglob);
int G_decl G_n(graf_slidebox)( OBJECT *gr_slptree, int gr_slparent,
                   int gr_slobject, int gr_slvh dglob);
int G_decl G_n(graf_handle)( int *gr_hwchar, int *gr_hhchar,
                 int *gr_hwbox, int *gr_hhbox dglob);
#if G_EXT
int G_decl G_n(graf_xhandle)(int *wchar,int *hchar,int *wbox,int *hbox,int *device dglob);
#endif
int G_decl G_n(graf_mouse)( int gr_monumber, MFORM *gr_mofaddr dglob);
#if !G_MODIFIED
int G_decl G_n(graf_mkstate)( int *gr_mkmx, int *gr_mkmy,
                  int *gr_mkmstate, int *gr_mkkstate dglob);
#else
int G_decl G_n(graf_mkstate)(EVNTDATA *ev dglob);
#endif

/****** Scrap definitions ***********************************************/

int G_decl scrp_read( char *sc_rpscrap );
int G_decl scrp_write( char *sc_wpscrap );


/****** File selector definitions ***************************************/

int G_decl G_n(fsel_input)( char *fs_iinpath, char *fs_iinsel,
                int *fs_iexbutton dglob);
int G_decl G_n(fsel_exinput)( char *fs_einpath, char *fs_einsel,
                int *fs_eexbutton, char *fs_elabel dglob);


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
int G_decl G_n(wind_create)( int wi_crkind, int wi_crwx, int wi_crwy,
                 int wi_crww, int wi_crwh dglob);
int G_decl G_n(wind_open)( int wi_ohandle, int wi_owx, int wi_owy,
               int wi_oww, int wi_owh dglob);
int G_decl G_n(wind_calc)( int wi_ctype, int wi_ckind, int wi_cinx,
               int wi_ciny, int wi_cinw, int wi_cinh,
               int *coutx, int *couty, int *coutw,
               int *couth dglob);
#else
int G_decl G_n(wind_create)(int kind, GRECT *r dglob);
int G_decl G_n(wind_open  )(int whl,  GRECT *r dglob);
int G_decl G_n(wind_calc)(int ty,int srt, GRECT *ri, GRECT *ro dglob);
#endif
int G_decl G_n(wind_close)( int wi_clhandle dglob);
int G_decl G_n(wind_delete)( int wi_dhandle dglob);
#if __WGS_ELLIPSISD__
int wind_get( int wi_ghandle, int wi_gfield, ... );
int wind_set( int wi_shandle, int wi_sfield, ... );
#else
int G_decl G_n(wind_get)( int wi_ghandle, int wi_gfield, int, int, int, int dglob);
int G_decl G_n(wind_set)( int wi_shandle, int wi_sfield, int *, int *, int *, int * dglob);
#endif
#if G_EXT
int G_decl G_n(wind_get_grect) (int whl, int srt, GRECT *g dglob);
int G_decl G_n(wind_get_int)   (int whl, int srt, int *g1 dglob);
int G_decl G_n(wind_get_ptr)   (int whl, int srt, void **v dglob);
int G_decl G_n(wind_set_string)(int whl, int srt, char *s dglob);
int G_decl G_n(wind_set_grect) (int whl, int srt, GRECT *r dglob);
int G_decl G_n(wind_set_int)   (int whl, int srt, int i dglob);
int G_decl G_n(wind_set_ptr_int)(int whl,int srt, void *s, int g dglob);
#endif
int G_decl G_n(wind_find)( int wi_fmx, int wi_fmy dglob);
int G_decl G_n(wind_update)( int wi_ubegend dglob);
void G_decl G_nv(wind_new);

int G_decl G_n(wind_get_nargs)(int field);

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
	int	vrsn;		/* RCS version no. */
	unsigned
	int	object,		/* Offset to object[] */
			tedinfo,	/* Offset to tedinfo[] */
			iconblk,	/* Offset to iconblk[] */
			bitblk,		/* Offset to bitblk[] */
			frstr,		/* Offset to free string index */
			string,		/* HR: unused (Offset to first string) */
			imdata,		/* Offset to image data */
			frimg,		/* Offset to free image index */
			trindex;	/* Offset to object tree index */
	int	nobs,		/* Number of objects */
			ntree,		/* Number of trees */
			nted,		/* Number of tedinfos */
			nib,		/* Number of icon blocks */
			nbb,		/* Number of blt blocks */
			nstring,	/* Number of free strings */
			nimages;	/* Number of free images */
	unsigned
	int	rssize;	/* Total bytes in resource */
} RSHDR;

int G_decl G_n(rsrc_load)( const char *re_lpfname dglob);
int G_decl G_nv(rsrc_free);
int G_decl G_n(rsrc_gaddr)( int re_gtype, int re_gindex, void *gaddr dglob);
int G_decl G_n(rsrc_saddr)( int re_stype, int re_sindex, void *saddr dglob);
int G_decl G_n(rsrc_obfix)( OBJECT *re_otree, int re_oobject dglob);
int G_decl G_n(rsrc_rcfix)( RSHDR *rc_header dglob);


/****** Shell definitions ***********************************************/

/* tail for default shell */

typedef struct
{
	int	dummy;                   /* ein Nullwort               */
	long	magic;                   /* 'SHEL', wenn ist Shell     */
	int	isfirst;                 /* erster Aufruf der Shell    */
	long	lasterr;                 /* letzter Fehler             */
	int	wasgr;                   /* Programm war Grafikapp.    */
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
	int	mo;			/* immer auf 0 setzen! */
	long	res1;		/* immer auf 0L setzen! */
} THREADINFO;
#endif

int G_decl G_n(shel_read)( char *sh_rpcmd, char *sh_rptail dglob);
int G_decl G_n(shel_write)( int sh_wdoex, int sh_wisgr, int sh_wiscr,
							char *sh_wpcmd, char *sh_wptail dglob);
int G_decl G_n(shel_get)( char *sh_gaddr, unsigned int sh_glen dglob);
int G_decl G_n(shel_put)( char *sh_paddr, unsigned int sh_plen dglob);
int G_decl G_n(shel_find)( char *sh_fpbuff dglob);
int G_decl G_n(shel_envrn)( char **sh_epvalue, char *sh_eparm dglob);
#if G_EXT
int G_decl G_n(shel_rdef)( char *fname, char *dir dglob);
int G_decl G_n(shel_wdef)( char *fname, char *dir dglob);

#include <aes_xtnd.h>
#endif

extern int aes_handle,MagX_version,radio_bgcol;
extern bool MagX,MiNT;
extern MAGX_COOKIE *magic;

void	adapt3d_rsrc	( OBJECT *objs, int no_objs, int hor_3d, int ver_3d );
void	   no3d_rsrc	( OBJECT *objs, int no_objs, int ftext_to_fboxtext );
char *	is_userdef_title( OBJECT *obj );
int	get_aes_info	( int version, int *font_id, int *font_height, int *hor_3d, int *ver_3d );
void	substitute_objects( OBJECT *objs, int no_objs, int aes_flags, OBJECT *rslct, OBJECT *rdeslct );
void	substitute_free	(void);
#endif

