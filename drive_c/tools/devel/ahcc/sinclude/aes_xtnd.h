#ifndef __AES_XTND_H
#define __AES_XTND_H

#if ( WDLG_DIRECT_CALL == 0 )

/****** Wdialog definitions ***********************************************/

typedef	void	*DIALOG;

typedef	short	(__Cdecl *HNDL_OBJ)( DIALOG *dialog, EVNT *events, short obj, short clicks, void *data );

DIALOG *G_decl wdlg_create			( HNDL_OBJ handle_exit, OBJECT *tree, void *user_data, short code, void *data, short flags dglob );
short	G_decl wdlg_open			( DIALOG *dialog, char *title, short kind, short x, short y, short code, void *data dglob );
#if MT_OLDWAY
short	G_decl wdlg_close			( DIALOG *dialog dglob );
#else
short	G_decl wdlg_close			( DIALOG *dialog, short *x, short *y dglob );
#endif
short	G_decl wdlg_delete			( DIALOG *dialog dglob );

short	G_decl wdlg_get_tree		( DIALOG *dialog, OBJECT **tree, GRECT *r dglob );
short	G_decl wdlg_get_edit		( DIALOG *dialog, short *cursor dglob );
void *G_decl wdlg_get_udata			( DIALOG *dialog dglob );
short	G_decl wdlg_get_handle		( DIALOG *dialog dglob );

short	G_decl wdlg_set_edit		( DIALOG *dialog, short obj dglob );
short	G_decl wdlg_set_tree		( DIALOG *dialog, OBJECT *tree dglob );
short	G_decl wdlg_set_size		( DIALOG *dialog, GRECT *size dglob );
short	G_decl wdlg_set_iconify		( DIALOG *dialog, GRECT *g, char *title, OBJECT *tree, short obj dglob );
short	G_decl wdlg_set_uniconify	( DIALOG *dialog, GRECT *g, char *title, OBJECT *tree dglob );

short	G_decl wdlg_evnt			( DIALOG *dialog, EVNT *events dglob );
void G_decl wdlg_redraw				( DIALOG *dialog, GRECT *rect, short obj, short depth dglob );

/* Definitionen fÅr <flags> */
#define	WDLG_BKGD	1				/* Hintergrundbedienung zulassen */

/* Funktionsnummern fÅr <obj> bei handle_exit(...) */
#define	HNDL_INIT	-1				/* Dialog initialisieren */
#define	HNDL_MESG	-2				/* Dialog initialisieren */
#define	HNDL_CLSD	-3				/* Dialogfenster wurde geschlossen */
#define	HNDL_OPEN	-5				/* Dialog-Initialisierung abschlieûen (zweiter Aufruf am Ende von wdlg_init) */
#define	HNDL_EDIT	-6				/* Zeichen fÅr ein Edit-Feld ÅberprÅfen */
#define	HNDL_EDDN	-7				/* Zeichen wurde ins Edit-Feld eingetragen */
#define	HNDL_EDCH	-8				/* Edit-Feld wurde gewechselt */
#define	HNDL_MOVE	-9				/* Dialog wurde verschoben */
#define	HNDL_TOPW	-10				/* Dialog-Fenster ist nach oben gekommen */
#define	HNDL_UNTP	-11				/* Dialog-Fenster ist nicht aktiv */

/****** Listbox definitions ***********************************************/
typedef	void	*LIST_BOX;

typedef	void	(__Cdecl *SLCT_ITEM)( LIST_BOX *box, OBJECT *tree, struct _lbox_item *item, void *user_data, short obj_index, short last_state );
typedef	short	(__Cdecl *SET_ITEM)( LIST_BOX *box, OBJECT *tree, struct _lbox_item *item, short obj_index, void *user_data, GRECT *rect, short first );

typedef struct	_lbox_item
{
	struct _lbox_item *next;			/* Zeiger auf den nÑchsten Eintrag in der Liste */
	short	selected;					/* gibt an, ob das Objekt selektiert ist */

	short	data1;					/* Daten fÅr das Programm... */
	void	*data2;
	void	*data3;

} LBOX_ITEM;

