/******************************************************************************
 * XRSRC.C
 *
 *			Extended Resource-Manager. RSC-Files can now have up to
 *			4294967295 bytes length.
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tos.h>
#include <vdi.h>
#include <aes.h>
#include <assert.h>
#ifdef __GNUC__
#include <sys/stat.h>
#else
#include <ext.h>
#endif
#include "xrsrc.h"

/* horizontal text alignment */
#ifndef ALI_LEFT
#define ALI_LEFT         0
#define ALI_CENTER       1
#define ALI_RIGHT        2
#endif
#ifndef ALI_TOP
#define ALI_TOP          5
#endif
#ifndef R_IBPTEXT
#define R_IBPTEXT 13
#endif

#ifndef FALSE
# define FALSE 0
# define TRUE 1
#endif

#ifndef _CDECL
#ifdef __GNUC__
#define _CDECL /**/
#else
#define _CDECL cdecl
#endif
#endif

#ifndef G_SHORTCUT
#define G_SHORTCUT 38
#endif

#ifndef G_EXTBOX
#define G_EXTBOX 40
#endif
#ifndef G_WHITE
#define G_WHITE 0
#endif
#ifndef G_BLACK
#define G_BLACK 1
#endif
#ifndef OS_SELECTED
#define OS_SELECTED SELECTED
#endif
#undef fclose

#ifndef _AESrscfile
#  define _AESrscfile (((AES_GLOBAL *)_GemParBlk.global)->ap_ptree)
#  define _AESrscmem  (((AES_GLOBAL *)_GemParBlk.global)->ap_rscmem)
#endif

#define USE_NICELINES 0

#define ICOLSPEC_GET_DATACOL(color)   ( ((color) >> 12) & 0x0f )
#define ICOLSPEC_GET_MASKCOL(color)   ( ((color) >>  8) & 0x0f )
#define ICOLSPEC_GET_CHARACTER(color) ( ((color)      ) & 0xff )

/****** TYPES ****************************************************************/

struct userdef {
	OBJECT orig;
	USERBLK user;
	_WORD obj;
};

struct userdef_list {
	struct userdef_list *next;
	RSHDR *hdr;
	OBJECT *objects;
	_WORD nobjs;
	_WORD nuserobjs;
	struct userdef userobjs[1];
};

/****** VARIABLES ************************************************************/

static struct userdef_list *userdefs;

/*
 * vdi handle used for drawing USERDEF objects
 * It's safe to directly use the AES handle here,
 * because we save/restore all attributes we change
 */
static _WORD aes_handle;

#define TEST_COLOR 15
#define XMAX_PLANES 32
#define XMAX_COLOR 256

typedef _WORD table4[XMAX_COLOR][4];

/*
 * vdi handle used for initializing the color icon tables
 */
#define xvdi_handle aes_handle
static _WORD xscrn_planes;

/* number of bytes per pixel (0 == planeoriented) */
static _WORD xpixelbytes = -1;
/* table for plane oriented images */
static _WORD *colortbl;
/* table for pixel oriented imaged */
static _ULONG colortbl2[XMAX_COLOR];
/* wether an palette has already been set */
static _BOOL is_std_palette;
static table4 rgb_palette;

static _WORD xscr_w, xscr_h;

static _WORD const pixtbl[XMAX_COLOR] = {
    0,   2,   3,   6,   4,   7,   5,   8,   9,  10,  11,  14,  12,  15,  13, 255,
   16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
   32 , 33 , 34 , 35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
   48 , 49 , 50 , 51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
   64 , 65 , 66 , 67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
   80 , 81 , 82 , 83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
   96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
  112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
  144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
  176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
  192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
  224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,   1
};

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static _BOOL xywh2pxy(_WORD x, _WORD y, _WORD w, _WORD h, _WORD *pxy, _WORD max_w, _WORD max_h)
{
	if (x < 0)
	{
		w += x;
		x = 0;
	}
	if (x >= max_w)
	{
		x = 0;
		w = 0;
	}
	if (x + w > max_w)
	{
		w = max_w - x;
	}
	if (y < 0)
	{
		h += y;
		y = 0;
	}
	if (y >= max_h)
	{
		y = 0;
		h = 0;
	}
	if (y + h > max_h)
	{
		h = max_h - y;
	}
	pxy[0] = x;
	pxy[1] = y;
	pxy[2] = x + w - 1;
	pxy[3] = y + h - 1;
	return w > 0 && h > 0;
}

/*** ---------------------------------------------------------------------- ***/

static void save_fillattr(_WORD handle, _WORD attrib[5])
{
	vqf_attributes(handle, attrib);
}

/*** ---------------------------------------------------------------------- ***/

static void restore_fillattr(_WORD handle, _WORD attrib[5])
{
	vsf_interior(handle, attrib[0]);
	vsf_color(handle, attrib[1]);
	vsf_style(handle, attrib[2]);
	vswr_mode(handle, attrib[3]);
	vsf_perimeter(handle, attrib[4]);
}

/*** ---------------------------------------------------------------------- ***/

static void save_lineattr(_WORD handle, _WORD attrib[6])
{
	vql_attributes(handle, attrib);
}

/*** ---------------------------------------------------------------------- ***/

static void restore_lineattr(_WORD handle, _WORD attrib[6])
{
	vsl_type(handle, attrib[0]);
	vsl_color(handle, attrib[1]);
	vswr_mode(handle, attrib[2]);
	vsl_width(handle, attrib[3]);
	vsl_ends(handle, attrib[4], attrib[5]);
}

/*** ---------------------------------------------------------------------- ***/

static void save_textattr(_WORD handle, _WORD attrib[10])
{
	_WORD dummy;
	
	vqt_attributes(handle, attrib);
	vst_effects(handle, 0);
	vst_alignment(handle, ALI_LEFT, ALI_TOP, &dummy, &dummy);
	vst_rotation(handle, 0);
}

/*** ---------------------------------------------------------------------- ***/

static void save_clip(_WORD handle, _WORD clip[5])
{
	_WORD wo[57];
	
	vq_extnd(handle, 1, wo);
	clip[0] = wo[45];
	clip[1] = wo[46];
	clip[2] = wo[47];
	clip[3] = wo[48];
	clip[4] = wo[19];
}

/*** ---------------------------------------------------------------------- ***/

static void restore_clip(_WORD handle, _WORD clip[5])
{
	vs_clip(handle, clip[4], clip);
}

/*** ---------------------------------------------------------------------- ***/

/*
 * set VDI clipping to coordinates in PARMBLK structure.
 * Neccessary on some AES that don't set the clipping
 * rectangle during objc_draw() (i.e. XaAES)
 */
static void set_user_clip(_WORD handle, PARMBLK *pb)
{
	_WORD pxy[4];
	
	pxy[0] = pb->pb_xc;
	pxy[1] = pb->pb_yc;
	pxy[2] = pb->pb_xc + pb->pb_wc - 1;
	pxy[3] = pb->pb_yc + pb->pb_hc - 1;
	vs_clip(handle, TRUE, pxy);
}

/*** ---------------------------------------------------------------------- ***/

static void restore_textattr(_WORD handle, _WORD attrib[10])
{
	_WORD dummy;
	
	vst_color(handle, attrib[1]);
	vst_rotation(handle, attrib[2]);
	vst_alignment(handle, attrib[3], attrib[4], &dummy, &dummy);
	/* original vqt_attributes returns mode-1 */
	vswr_mode(handle, attrib[5] + 1);
	vst_height(handle, attrib[7], &dummy, &dummy, &dummy, &dummy);
}

/*** ---------------------------------------------------------------------- ***/

static void GetScreenSize(_WORD *width, _WORD *height)
{
	*width = xscr_w;
	*height = xscr_h;
}

/*** ---------------------------------------------------------------------- ***/