#define	LBOX_VERT	1				/* Listbox mit vertikalem Slider */
#define	LBOX_AUTO	2				/* Auto-Scrolling */
#define	LBOX_AUTOSLCT	4			/* automatische Darstellung beim Auto-Scrolling */
#define	LBOX_REAL	8				/* Real-Time-Slider */
#define	LBOX_SNGL	16				/* nur ein anwÑhlbarer Eintrag */
#define	LBOX_SHFT	32				/* Mehrfachselektionen mit Shift */
#define	LBOX_TOGGLE	64			/* Status eines Eintrags bei Selektion wechseln */
#define	LBOX_2SLDRS	128			/* Listbox hat einen hor. und einen vertikalen Slider */

/* #defines fÅr Listboxen mit nur einem Slider */
#define	lbox_get_visible \
			lbox_get_avis

#define	lbox_get_first \
			lbox_get_afirst

#define	lbox_set_slider \
			lbox_set_asldr

#define	lbox_scroll_to \
			lbox_ascroll_to

LIST_BOX *G_decl (lbox_create)(
		OBJECT *tree, SLCT_ITEM slct, SET_ITEM set, LBOX_ITEM *items, short visible_a, short first_a,
		short *ctrl_objs, short *objs, short flags, short pause_a, void *user_data, void *dialog,
		short visible_b, short first_b, short entries_b, short pause_b dglob );

void	G_decl lbox_update			( LIST_BOX *box, GRECT *rect dglob );
short	G_decl lbox_do				( LIST_BOX *box, short obj dglob );
short	G_decl lbox_delete			( LIST_BOX *box dglob );

short	G_decl lbox_cnt_items		( LIST_BOX *box dglob );
OBJECT *G_decl lbox_get_tree		( LIST_BOX *box dglob );
short	G_decl lbox_get_avis		( LIST_BOX *box dglob );
void *	G_decl lbox_get_udata			( LIST_BOX *box dglob );
short	G_decl lbox_get_afirst		( LIST_BOX *box dglob );
short	G_decl lbox_get_slct_idx	( LIST_BOX *box dglob );
LBOX_ITEM *
		G_decl lbox_get_items		( LIST_BOX *box dglob );
LBOX_ITEM *
		G_decl lbox_get_item		( LIST_BOX *box, short n dglob );
LBOX_ITEM *
		G_decl lbox_get_slct_item	( LIST_BOX *box dglob );
short	G_decl lbox_get_idx			( LBOX_ITEM *items, LBOX_ITEM *search dglob );
short	G_decl lbox_get_bvis		( LIST_BOX *box dglob );
short	G_decl lbox_get_bentries	( LIST_BOX *box dglob );
short	G_decl lbox_get_bfirst		( LIST_BOX *box dglob );

void	G_decl lbox_set_asldr		( LIST_BOX *box, short first, GRECT *rect dglob );
void	G_decl lbox_set_items		( LIST_BOX *box, LBOX_ITEM *items dglob );
void	G_decl lbox_free_items		( LIST_BOX *box dglob );
void	G_decl lbox_free_list		( LBOX_ITEM *items dglob );
void	G_decl lbox_ascroll_to		( LIST_BOX *box, short first, GRECT *box_rect, GRECT *slider_rect dglob );
void	G_decl lbox_set_bsldr		( LIST_BOX *box, short first, GRECT *rect dglob );
void	G_decl lbox_set_bentries	( LIST_BOX *box, short entries dglob );
void	G_decl lbox_bscroll_to		( LIST_BOX *box, short first, GRECT *box_rect, GRECT *slider_rect dglob );
/****** font selector definitions ***********************************************/

typedef	void	*FNT_DIALOG;

typedef	void	(__Cdecl *UTXT_FN)( short x, short y, short *clip_rect, long id, long pt, long ratio, char *string );

typedef struct _fnts_item
{
	struct	_fnts_item	*next;	/* Zeiger auf den nÑchsten Font oder 0L (Ende der Liste) */
	UTXT_FN	display;				/* Zeiger auf die Anzeige-Funktion fÅr applikationseigene Fonts */
	long		id;					/* ID des Fonts, >= 65536 fÅr applikationseigene Fonts */
	short		index;				/* Index des Fonts (falls VDI-Font) */
	char		mono;				/* Flag fÅr Ñquidistante Fonts */
	char		outline;			/* Flag fÅr Vektorfont */
	short		npts;				/* Anzahl der vordefinierten Punkthîhen */
	char		*full_name;			/* Zeiger auf den vollstÑndigen Namen */
	char		*family_name;		/* Zeiger auf den Familiennamen */
	char		*style_name;		/* Zeiger auf den Stilnamen */
	char		*pts;				/* Zeiger auf Feld mit Punkthîhen */
	long		reserved[4];		/* reserviert, mÅssen 0 sein */
} FNTS_ITEM;

/* Definitionen fÅr <font_flags> bei fnts_create() */

#define FNTS_BTMP		1			/* Bitmapfonts anzeigen */
#define FNTS_OUTL		2			/* Vektorfonts anzeigen */
#define FNTS_MONO		4			/* Ñquidistante Fonts anzeigen */
#define FNTS_PROP		8			/* proportionale Fonts anzeigen */

/* Definitionen fÅr <dialog_flags> bei fnts_create() */
#define FNTS_3D		1				/* 3D-Design benutzen */

/* Definitionen fÅr <button_flags> bei fnts_open() */
#define FNTS_SNAME		0x01		/* Checkbox fÅr die Namen selektieren */
#define FNTS_SSTYLE		0x02		/* Checkbox fÅr die Stile selektieren */
#define FNTS_SSIZE		0x04		/* Checkbox fÅr die Hîhe selektieren */
#define FNTS_SRATIO		0x08		/* Checkbox fÅr das VerhÑltnis Breite/Hîhe selektieren */

#define FNTS_CHNAME		0x0100		/* Checkbox fÅr die Namen anzeigen */
#define FNTS_CHSTYLE	0x0200		/* Checkbox fÅr die Stile anzeigen */
#define FNTS_CHSIZE		0x0400		/* Checkbox fÅr die Hîhe anzeigen */
#define FNTS_CHRATIO	0x0800		/* Checkbox fÅr das VerhÑltnis Breite/Hîhe anzeigen */
#define FNTS_RATIO		0x1000		/* VerhÑltnis Breite/Hîhe einstellbar */
#define FNTS_BSET		0x2000		/* Button "setzen" anwÑhlbar */
#define FNTS_BMARK		0x4000		/* Button "markieren" anwÑhlbar */

/* Definitionen fÅr <button> bei fnts_evnt() */

#define FNTS_CANCEL		1		/* "Abbruch" wurde angewÑhlt */
#define FNTS_OK			2		/* "OK" wurde gedrÅckt */
#define FNTS_SET		3		/* "setzen" wurde angewÑhlt */
#define FNTS_MARK		4		/* "markieren" wurde betÑtigt */
#define FNTS_OPT		5		/* der applikationseigene Button wurde ausgewÑhlt */

FNT_DIALOG	*
		G_decl fnts_create			( short vdi_handle, short no_fonts, short font_flags, short dialog_flags, char *sample, char *opt_button dglob );
short	G_decl fnts_delete			( FNT_DIALOG *fnt_dialog, short vdi_handle dglob );
short	G_decl fnts_open			( FNT_DIALOG *fnt_dialog, short button_flags, short x, short y, long id, long pt, long ratio dglob );
#if MT_OLDWAY
short	G_decl fnts_close			( FNT_DIALOG *fnt_dialog dglob );
#else
short	G_decl fnts_close			( FNT_DIALOG *fnt_dialog, short *x, short *y dglob );
#endif

short	G_decl fnts_get_no_styles	( FNT_DIALOG *fnt_dialog, long id dglob );
long	G_decl fnts_get_style		( FNT_DIALOG *fnt_dialog, long id, short index dglob );
short	G_decl fnts_get_name		( FNT_DIALOG *fnt_dialog, long id, char *full_name, char *family_name, char *style_name dglob );
short	G_decl fnts_get_info		( FNT_DIALOG *fnt_dialog, long id, short *mono, short *outline dglob );