static void scrfdb(MFDB *fdb)
{
	fdb->fd_addr = (void *) 0;
	GetScreenSize(&fdb->fd_w, &fdb->fd_h);
	fdb->fd_wdwidth = (fdb->fd_w + 15) >> 4;
	fdb->fd_stand = FALSE;
	fdb->fd_nplanes = xscrn_planes;
	fdb->fd_r1 = fdb->fd_r2 = fdb->fd_r3 = 0;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

void GetTextSize(_WORD *width, _WORD *height)
{
	_WORD dummy;
	
	graf_handle(width, height, &dummy, &dummy);
}

/*** ---------------------------------------------------------------------- ***/

static void rsc_obfix(OBJECT *tree, _ULONG count)
{
	_WORD wchar, hchar;
	
	GetTextSize(&wchar, &hchar);
	while (count)
	{
		tree->ob_x = wchar * (tree->ob_x & 0xff) + (tree->ob_x >> 8);
		tree->ob_y = hchar * (tree->ob_y & 0xff) + (tree->ob_y >> 8);
		tree->ob_width = wchar * (tree->ob_width & 0xff) + (tree->ob_width >> 8);
		tree->ob_height = hchar * (tree->ob_height & 0xff) + (tree->ob_height >> 8);
		tree++;
		count--;
	}
}

/*** ---------------------------------------------------------------------- ***/

static _WORD _CDECL draw_nothing(PARMBLK *pb)
{
	(void) pb;
	return 0;
}

/*** ---------------------------------------------------------------------- ***/

static void xrsrc_hdr2xrsc(RSXHDR *xrsc_header, RSHDR *header)
{
	xrsc_header->rsh_vrsn	 = 3 | (header->rsh_vrsn & ~RSC_VERSION_MASK);
	xrsc_header->rsh_extvrsn = XRSC_VRSN_ORCS;
	xrsc_header->rsh_object  = header->rsh_object;
	xrsc_header->rsh_tedinfo = header->rsh_tedinfo;
	xrsc_header->rsh_iconblk = header->rsh_iconblk;
	xrsc_header->rsh_bitblk  = header->rsh_bitblk;
	xrsc_header->rsh_frstr	 = header->rsh_frstr;
	xrsc_header->rsh_string  = header->rsh_string;
	xrsc_header->rsh_imdata  = header->rsh_imdata;
	xrsc_header->rsh_frimg	 = header->rsh_frimg;
	xrsc_header->rsh_trindex = header->rsh_trindex;
	xrsc_header->rsh_nobs	 = header->rsh_nobs;
	xrsc_header->rsh_ntree	 = header->rsh_ntree;
	xrsc_header->rsh_nted	 = header->rsh_nted;
	xrsc_header->rsh_nib	 = header->rsh_nib;
	xrsc_header->rsh_nbb	 = header->rsh_nbb;
	xrsc_header->rsh_nstring = header->rsh_nstring;
	xrsc_header->rsh_nimages = header->rsh_nimages;
	xrsc_header->rsh_rssize  = header->rsh_rssize;
}

/*** ---------------------------------------------------------------------- ***/

static void std_palette(table4 palette)
{
	_WORD color;

	for (color = 0; color < XMAX_COLOR; color++)
	{
		vq_color(xvdi_handle, pixtbl[color], 1, palette[color]);
		palette[color][3] = pixtbl[color];
	}
}
			
/*****************************************************************************/
/* Test how many bytes per pixel are needed in device-dependent format       */
/*****************************************************************************/

static _WORD test_rez(void)
{
	_WORD i, np, color, bpp = 0;
	_WORD pxy[8], rgb[3];
	_UWORD backup[XMAX_PLANES], test[XMAX_PLANES], test2[XMAX_PLANES];
	_WORD black[3] = { 0, 0, 0 };
	_WORD white[3] = { 1000, 1000, 1000 };
	MFDB screen;
	MFDB pixel;
	MFDB stdfm;
	
	pixel.fd_addr = NULL;
	pixel.fd_w = 16;
	pixel.fd_h = 1;
	pixel.fd_wdwidth = 1;
	pixel.fd_stand = FALSE;
	pixel.fd_nplanes = xscrn_planes;
	pixel.fd_r1 = 0;
	pixel.fd_r2 = 0;
	pixel.fd_r3 = 0;
	stdfm = pixel;
	stdfm.fd_stand = TRUE;
	
	if (xscrn_planes >= 8)
	{
		if (xscrn_planes == 8)
		{
			color = 0xff;
			memset(test, 0, sizeof(test));
			memset(test2, 0, sizeof(test2));
			for (np = 0; np < xscrn_planes; np++)
				test2[np] = (color & (1 << np)) << (15 - np);
			
			pixel.fd_addr = test;
			stdfm.fd_addr = test2;
			vr_trnfm(xvdi_handle, &stdfm, &pixel);
			
			for (i = 1; i < xscrn_planes; i++)
				if (test[i])
					break;
			
			if (i >= xscrn_planes && !(test[0] & 0x00ff))
				bpp = 1;
		} else
		{
			_WORD lineattrib[6];
			_WORD clip[5];
			
			save_lineattr(xvdi_handle, lineattrib);
			save_clip(xvdi_handle, clip);
			
			scrfdb(&screen);
			pxy[0] = 0;
			pxy[1] = 0;
			pxy[2] = screen.fd_w - 1;
			pxy[3] = screen.fd_h - 1;
			vs_clip(xvdi_handle, FALSE, pxy);
			
			memset(backup, 0, sizeof(backup));
			
			vswr_mode(xvdi_handle, MD_REPLACE);
			vsl_ends(xvdi_handle, 0, 0);
			vsl_type(xvdi_handle, SOLID);
			vsl_width(xvdi_handle, 1);
			pxy[0] = 0;
			pxy[1] = 0;
			pxy[2] = 0;
			pxy[3] = 0;
			pxy[4] = 0;
			pxy[5] = 0;
			pxy[6] = 0;
			pxy[7] = 0;
			
			v_hide_c(xvdi_handle);
			
			/* save pixel */
			pixel.fd_addr = backup;
			vro_cpyfm(xvdi_handle, S_ONLY, pxy, &screen, &pixel);
			
			/* save old color */
			vq_color(xvdi_handle, TEST_COLOR, 1, rgb);
			
			/* set 1 white pixel */
			vsl_color(xvdi_handle, TEST_COLOR);
			vs_color(xvdi_handle, TEST_COLOR, white);
			v_pline(xvdi_handle, 2, pxy);
			
			/* fetch pixel value */
			memset(test, 0, sizeof(test));
			pixel.fd_addr = test;
			vro_cpyfm(xvdi_handle, S_ONLY, pxy, &screen, &pixel);
			
			for (i = ((xscrn_planes + 15) >> 4) * 2; i < xscrn_planes; i++)
				if (test[i])
					break;
			
			if (i >= xscrn_planes)
			{
				vs_color(xvdi_handle, TEST_COLOR, black);
				v_pline(xvdi_handle, 2, pxy);
				
				memset(test, 0, sizeof(test));
				vro_cpyfm(xvdi_handle, S_ONLY, pxy, &screen, &pixel);
				
				for (i = ((xscrn_planes + 15) >> 4) * 2; i < xscrn_planes; i++)
					if (test[i])
						break;
				
				if (i >= xscrn_planes)
					bpp = (xscrn_planes + 7) >> 3;
			}

			/* restore old color */
			vs_color(xvdi_handle, TEST_COLOR, rgb);
			
			/* restore saved pixel */
			pixel.fd_addr = backup;
			vro_cpyfm(xvdi_handle, S_ONLY, pxy, &pixel, &screen);
			
			restore_lineattr(xvdi_handle, lineattrib);
			restore_clip(xvdi_handle, clip);
			
			v_show_c(xvdi_handle, 1);
		}
	}

	return bpp;
}

/*****************************************************************************/
/* determine pixel values for the selected palette                           */
/*****************************************************************************/
static void xfill_colortbl(void)
{
	_WORD np, color, backup[XMAX_PLANES * 4];
	_WORD pxy[8], rgb[3];
	MFDB screen;
	MFDB pixel;
	MFDB stdfm;
	_UWORD pixel_data[XMAX_PLANES];
	_UWORD pixel_data2[XMAX_PLANES];
	
	pixel.fd_addr = NULL;
	pixel.fd_w = 16;
	pixel.fd_h = 1;
	pixel.fd_wdwidth = 1;
	pixel.fd_stand = FALSE;
	pixel.fd_nplanes = xscrn_planes;
	pixel.fd_r1 = 0;
	pixel.fd_r2 = 0;
	pixel.fd_r3 = 0;
	stdfm = pixel;
	stdfm.fd_stand = TRUE;
	
	if (xscrn_planes >= 8)
	{
		if (xscrn_planes > 8)
		{
			_WORD lineattrib[6];
			_WORD clip[5];
			
			save_lineattr(xvdi_handle, lineattrib);
			save_clip(xvdi_handle, clip);
			
			scrfdb(&screen);

			pxy[0] = 0;
			pxy[1] = 0;
			pxy[2] = screen.fd_w - 1;
			pxy[3] = screen.fd_h - 1;
			vs_clip(xvdi_handle, TRUE, pxy);
			v_hide_c(xvdi_handle);

			if (xpixelbytes == 0 && colortbl == NULL)
			{
				colortbl = (_WORD *)malloc(xscrn_planes * XMAX_COLOR * sizeof(_WORD));
			}
			
			memset(backup, 0, sizeof(backup));
			if (colortbl != NULL)
				memset(colortbl, 0, xscrn_planes * XMAX_COLOR * sizeof(_WORD));
			
			vswr_mode(xvdi_handle, MD_REPLACE);
			vsl_ends(xvdi_handle, 0, 0);
			vsl_type(xvdi_handle, SOLID);
			vsl_width(xvdi_handle, 1);
			
			/* save pixel value */
			memset(pxy, 0, sizeof(pxy));
			pxy[2] = 1;
			pxy[6] = 1;
			pixel.fd_addr = backup;
			vro_cpyfm(xvdi_handle, S_ONLY, pxy, &screen, &pixel);
			pxy[6] = 0;
			
			/* save old color */
			vq_color(xvdi_handle, TEST_COLOR, 1, rgb);

			for (color = 0; color < XMAX_COLOR; color++)
			{
				vs_color(xvdi_handle, TEST_COLOR, rgb_palette[color]);
				vsl_color(xvdi_handle, TEST_COLOR);
				pxy[2] = 1;
				v_pline(xvdi_handle, 2, pxy);
				
				pixel.fd_addr = pixel_data;
				stdfm.fd_addr = pixel_data2;

				/* vro_cpyfm, because v_get_pixel does not work for TrueColor */
				pxy[2] = 0;
				memset(pixel_data, 0, sizeof(pixel_data));
				vro_cpyfm(xvdi_handle, S_ONLY, pxy, &screen, &pixel);
				
				if (xpixelbytes != 0)
				{
					colortbl2[color] = 0L;
					memcpy(&colortbl2[color], pixel.fd_addr, xpixelbytes);
				} else
				{
					memset(pixel_data2, 0, sizeof(pixel_data2));
					vr_trnfm(xvdi_handle, &pixel, &stdfm);
					for (np = 0; np < xscrn_planes; np++)
						if (pixel_data2[np])
							pixel_data2[np] = 0xffff;
					if (colortbl != NULL)
						memcpy(&colortbl[color * xscrn_planes], pixel_data2, xscrn_planes * sizeof(_WORD));
				}
			}
			
			/* restore old color */
			vs_color(xvdi_handle, TEST_COLOR, rgb);

			/* restore old pixel */
			pixel.fd_addr = backup;
			pxy[2] = 1;
			pxy[6] = 1;
			vro_cpyfm(xvdi_handle, S_ONLY, pxy, &pixel, &screen);
			
			/* restore line attributes */
			restore_lineattr(xvdi_handle, lineattrib);
			restore_clip(xvdi_handle, clip);
			
			v_show_c(xvdi_handle, 1);
		} else
		{
			if (xpixelbytes != 0)
				for (color = 0; color < XMAX_COLOR; color++)
					*(unsigned char *)&colortbl2[color] = color;
		}
	}
}

/*****************************************************************************/
/* std_to_byte converts an image from standard format to device dependent    */
/* format (for resolutions >= 16 Planes)                                     */
/*****************************************************************************/

static void std_to_byte(_UWORD *col_data, _LONG len, _WORD old_planes, _ULONG *colortbl2, MFDB *s)
{
	_LONG x, i, pos;
	_UWORD np, *new_data, pixel, color, back[XMAX_PLANES];
	_WORD memflag = FALSE;
	unsigned char *p1, *p2;
	_ULONG colback = 0;
	_UWORD *plane_ptr[XMAX_PLANES];
	
	if ((s->fd_addr = (_UWORD *)malloc(len * 2 * s->fd_nplanes)) == NULL)
	{
		return;
	}
	memcpy(s->fd_addr, col_data, len * 2 * old_planes);
	new_data = (_UWORD *)s->fd_addr;
	p1 = (unsigned char *)new_data;

	if (old_planes < 8)
	{
		colback = colortbl2[(1 << old_planes) - 1];
		colortbl2[(1 << old_planes) - 1] = colortbl2[XMAX_COLOR - 1];
	}
	
	for (i = 0; i < old_planes; i++)
		plane_ptr[i] = &col_data[i * len];
	
	pos = 0;
	
	for (x = 0; x < len; x++)
	{
		for (np = 0; np < old_planes; np++)
			back[np] = plane_ptr[np][x];
		
		for (pixel = 0; pixel < 16; pixel++)
		{
			color = 0;
			for (np = 0; np < old_planes; np++)
			{
				color |= ((back[np] & 0x8000) >> (15 - np));
				back[np] <<= 1;
			}
			
			switch (xpixelbytes)
			{
			case 2:
				new_data[pos++] = *(_UWORD *) &colortbl2[color];
				break;

			case 3:
				p2 = (unsigned char *) &colortbl2[color];
				*(p1++) = *(p2++);
				*(p1++) = *(p2++);
				*(p1++) = *(p2++);
				break;

			case 4:
				((_ULONG *)new_data)[pos++] = colortbl2[color];
				break;
			}
		}
	}

	if (old_planes < 8)
		colortbl2[(1 << old_planes) - 1] = colback;

	if (memflag)
		free(col_data);
}

/*** ---------------------------------------------------------------------- ***/

static _BOOL W_Cicon_Setpalette(_WORD *palette)
{
	_BOOL need_recalc = FALSE;
	
	if (palette != NULL)
	{
		_WORD i;
		table4 palbuf;
		
		std_palette(palbuf);
		is_std_palette = TRUE;
		
		for (i = 0; i < XMAX_COLOR; i++)
		{
			if (rgb_palette[i][0] != palette[0] ||
				rgb_palette[i][1] != palette[1] ||
				rgb_palette[i][2] != palette[2])
				need_recalc = TRUE;
			if (palbuf[i][0] != palette[0] ||
				palbuf[i][1] != palette[1] ||
				palbuf[i][2] != palette[2])
				is_std_palette = FALSE;
			rgb_palette[i][0] = *palette++;
			rgb_palette[i][1] = *palette++;
			rgb_palette[i][2] = *palette++;
			rgb_palette[i][3] = *palette++;
		}
	} else
	{
		need_recalc = !is_std_palette;
		std_palette(rgb_palette);
		is_std_palette = TRUE;
	}
	if (xpixelbytes < 0)
	{
		xpixelbytes = test_rez();
		need_recalc = TRUE;
	}
	if (need_recalc)
		xfill_colortbl();
	return TRUE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void *rs_load(const char *filename)
{
	register _UWORD UObj;
	register CICONBLK *cicon_p;
	RSXHDR xrsc_header;
	unsigned char *buf = NULL;
	FILE *fp;
	_ULONG filesize;

	cicon_p = NULL;
	{
		char fname_buf[128];
		
		strncpy(fname_buf, filename, sizeof(fname_buf));
		fname_buf[sizeof(fname_buf) - 1] = '\0';
		if (!shel_find(fname_buf) || (fp = fopen(fname_buf, "rb")) == NULL)
		{
			form_error(2); /* ENOENT */
			return NULL;
		}
	}

	{
		struct stat st;
		
		if (fstat(fileno(fp), &st) < 0)
		{
			fclose(fp);
			return NULL;
		}
		filesize = st.st_size;
	}

	if ((buf = (unsigned char *)malloc((size_t)filesize)) == NULL)
	{
		fclose(fp);
		form_error(8); /* ENOMEM */
		return NULL;
	}
	if (fread(buf, 1, (size_t)filesize, fp) != filesize)
	{
		free(buf);
		fclose(fp);
		return NULL;
	}
	fclose(fp);

	if (!IS_XRSC_HEADER(buf))
		xrsrc_hdr2xrsc(&xrsc_header, (RSHDR *)buf);
	else
		xrsc_header = *((RSXHDR *)buf);
	
	if (xrsc_header.rsh_vrsn & RSC_EXT_FLAG)
	{
		_LONG *p;
		_BOOL ok = TRUE;

		p = (_LONG *)(buf + (size_t)xrsc_header.rsh_rssize);
		if ((_ULONG)p[RSC_EXT_FILESIZE] != filesize)
		{
			ok = FALSE;
		} else if (p[RSC_EXT_CICONBLK] < 0 || (_ULONG)p[RSC_EXT_CICONBLK] >= filesize)
		{
			ok = FALSE;
		} else
		{
			_LONG *cp = p + RSC_EXT_CICONBLK + 1;

			while (ok != FALSE)
			{
				if ((_ULONG)((unsigned char *)cp - buf) >= filesize)
					ok = FALSE;
				else if (*cp == 0)
					break;
				else if (*cp != -1)
				{
					/* ok = FALSE; */
					if (cp == (p + RSC_EXT_PALETTE))
					{
						_WORD *palette = (_WORD *)(buf + (size_t)(*cp));
						W_Cicon_Setpalette(palette);
					}
					break;
				}
				cp++;
			}
		}

		if (ok != FALSE)
		{
			p = (_LONG *)(buf + (size_t)p[RSC_EXT_CICONBLK]);
			while (ok != FALSE)
			{
				if ((_ULONG)((unsigned char *)p - buf) >= filesize)
					ok = FALSE;
				else if (*p == -1)
					break;
				else if (*p != 0)
					ok = FALSE;
				else
					p++;
			}
			if (ok != FALSE && *p == -1)
			{
				p++;
				cicon_p = (CICONBLK *)p;
			}
		}
		if (ok == FALSE)
		{
			free(buf);
			return NULL;
		}
	}

	{
		OBJECT *_rs_object;

		_rs_object = (OBJECT *)(buf + (size_t)xrsc_header.rsh_object);
		rsc_obfix(_rs_object, xrsc_header.rsh_nobs);
		for (UObj = 0; UObj < xrsc_header.rsh_nobs; UObj++)
		{
			switch (_rs_object->ob_type & 0xff)
			{
			case G_BOX:
			case G_IBOX:
			case G_BOXCHAR:
			case G_EXTBOX:
				break;
			case G_STRING:
			case G_TITLE:
			case G_BUTTON:
			case G_TEXT:
			case G_FTEXT:
			case G_BOXTEXT:
			case G_FBOXTEXT:
			case G_IMAGE:
			case G_ICON:
				_rs_object->ob_spec.free_string = (char *)buf + (size_t)(_rs_object->ob_spec.index);
				break;
			case G_SHORTCUT:
				/* not changed to G_STRING here;
				   might be displayed in window
				   where we use our own functions
				 */
				_rs_object->ob_spec.free_string = (char *)buf + (size_t)(_rs_object->ob_spec.index);
				break;
			case G_CICON:

				if (cicon_p == NULL)
				{
					/* !!! */
				} else
				{
					CICON *dp;
					CICONBLK *cicon;
					_LONG size;
					unsigned char *p;
					_LONG num_cicons;
					_LONG idx;

					cicon = cicon_p;
					cicon_p++;
					_rs_object->ob_spec.ciconblk = cicon;
					size = ((cicon->monoblk.ib_wicon + 15) / 16) * 2l * cicon->monoblk.ib_hicon;
					p = (unsigned char *)cicon_p;
					cicon->monoblk.ib_pdata = (_WORD *)p;
					p += (size_t)size;
					cicon->monoblk.ib_pmask = (_WORD *)p;
					p += (size_t)size;
					idx = (_LONG)cicon->monoblk.ib_ptext;
					if (idx <= 0 || (buf + (size_t)idx) == p || idx < (_LONG)xrsc_header.rsh_string || idx >= (_LONG)xrsc_header.rsh_rssize)
						cicon->monoblk.ib_ptext = (char *)p;
					else
						cicon->monoblk.ib_ptext = (char *)buf + (size_t)idx;
					p += 12; /* skip reserved space for icon text */
					dp = (CICON *)p;
					num_cicons = (_LONG)(cicon->mainlist);
					if (p > (buf + (size_t)filesize))
					{
						free(buf);
						return NULL;
					}
					if (num_cicons == 0)
					{
						cicon->mainlist = NULL;
					} else
					{
						cicon->mainlist = dp;
						while (num_cicons != 0)
						{
							p += sizeof(CICON);
							dp->col_data = (_WORD *)p;
							p += (size_t)(size * dp->num_planes);
							dp->col_mask = (_WORD *)p;
							p += (size_t)size;
							if (dp->sel_data != NULL)
							{
								dp->sel_data = (_WORD *)p;
								p += (size_t)(size * dp->num_planes);
								dp->sel_mask = (_WORD *)p;
								p += (size_t)size;
							} else
							{
								dp->sel_data = NULL;
								dp->sel_mask = NULL;
							}
							num_cicons--;
							if (num_cicons == 0)
							{
								dp->next_res = NULL;
							} else
							{
								dp->next_res = (CICON *)p;
							}
							dp = (CICON *)p;
						}
					}
					cicon_p = (CICONBLK *)p;
				}
				break;
			case G_USERDEF:
				_rs_object->ob_spec.userblk = (USERBLK *)(buf + (size_t)_rs_object->ob_spec.index);
				/*
				 * It's up to the application to set the appropiate function.
				 * To be on the safe side, let it point to some function
				 * that draws a box only, or simply does nothing.
				 */
				_rs_object->ob_spec.userblk->ub_code = draw_nothing;
				break;
			}
			_rs_object++;
		}
	}

	{
		TEDINFO *_rs_tedinfo;

		_rs_tedinfo = (TEDINFO *)(buf + (size_t)xrsc_header.rsh_tedinfo);
		for (UObj = 0; UObj < xrsc_header.rsh_nted; UObj++)
		{
			_rs_tedinfo->te_ptext += (size_t)buf;
			_rs_tedinfo->te_ptmplt += (size_t)buf;
			_rs_tedinfo->te_pvalid += (size_t)buf;
			_rs_tedinfo++;
		}
	}

	{
		ICONBLK *_rs_iconblk;

		_rs_iconblk = (ICONBLK *)(buf + (size_t)xrsc_header.rsh_iconblk);
		for (UObj = 0; UObj < xrsc_header.rsh_nib; UObj++)
		{
			_rs_iconblk->ib_pmask = (_WORD *)(buf + (size_t)(_rs_iconblk->ib_pmask));
			_rs_iconblk->ib_pdata = (_WORD *)(buf + (size_t)(_rs_iconblk->ib_pdata));
			_rs_iconblk->ib_ptext = (char *)buf + (size_t)_rs_iconblk->ib_ptext;
			_rs_iconblk++;
		}
	}

	{
		BITBLK *_rs_bitblk;

		_rs_bitblk = (BITBLK *)(buf + (size_t)xrsc_header.rsh_bitblk);
		for (UObj = 0; UObj < xrsc_header.rsh_nbb; UObj++)
		{
			_rs_bitblk->bi_pdata = (_WORD *)(buf + (size_t)(_rs_bitblk->bi_pdata));
			_rs_bitblk++;
		}
	}

	{
		char **_rs_frstr;

		_rs_frstr = (char **)(buf + (size_t)xrsc_header.rsh_frstr);
		for (UObj = 0; UObj < xrsc_header.rsh_nstring; UObj++)
		{
			*_rs_frstr += (size_t)buf;
			_rs_frstr++;
		}
	}

	{
		BITBLK **_rs_frimg;

		_rs_frimg = (BITBLK **)(buf + (size_t)xrsc_header.rsh_frimg);
		for (UObj = 0; UObj < xrsc_header.rsh_nimages; UObj++)
		{
			*_rs_frimg = (BITBLK *)(buf + (size_t)(*_rs_frimg));
			_rs_frimg++;
		}
	}

	{
		OBJECT **_rs_trindex;

		_rs_trindex = (OBJECT **)(buf + (size_t)xrsc_header.rsh_trindex);
#if 0
		/*
		 * settings these variables in the global array
		 * would actually allow using rsrc_gaddr(),
		 * but rsrc_free() might bomb since we did not use rsrc_load before
		 */
		_AESrscfile = _rs_trindex;
		_AESrscmem = buf;
#endif
		for (UObj = 0; UObj < xrsc_header.rsh_ntree; UObj++)
		{
			*_rs_trindex = (OBJECT *)(buf + (size_t)(*_rs_trindex));
			_rs_trindex++;
		}
	}
	
	{
		OBJECT *_rs_object;

		_rs_object = (OBJECT *)(buf + (size_t)xrsc_header.rsh_object);
		hfix_objs((RSHDR *)buf, _rs_object, (_WORD)xrsc_header.rsh_nobs);
	}
	
	return buf;
}

/*****************************************************************************/
/* Convert icon data to current resolution                                   */
/* (e.g. 4 Plane Icon to 24 Plane TrueColor)                                 */
/*****************************************************************************/

static _BOOL xfix_cicon(_UWORD *col_data, _LONG len, _WORD old_planes, _WORD new_planes, MFDB *s)
{
	_LONG x, i, old_len, rest_len, new_len;
	_UWORD np, *new_data, mask, pixel, bit, color, back[XMAX_PLANES];
	MFDB d;
	
	len >>= 1;

	s->fd_nplanes = new_planes;
	if (old_planes == new_planes)
	{
		d = *s;
		d.fd_stand = FALSE;
		s->fd_addr = col_data;
		if ((d.fd_addr = malloc(len * 2 * new_planes)) == NULL)
			d.fd_addr = s->fd_addr;
		
		vr_trnfm(xvdi_handle, s, &d);
		if (d.fd_addr != s->fd_addr)
		{
			memcpy(s->fd_addr, d.fd_addr, len * 2 * new_planes);
			free(d.fd_addr);
		}
		return TRUE;
	}
	
	old_len = old_planes * len;
	new_len = new_planes * len;
	rest_len = new_len - old_len;
	if (new_planes <= 8)
	{
		s->fd_addr = malloc(new_len * 2);
		if (s->fd_addr != NULL)
		{
			new_data = &((_UWORD *)s->fd_addr)[old_len];
			memset(new_data, 0, rest_len * 2);
			memcpy(s->fd_addr, col_data, old_len * 2);

			col_data = (_UWORD *)s->fd_addr;
			
			for (x = 0; x < len; x++)
			{
				mask = 0xffff;
				
				for (i = 0; i < old_len; i += len)
					mask &= col_data[x + i];
				
				if (mask)
					for (i = 0; i < rest_len; i += len)
						new_data[x + i] |= mask;
			}

			/* convert to device dependent format */
			d = *s;
			d.fd_stand = FALSE;
			if ((d.fd_addr = malloc(len * 2 * new_planes)) == NULL)
				d.fd_addr = s->fd_addr;
			
			vr_trnfm(xvdi_handle, s, &d);
			if (d.fd_addr != s->fd_addr)
			{
				memcpy(s->fd_addr, d.fd_addr, len * 2 * new_planes);
				free(d.fd_addr);
			}
		}
	} else
	{
		/* TrueColor */
		if (xpixelbytes == 0)
		{
			s->fd_addr = NULL;
			if (colortbl != NULL)
			{
				_UWORD *plane_ptr[XMAX_PLANES], *pos;
				_UWORD old_col[XMAX_PLANES];
				_UWORD maxcol = 0;
				
				if (old_planes < 8)
				{
					maxcol = (1 << old_planes) - 1;
					memcpy(old_col, &colortbl[maxcol * new_planes], new_planes * sizeof(_WORD));
					memset(&colortbl[maxcol * new_planes], 0, new_planes * sizeof(_WORD));
				}
				
				if ((new_data = (_UWORD *)malloc(len * 2 * new_planes)) != NULL)
				{
					_WORD *colp;
					
					memcpy(new_data, col_data, old_len * 2);
					memset(new_data + old_len, 0, rest_len * 2);
	
					for (i = 0; i < new_planes; i++)
						plane_ptr[i] = &new_data[i * len];
		
					for (x = 0; x < len; x++)
					{
						bit = 1;
						for (np = 0; np < old_planes; np++)
							back[np] = plane_ptr[np][x];
						
						for (pixel = 0; pixel < 16; pixel++)
						{
							color = 0;
							for (np = 0; np < old_planes; np++)
							{
								color += ((back[np] & 1) << np);
								back[np] >>= 1;
							}
							
							colp = &colortbl[color * new_planes];
							for (np = 0; np < new_planes; np++)
							{
								pos = plane_ptr[np] + x;
								*pos = (*pos & ~bit) | (colp[np] & bit);
							}
		
							bit <<= 1;
						}
					}
					if (old_planes < 8)
						memcpy(&colortbl[maxcol * new_planes], old_col, new_planes * sizeof(_WORD));
		
					/* convert to device dependent format */
					d = *s;
					s->fd_addr = new_data;
					d.fd_stand = FALSE;
					if ((d.fd_addr = malloc(len * 2 * new_planes)) == NULL)
						d.fd_addr = s->fd_addr;
					
					vr_trnfm(xvdi_handle, s, &d);
					if (d.fd_addr != s->fd_addr)
					{
						memcpy(s->fd_addr, d.fd_addr, len * 2 * new_planes);
						free(d.fd_addr);
					}
				}
			}
		} else
		{
			std_to_byte(col_data, len, old_planes, colortbl2, s);
		}
	}
	if (s->fd_addr == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void xfix_make_selmask(_WORD w, _WORD h, void *dst, const void *src)
{
	_UWORD mask = 0x5555;
	_WORD x, y;
	_UWORD *d = (_UWORD *)dst;
	const _UWORD *s = (const _UWORD *)src;
	
	w = (w + 15) >> 4;
	for (y = h; --y >= 0;)
	{
		for (x = w; --x >= 0; )
			*d++ = (*s++) & mask;
		mask = ~mask;
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

#if USE_NICELINES

/*** ---------------------------------------------------------------------- ***/

static void rect2pxy(const GRECT *gr, _WORD *pxy, _WORD max_w, _WORD max_h)
{
	xywh2pxy(gr->g_x, gr->g_y, gr->g_w, gr->g_h, pxy, max_w, max_h);
}

/*** ---------------------------------------------------------------------- ***/

static _WORD _CDECL draw_niceline(PARMBLK *pb)
{
	GRECT gr;
	GRECT clip;
	_WORD pxy[4];
	_WORD aes_clip[5];
	
	save_clip(aes_handle, aes_clip);
	set_user_clip(aes_handle, pb);
	
	gr.g_x = pb->pb_x;
	gr.g_y = pb->pb_y + pb->pb_h / 2 - 1;
	gr.g_w = pb->pb_w;
	gr.g_h = 2;
	clip.g_x = pb->pb_xc;
	clip.g_y = pb->pb_yc;
	clip.g_w = pb->pb_wc;
	clip.g_h = pb->pb_hc;
	if (rc_intersect(&clip, &gr))
	{
		_WORD attrib[5];
		_WORD max_w, max_h;
		
		save_fillattr(aes_handle, attrib);
		
		vswr_mode(aes_handle, MD_REPLACE);
		vsf_perimeter(aes_handle, FALSE);
		GetScreenSize(&max_w, &max_h);
		rect2pxy(&gr, pxy, max_w, max_h);
		if (xscrn_planes >= 4)
		{
			vsf_color(aes_handle, G_LBLACK);
			vsf_interior(aes_handle, FIS_SOLID);
			vsf_style(aes_handle, 0);
		} else
		{
			vsf_color(aes_handle, G_BLACK);
			vsf_interior(aes_handle, FIS_PATTERN);
			vsf_style(aes_handle, 4);
		}
		vr_recfl(aes_handle, pxy);
		
		restore_fillattr(aes_handle, attrib);
	}
	restore_clip(aes_handle, aes_clip);
	return OS_NORMAL;
}
#endif

/*** ---------------------------------------------------------------------- ***/

static void draw_small_text(char *text, _WORD *pxy)
{
	_WORD extent[8];
	_WORD textw, texth;
	
	vqt_extent(aes_handle, text, extent);
	textw = extent[2] - extent[0];
	texth = extent[5] - extent[3];
	pxy[0] += (pxy[2] - pxy[0] + 1 - textw) / 2;
	pxy[1] += (pxy[3] - pxy[1] + 1 - texth) / 2;
	v_gtext(aes_handle, pxy[0], pxy[1], text);
}

/*** ---------------------------------------------------------------------- ***/

static void draw_icon_text(ICONBLK *ib, _WORD xpos, _WORD ypos, _WORD selected)
{
	_WORD x, y, w, h;
	_WORD pxy[4];
	_WORD datacol = ICOLSPEC_GET_DATACOL(ib->ib_char);
	_WORD maskcol = ICOLSPEC_GET_MASKCOL(ib->ib_char);
	char c[2];
	_WORD max_w, max_h;
	_WORD dummy;
	_WORD cw, ch;
	_WORD attrib[5];
	_WORD textattrib[10];
	
	save_fillattr(aes_handle, attrib);
	save_textattr(aes_handle, textattrib);

	GetScreenSize(&max_w, &max_h);
	x = xpos + ib->ib_xtext;
	y = ypos + ib->ib_ytext;
	w = ib->ib_wtext;
	h = ib->ib_htext;
	vsf_interior(aes_handle, FIS_SOLID);
	vsf_style(aes_handle, 0);
	vst_height(aes_handle, 4, &dummy, &dummy, &cw, &ch);
	vswr_mode(aes_handle, MD_TRANS);
	if (w > 0 && h > 0 && ib->ib_ptext && *ib->ib_ptext &&
		xywh2pxy(x, y, w, h, pxy, max_w, max_h))
	{
		if (selected)
		{
			vsf_color(aes_handle, datacol);
			if (datacol != G_WHITE)
				vr_recfl(aes_handle, pxy);
			vst_color(aes_handle, maskcol);
			draw_small_text(ib->ib_ptext, pxy);
		} else
		{
			vsf_color(aes_handle, maskcol);
			if (maskcol != G_WHITE)
				vr_recfl(aes_handle, pxy);
			vst_color(aes_handle, datacol);
			draw_small_text(ib->ib_ptext, pxy);
		}
	}
	
	c[0] = ib->ib_char;
	c[1] = 0;
	if (c[0] != 0)
	{
		x = xpos + ib->ib_xicon + ib->ib_xchar;
		y = ypos + ib->ib_yicon + ib->ib_ychar;
		if (xywh2pxy(x, y, cw, ch, pxy, max_w, max_h))
		{
			vst_color(aes_handle, selected ? maskcol : datacol);
			v_gtext(aes_handle, pxy[0], pxy[1], c);
		}
	}

	restore_textattr(aes_handle, textattrib);
	restore_fillattr(aes_handle, attrib);
}

/*** ---------------------------------------------------------------------- ***/

static CICON *cicon_best_match(CICONBLK *cib, _WORD planes)
{
	_WORD best_match = 0;
	CICON *best = NULL;
	CICON *list;
	
	for (list = cib->mainlist; list != NULL; list = list->next_res)
	{
		if (list->num_planes > best_match && list->num_planes <= planes)
		{
			best_match = list->num_planes;
			best = list;
		}
	}
	return best;
}

/*** ---------------------------------------------------------------------- ***/

static _WORD _CDECL draw_cicon(PARMBLK *pb)
{
	MFDB src, dst;
	_WORD pxy[8];
	struct userdef *u = (struct userdef *)pb->pb_parm;
	CICONBLK *ciconblk = u->orig.ob_spec.ciconblk;
	ICONBLK *ib = &ciconblk->monoblk;
	_WORD x = pb->pb_x + ib->ib_xicon;
	_WORD y = pb->pb_y + ib->ib_yicon;
	_WORD w = ib->ib_wicon;
	_WORD h = ib->ib_hicon;
	_WORD datacol = ICOLSPEC_GET_DATACOL(ib->ib_char);
	_WORD maskcol = ICOLSPEC_GET_MASKCOL(ib->ib_char);
	_WORD colind[2];
	_WORD selected = pb->pb_currstate & OS_SELECTED;
	CICON *cicon;
	void *pdata, *pmask;
	_WORD aes_clip[5];
	
	save_clip(aes_handle, aes_clip);
	set_user_clip(aes_handle, pb);
	
	scrfdb(&dst);
	src.fd_w = w;
	src.fd_h = h;
	src.fd_wdwidth = (src.fd_w + 15) >> 4;
	src.fd_stand = TRUE;
	src.fd_nplanes = 1;
	src.fd_r1 = src.fd_r2 = src.fd_r3 = 0;
	if (xywh2pxy(x, y, w, h, &pxy[4], dst.fd_w, dst.fd_h))
	{
		pxy[0] = pxy[4] - x;
		pxy[1] = pxy[5] - y;
		pxy[2] = pxy[6] - x;
		pxy[3] = pxy[7] - y;
		
		cicon = ciconblk->mainlist;
		if (selected)
		{
			if (cicon->sel_data != NULL)
			{
				pmask = cicon->sel_mask;
				pdata = cicon->sel_data;
				selected = FALSE;
			} else
			{
				pmask = cicon->col_mask;
				pdata = cicon->col_data;
	
				/*
				 * for >1 planes, draw selection by darken the image
				 * instead of inverting, if the icon didn't have a mask
				 */
				if (cicon->sel_mask != NULL && cicon->num_planes > 1)
					selected = 2;
			}
		} else
		{
			pmask = cicon->col_mask;
			pdata = cicon->col_data;
		}
		
		src.fd_addr = pmask;
		src.fd_nplanes = 1;
		src.fd_stand = TRUE;
		colind[0] = selected == 1 ? datacol : maskcol;
		colind[1] = G_WHITE;
		vrt_cpyfm(aes_handle, MD_TRANS, pxy, &src, &dst, colind);
		
		src.fd_nplanes = cicon->num_planes;
		if (src.fd_nplanes == 1)
		{
			src.fd_addr = pdata;
			src.fd_stand = TRUE;
			colind[0] = selected ? maskcol : datacol;
			colind[1] = G_WHITE;
			vrt_cpyfm(aes_handle, MD_TRANS, pxy, &src, &dst, colind);
		} else
		{
			_WORD mode;
			
			if (dst.fd_nplanes > 8)
				mode = S_AND_D;
			else
				mode = S_OR_D;
			src.fd_addr = pdata;
			src.fd_stand = FALSE;
			src.fd_nplanes = xscrn_planes;
			vro_cpyfm(aes_handle, mode, pxy, &src, &dst);
			if (selected == 2)
			{
				src.fd_nplanes = 1;
				src.fd_addr = cicon->sel_mask;
				src.fd_stand = TRUE;
				colind[0] = G_BLACK;
				colind[1] = G_WHITE;
				vrt_cpyfm(aes_handle, MD_TRANS, pxy, &src, &dst, colind);
			}
		}
	}
	
	draw_icon_text(ib, pb->pb_x, pb->pb_y, selected);
	
	restore_clip(aes_handle, aes_clip);
	
	return pb->pb_currstate & ~OS_SELECTED;
}

/*** ---------------------------------------------------------------------- ***/

static void release_list(struct userdef_list *list)
{
	OBJECT *tree = list->objects;
	_WORD i;

	for (i = 0; i < list->nuserobjs; i++)
	{
		tree[list->userobjs[i].obj] = list->userobjs[i].orig;
		switch (list->userobjs[i].orig.ob_type & 0xff)
		{
		case G_CICON:
			{
				CICONBLK *ciconblk = list->userobjs[i].orig.ob_spec.ciconblk;
				CICON *cicon;

				cicon = ciconblk->mainlist;
				assert(cicon != NULL);
				if (cicon->num_planes > 1 && cicon->num_planes != xscrn_planes)
				{
					free(cicon->col_data);
					if (cicon->sel_data)
						free(cicon->sel_data);
				}
				if (cicon->num_planes > 1 && cicon->sel_data == NULL)
					free(cicon->sel_mask);
			}
			break;
		}
	}

	if (list->hdr)
	{
		free(list->hdr);
		list->hdr = NULL;
	}
}

/******************************************************************************/
/*** Exported functions                                                     ***/
/******************************************************************************/

/*
 * This function is called by inlined sources
 */
void *hfix_objs(RSHDR *hdr, OBJECT *objects, _WORD num_objs)
{
	_WORD i;
	_WORD num_user;
	_WORD dummy;
	struct userdef_list *list;
	
	aes_handle = graf_handle(&dummy, &dummy, &dummy, &dummy);
	{
		_WORD wo[57];
		vq_extnd(aes_handle, 1, wo);
		xscrn_planes = wo[4];
	}
	if (xpixelbytes < 0)
	{
		xpixelbytes = test_rez();
		std_palette(rgb_palette);
	}
	xfill_colortbl();
	
	num_user = 0;
	for (i = 0; i < num_objs; i++)
	{
		OBJECT *ob = &objects[i];
		
		switch (ob->ob_type & 0xff)
		{
		case G_ICON:
			break;

		case G_CICON:
			{
				CICONBLK *cicon = ob->ob_spec.ciconblk;

				if (cicon_best_match(cicon, xscrn_planes) != NULL)
					++num_user;
			}
			break;

		case G_IMAGE:
			break;

		case G_FTEXT:
		case G_FBOXTEXT:
			break;

		case G_TEXT:
		case G_BOXTEXT:
			break;

		case G_TITLE:
		case G_BUTTON:
			break;

		case G_STRING:
		case G_SHORTCUT:
#if USE_NICELINES
			if ((ob->ob_state & OS_DISABLED) &&
				ob->ob_spec.free_string[0] == '-')
			{
				num_user++;
			}
#endif
			break;
		}
	}

	list = (struct userdef_list *)malloc(sizeof(*list) + (num_user - 1) * sizeof(struct userdef));
	if (list == NULL)
		return NULL;
	list->hdr = hdr;
	list->objects = objects;
	list->nobjs = num_objs;
	list->nuserobjs = num_user;
	list->next = userdefs;
	userdefs = list;

#define adduser(f) \
	list->userobjs[num_user].orig = *ob; \
	list->userobjs[num_user].obj = i; \
	list->userobjs[num_user].user.ub_code = f; \
	list->userobjs[num_user].user.ub_parm = (_LONG)&list->userobjs[num_user]; \
	ob->ob_type = G_USERDEF; \
	ob->ob_spec.userblk = &list->userobjs[num_user].user; \
	num_user++
	
	num_user = 0;
	for (i = 0; i < num_objs; i++)
	{
		OBJECT *ob = &objects[i];
		
		switch (ob->ob_type & 0xff)
		{
		case G_ICON:
			break;

		case G_CICON:
			{
				CICONBLK *ciconblk = ob->ob_spec.ciconblk;
				CICON *cicon;
				MFDB d;
				_LONG len;
				
				cicon = cicon_best_match(ciconblk, xscrn_planes);
				if (cicon != NULL)
				{
					if (cicon->num_planes > 1)
					{
						d.fd_w = ciconblk->monoblk.ib_wicon;
						d.fd_h = ciconblk->monoblk.ib_hicon;
						d.fd_wdwidth = (d.fd_w + 15) >> 4;
						d.fd_stand = TRUE;
						d.fd_nplanes = xscrn_planes;
						len = (_LONG) d.fd_wdwidth * 2l * d.fd_h;
						
						xfix_cicon((_UWORD *)cicon->col_data, len, cicon->num_planes, xscrn_planes, &d);
						cicon->col_data = d.fd_addr;
						if (cicon->sel_data)
						{
							xfix_cicon((_UWORD *)cicon->sel_data, len, cicon->num_planes, xscrn_planes, &d);
							cicon->sel_data = d.fd_addr;
						} else
						{
							/* prepare darken mask */
							cicon->sel_mask = malloc(len);
							if (cicon->sel_mask != NULL)
								xfix_make_selmask(d.fd_w, d.fd_h, cicon->sel_mask, cicon->col_mask);
						}
					}
					ciconblk->mainlist = cicon;
					cicon->next_res = NULL;
					adduser(draw_cicon);
				} else
				{
					ob->ob_spec.iconblk = &ciconblk->monoblk;
					ob->ob_type = (ob->ob_type & 0xff00) | G_ICON;
				}
			}
			break;

		case G_IMAGE:
			break;

		case G_FTEXT:
		case G_FBOXTEXT:
			break;

		case G_TEXT:
		case G_BOXTEXT:
			break;

		case G_TITLE:
		case G_BUTTON:
			break;

		case G_STRING:
		case G_SHORTCUT:
#if USE_NICELINES
			if ((ob->ob_state & OS_DISABLED) &&
				ob->ob_spec.free_string[0] == '-')
			{
				adduser(draw_niceline);
			}
#endif
			break;
		}
	}
	assert(num_user == list->nuserobjs);
#undef adduser

	return list;
}

/*** ---------------------------------------------------------------------- ***/

RSHDR *xrsrc_load(const char *re_lpfname)
{
	return rs_load(re_lpfname);
}

/*** ---------------------------------------------------------------------- ***/

_WORD xrsrc_free(RSHDR *hdr)
{
	struct userdef_list **list, *l;
	
	for (list = &userdefs; (l = *list) != NULL; list = &l->next)
	{
		if (l->hdr == hdr)
		{
			*list = l->next;
			release_list(l);
			free(l);
			return 1;
		}
	}
	return 0;
}

/*** ---------------------------------------------------------------------- ***/

/*
 * xrsrc_gaddr: like rsrc_gaddr(), taking an extra parameter for the resource
 */
_BOOL xrsrc_gaddr(RSHDR *handle, _WORD type, _WORD idx, void *gaddr)
{
	RSXHDR xrsc_header;
	
	if (gaddr == NULL)
		return FALSE;
	*(void **)gaddr = NULL;
	if (handle == NULL)
	{
		return FALSE;
	}
	if (IS_XRSC_HEADER(handle))
	{
		xrsc_header = *((RSXHDR *)handle);
	} else
	{
		xrsrc_hdr2xrsc(&xrsc_header, handle);
	}
	switch (type)
	{
	case R_TREE:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_ntree)
		{
			return FALSE;
		}
		{
			OBJECT **_rs_trindex = (OBJECT **)((char *)handle + (size_t)xrsc_header.rsh_trindex);
			*((OBJECT **)gaddr) = _rs_trindex[idx];
		}
		break;
	case R_OBJECT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nobs)
		{
			return FALSE;
		}
		{
			OBJECT *_rs_object = (OBJECT *)((char *)handle + (size_t)xrsc_header.rsh_object);
			*((OBJECT **)gaddr) = &_rs_object[idx];
		}
		break;
	case R_TEDINFO:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			*((TEDINFO **)gaddr) = &_rs_tedinfo[idx];
		}
		break;
	case R_ICONBLK:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			*((ICONBLK **)gaddr) = &_rs_iconblk[idx];
		}
		break;
	case R_BITBLK:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nbb)
		{
			return FALSE;
		}
		{
			BITBLK *_rs_bitblk = (BITBLK *)((char *)handle + (size_t)xrsc_header.rsh_bitblk);
			*((BITBLK **)gaddr) = &_rs_bitblk[idx];
		}
		break;
	case R_STRING:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nstring)
		{
			return FALSE;
		}
		{
			char **_rs_frstr = (char **)((char *)handle + (size_t)xrsc_header.rsh_frstr);
			*((char **)gaddr) = _rs_frstr[idx];
		}
		break;
	case R_IMAGEDATA:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nimages)
		{
			return FALSE;
		}
		{
			BITBLK **_rs_frimg = (BITBLK **)((char *)handle + (size_t)xrsc_header.rsh_frimg);
			*((BITBLK **)gaddr) = _rs_frimg[idx];
		}
		break;
	case R_OBSPEC:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nobs)
		{
			return FALSE;
		}
		{
			OBJECT *_rs_object = (OBJECT *)((char *)handle + (size_t)xrsc_header.rsh_object);
			*((_LONG **)gaddr) = &_rs_object[idx].ob_spec.index;
		}
		break;
	case R_TEPTEXT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			*((char ***)gaddr) = &_rs_tedinfo[idx].te_ptext;
		}
		break;
	case R_TEPTMPLT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			*((char ***)gaddr) = &_rs_tedinfo[idx].te_ptmplt;
		}
		break;
	case R_TEPVALID:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			*((char ***)gaddr) = &_rs_tedinfo[idx].te_pvalid;
		}
		break;
	case R_IBPMASK:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			*((char ***)gaddr) = (char **)&_rs_iconblk[idx].ib_pmask;
		}
		break;
	case R_IBPDATA:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			*((char ***)gaddr) = (char **)&_rs_iconblk[idx].ib_pdata;
		}
		break;
	case R_IBPTEXT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			*((char ***)gaddr) = &_rs_iconblk[idx].ib_ptext;
		}
		break;
	case R_BIPDATA:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nbb)
		{
			return FALSE;
		}
		{
			BITBLK *_rs_bitblk = (BITBLK *)((char *)handle + (size_t)xrsc_header.rsh_bitblk);
			*((char ***)gaddr) = (char **)&_rs_bitblk[idx].bi_pdata;
		}
		break;
	case R_FRSTR:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nstring)
		{
			return FALSE;
		}
		{
			char **_rs_frstr = (char **)((char *)handle + (size_t)xrsc_header.rsh_frstr);
			*((char ***)gaddr) = &_rs_frstr[idx];
		}
		break;
	case R_FRIMG:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nimages)
		{
			return FALSE;
		}
		{
			BITBLK **_rs_frimg = (BITBLK **)((char *)handle + (size_t)xrsc_header.rsh_frimg);
			*((BITBLK ***)gaddr) = &_rs_frimg[idx];
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

/*
 * xrsrc_gaddr: like rsrc_gaddr(), taking an extra parameter for the resource
 */
_BOOL xrsrc_saddr(RSHDR *handle, _WORD type, _WORD idx, void *saddr)
{
	RSXHDR xrsc_header;
	
	if (handle == NULL)
	{
		return FALSE;
	}
	if (IS_XRSC_HEADER(handle))
	{
		xrsc_header = *((RSXHDR *)handle);
	} else
	{
		xrsrc_hdr2xrsc(&xrsc_header, handle);
	}
	switch (type)
	{
	case R_TREE:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_ntree)
		{
			return FALSE;
		}
		{
			OBJECT **_rs_trindex = (OBJECT **)((char *)handle + (size_t)xrsc_header.rsh_trindex);
			_rs_trindex[idx] = saddr;
		}
		break;

		/*
		 * setting the address of an OBJECT simply does not work;
		 * current AES implementations (including GEM/3) trash the
		 * first 2 WORD of the OBJECT structure
		 */
	case R_OBJECT:
		return FALSE;

		/*
		 * current AES implementations (including GEM/3) set the first
		 * first member of the TEDINFO structure (te_ptext)
		 */
	case R_TEDINFO:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			_rs_tedinfo[idx].te_ptext = saddr;
		}
		break;

		/*
		 * current AES implementations (including GEM/3) set the first
		 * first member of the ICONBLK structure (ib_pmask)
		 */
	case R_ICONBLK:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			_rs_iconblk[idx].ib_pmask = saddr;
		}
		break;
		
		/*
		 * current AES implementations (including GEM/3) set the first
		 * first member of the BITBLK structure (ib_pdata)
		 */
	case R_BITBLK:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nbb)
		{
			return FALSE;
		}
		{
			BITBLK *_rs_bitblk = (BITBLK *)((char *)handle + (size_t)xrsc_header.rsh_bitblk);
			_rs_bitblk[idx].bi_pdata = saddr;
		}
		break;
		
		/*
		 * setting the address of a string simply does not work;
		 * current AES implementations (including GEM/3) trash the
		 * first 4 bytes of the string
		 */
	case R_STRING:
		return FALSE;
		
	case R_IMAGEDATA:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nimages)
		{
			return FALSE;
		}
		{
			BITBLK **_rs_frimg = (BITBLK **)((char *)handle + (size_t)xrsc_header.rsh_frimg);
			_rs_frimg[idx]->bi_pdata = saddr;
		}
		break;
		
	case R_OBSPEC:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nobs)
		{
			return FALSE;
		}
		{
			OBJECT *_rs_object = (OBJECT *)((char *)handle + (size_t)xrsc_header.rsh_object);
			_rs_object[idx].ob_spec.indirect = saddr;
		}
		break;
		
	case R_TEPTEXT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			_rs_tedinfo[idx].te_ptext = saddr;
		}
		break;
		
	case R_TEPTMPLT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			_rs_tedinfo[idx].te_ptmplt = saddr;
		}
		break;
	case R_TEPVALID:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nted)
		{
			return FALSE;
		}
		{
			TEDINFO *_rs_tedinfo = (TEDINFO *)((char *)handle + (size_t)xrsc_header.rsh_tedinfo);
			_rs_tedinfo[idx].te_pvalid = saddr;
		}
		break;
	case R_IBPMASK:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			_rs_iconblk[idx].ib_pmask = saddr;
		}
		break;
	case R_IBPDATA:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			_rs_iconblk[idx].ib_pdata = saddr;
		}
		break;
	case R_IBPTEXT:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nib)
		{
			return FALSE;
		}
		{
			ICONBLK *_rs_iconblk = (ICONBLK *)((char *)handle + (size_t)xrsc_header.rsh_iconblk);
			_rs_iconblk[idx].ib_ptext = saddr;
		}
		break;
	case R_BIPDATA:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nbb)
		{
			return FALSE;
		}
		{
			BITBLK *_rs_bitblk = (BITBLK *)((char *)handle + (size_t)xrsc_header.rsh_bitblk);
			_rs_bitblk[idx].bi_pdata = saddr;
		}
		break;
	case R_FRSTR:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nstring)
		{
			return FALSE;
		}
		{
			char **_rs_frstr = (char **)((char *)handle + (size_t)xrsc_header.rsh_frstr);
			_rs_frstr[idx] = saddr;
		}
		break;
	case R_FRIMG:
		if (idx < 0 || (_ULONG)idx >= xrsc_header.rsh_nimages)
		{
			return FALSE;
		}
		{
			BITBLK **_rs_frimg = (BITBLK **)((char *)handle + (size_t)xrsc_header.rsh_frimg);
			_rs_frimg[idx] = saddr;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

_WORD xrsrc_obfix(OBJECT *re_otree, _WORD re_oobject)
{
	rsc_obfix(&re_otree[re_oobject], 1);

	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

_BOOL init_xrsrc(void)
{
	_WORD dummy;
	
	aes_handle = graf_handle(&dummy, &dummy, &dummy, &dummy);
	{
		_WORD workout[57];
		vq_extnd(aes_handle, 0, workout);
		xscr_w = workout[0] + 1;
		xscr_h = workout[1] + 1;
		vq_extnd(aes_handle, 1, workout);
		xscrn_planes = workout[4];
	}
	std_palette(rgb_palette);
	is_std_palette = TRUE;
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

void term_xrsrc(void)
{
	struct userdef_list *list, *next;
	
	for (list = userdefs; list != NULL; list = next)
	{
		next = list->next;
		release_list(list);
		free(list);
	}
	userdefs = NULL;
	free(colortbl);
	colortbl = NULL;
}