short	G_decl fnts_add				( FNT_DIALOG *fnt_dialog, FNTS_ITEM *user_fonts dglob );
void	G_decl fnts_remove			( FNT_DIALOG *fnt_dialog dglob );
short	G_decl fnts_update			( FNT_DIALOG *fnt_dialog, short button_flags, long id, long pt, long ratio dglob );

short	G_decl fnts_evnt			( FNT_DIALOG *fnt_dialog, EVNT *events, short *button, short *check_boxes, long *id, long *pt, long *ratio dglob );
short	G_decl fnts_do				( FNT_DIALOG *fnt_dialog, short button_flags, long id_in, long pt_in, long ratio_in, short *check_boxes, long *id, long *pt, long *ratio dglob );
#endif	/* WDLG_DIRECT_CALL */

/****** file selector definitions ***********************************************/
/* Sortiermodi */

#define SORTBYNAME	0
#define SORTBYDATE	1
#define SORTBYSIZE	2
#define SORTBYTYPE	3
#define SORTBYNONE	4

/* Flags fÅr Dateiauswahl */

#define DOSMODE	1
#define NFOLLOWSLKS	2
#define GETMULTI	8

/* fslx_set_flags */

#define SHOW8P3	1
typedef void XATTR;

typedef short __Cdecl XFSL_FILTER(char *path, char *name, XATTR *xa);

void * G_decl fslx_open(
			char *title,
			short x, short y,
			short	*handle,
			char *path, short pathlen,
			char *fname, short fnamelen,
			char *patterns,
			XFSL_FILTER *filter,
			char *paths,
			short sort_mode,
			short flags dglob);

short G_decl fslx_evnt(
			void *fsd,
			EVNT *events,
			char *path,
			char *fname,
			short *button,
			short *nfiles,
			short *sort_mode,
			char **pattern dglob );

void * G_decl fslx_do(
			char *title,
			char *path, short pathlen,
			char *fname, short fnamelen,
			char *patterns,
			XFSL_FILTER *filter,
			char *paths,
			short *sort_mode,
			short flags,
			short *button,
			short *nfiles,
			char **pattern dglob );

short	G_decl fslx_getnxtfile		( void *fsd, char *fname dglob );
short	G_decl fslx_close			( void *fsd dglob );
short	G_decl fslx_set_flags		( short flags, short *oldval dglob );

/************************************************************************/
#if ( WDLG_DIRECT_CALL == 0 )

#include	"PRDIALOG.H"	/* Struktur zum EinfÅgen eigener Drucker und Unterdialoge */
#include	"PRSETTNG.H"	/* PRN_SETTINGS-Struktur */

typedef void *PRN_DIALOG;

PRN_DIALOG *
		G_decl pdlg_create			( short dialog_flags dglob );
short	G_decl pdlg_delete			( PRN_DIALOG *prn_dialog dglob );
short	G_decl pdlg_open			( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, char *document_name, short option_flags, short x, short y dglob );
short	G_decl pdlg_close			( PRN_DIALOG *prn_dialog, short *x, short *y dglob );

long G_decl G_nv(pdlg_get_setsize);

short	G_decl pdlg_add_printers	( PRN_DIALOG *prn_dialog, DRV_INFO *drv_info dglob );
short	G_decl pdlg_remove_printers	( PRN_DIALOG *prn_dialog dglob );
short	G_decl pdlg_update			( PRN_DIALOG *prn_dialog, char *document_name dglob );
short	G_decl pdlg_add_sub_dialogs	( PRN_DIALOG *prn_dialog, PDLG_SUB *sub_dialogs dglob );
short	G_decl pdlg_remove_sub_dialogs( PRN_DIALOG *prn_dialog dglob );
PRN_SETTINGS *
		G_decl pdlg_new_settings	( PRN_DIALOG *prn_dialog dglob );
short	G_decl pdlg_free_settings	( PRN_SETTINGS *settings dglob );
short	G_decl pdlg_dflt_settings	( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings dglob );
short	G_decl pdlg_validate_settings( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings dglob );
short	G_decl pdlg_use_settings	( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings dglob );
short	G_decl pdlg_save_default_settings( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings dglob );
short	G_decl pdlg_evnt			( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, EVNT *events, short *button dglob );
short	G_decl pdlg_do				( PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, char *document_name, short option_flags dglob );


/* <dialog_flags> fÅr pdlg_create() */
#define	PDLG_3D				0x0001

/* <option_flags> fÅr pdlg_open/do() */
#define	PDLG_PREFS			0x0000			/* Einstelldialog anzeigen */
#define	PDLG_PRINT			0x0001			/* Druckdialog anzeigen */

#define	PDLG_ALWAYS_COPIES	0x0010			/* immer Kopien anbieten */
#define	PDLG_ALWAYS_ORIENT	0x0020			/* immer Querformat anbieten */
#define	PDLG_ALWAYS_SCALE	0x0040			/* immer Skalierung anbieten */

#define	PDLG_EVENODD		0x0100			/* Option fÅr gerade und ungerade Seiten anbieten */

/* <button> fÅr pdlg_evnt()/pdlg_do */
#define	PDLG_CANCEL			1				/* "Abbruch" wurde angewÑhlt */
#define	PDLG_OK				2				/* "OK" wurde gedrÅckt */


#endif	/*WDLG_DIRECT_CALL*/

/************************************************************************\

/* Editor-Funktionen */

\************************************************************************/
typedef void XEDITINFO;

XEDITINFO *
		G_decl edit_create			(void);
short	G_decl edit_open			( OBJECT *tree, short obj dglob);
void	G_decl edit_close			( OBJECT *tree, short obj dglob);
void	G_decl edit_delete			( XEDITINFO *xi dglob);
short	G_decl edit_cursor			( OBJECT *tree, short obj, short whdl, short show dglob);
short	G_decl edit_evnt			( OBJECT *tree, short obj, short whdl,	EVNT *ev dglob);
short	G_decl edit_get_buf			( OBJECT *tree, short obj, char **buf, long *buflen, long *txtlen dglob );
short	G_decl edit_get_format		( OBJECT *tree, short obj, short *tabwidth, short *autowrap dglob );
short	G_decl edit_get_colour		( OBJECT *tree, short obj, short *tcolour, short *bcolour dglob );
short	G_decl edit_get_cursor		( OBJECT *tree, short obj, char **cursorpos dglob );
short	G_decl edit_get_font		( OBJECT *tree, short obj,	short *fontID, short *fontH, short *mono dglob );
void	G_decl edit_set_buf			( OBJECT *tree, short obj, char *buf, long buflen dglob );
void	G_decl edit_set_format		( OBJECT *tree, short obj, short tabwidth, short autowrap dglob );
void	G_decl edit_set_font		( OBJECT *tree, short obj, short fontID, short fontH, short mono dglob );
void	G_decl edit_set_colour		( OBJECT *tree, short obj, short tcolour, short bcolour dglob );
void	G_decl edit_set_cursor		( OBJECT *tree, short obj, char *cursorpos dglob );
short	G_decl edit_resized			( OBJECT *tree, short obj, short *oldrh, short *newrh dglob );
short	G_decl edit_get_dirty		( OBJECT *tree, short obj dglob );
void	G_decl edit_set_dirty		( OBJECT *tree, short obj,	short dirty dglob );
void	G_decl edit_get_sel			( OBJECT *tree, short obj, char **bsel, char **esel dglob );
void	G_decl edit_get_pos			( OBJECT *tree, short obj, short *xscroll, long *yscroll, char **cyscroll, char **cursorpos, short *cx, short *cy dglob );
void	G_decl edit_set_pos			( OBJECT *tree, short obj, short xscroll, long yscroll, char *cyscroll, char *cursorpos, short cx, short cy dglob );
void	G_decl edit_get_scrollinfo	( OBJECT *tree, short obj,	long *nlines, long *yscroll, short *yvis, short *yval, short *ncols, short *xscroll, short *xvis dglob );
short	G_decl edit_scroll			( OBJECT *tree, short obj, short whdl, long yscroll, short xscroll dglob );
#endif
