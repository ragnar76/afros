/*****************************************************************************/
/*                                                                           */
/* Modul: XRSRC.H                                                            */
/* Datum: 18.02.92                                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef __XRSRC__
#define __XRSRC__

#include <portab.h>

#ifndef _WORD
#define _WORD	WORD
#endif
#ifndef _UWORD
#define _UWORD	UWORD
#endif
#ifndef _LONG
#define _LONG	LONG
#endif
#ifndef _ULONG
#define _ULONG	ULONG
#endif
#ifndef _BOOL
#define _BOOL int
#endif


typedef struct
{
/* 0x00 */	_UWORD  rsh_vrsn;			/* should be 3; bit 2 is used to indicate extended resource format */
/* 0x02 */	_UWORD  rsh_extvrsn;		/* informational only:
                                           'IN' for Interface
                                           'RM' for ResourceMaster
                                           'OR' for ORCS
                                        */
/* 0x04 */	_ULONG  rsh_object;			/* offset to first object */
/* 0x08 */	_ULONG  rsh_tedinfo;		/* offset to TEDINFO structures */
/* 0x0c */	_ULONG  rsh_iconblk;		/* offset to ICONBLK structures */
/* 0x10 */	_ULONG  rsh_bitblk;			/* offset to BITBLK structures */
/* 0x14 */	_ULONG  rsh_frstr;			/* offset to free strings (alert box texts) */
/* 0x18 */	_ULONG  rsh_string;			/* offset to string pool */
/* 0x1c */	_ULONG  rsh_imdata;			/* offset to image data */
/* 0x20 */	_ULONG  rsh_frimg;			/* offset to free images */
/* 0x24 */	_ULONG  rsh_trindex;		/* offset to tree addresses */
/* 0x28 */	_ULONG  rsh_nobs;			/* number of objects */
/* 0x2c */	_ULONG  rsh_ntree;			/* number of trees */
/* 0x30 */	_ULONG  rsh_nted;			/* number of TEDINFOs */
/* 0x34 */	_ULONG  rsh_nib;			/* number of ICONBLKs */
/* 0x38 */	_ULONG  rsh_nbb;			/* number of BITBLKs */
/* 0x3c */	_ULONG  rsh_nstring;		/* number of free strings */
/* 0x40 */	_ULONG  rsh_nimages;		/* number of free images */
/* 0x44 */	_ULONG  rsh_rssize;			/* total bytes in standard resource part */
} RSXHDR;

#define RSC_EXT_FILESIZE	0
#define RSC_EXT_CICONBLK	1
#define RSC_EXT_PALETTE		2
#define RSC_EXT_ENDMARK		3
#define RSC_EXT_SIZE		4	/* number of known extension slots */

#define RSC_VERSION_MASK	0x03
#define RSC_EXT_FLAG		0x04

#define XRSC_VRSN_INTERFACE 0x494e
#define XRSC_VRSN_ORCS      0x4F52
#define XRSC_VRSN_RSM       0x524d


#define IS_XRSC_HEADER(handle) ((((RSXHDR *)(handle))->rsh_vrsn & RSC_VERSION_MASK) == 0x03)

void *hfix_objs(RSHDR *hdr, OBJECT *objects, _WORD num_objs);

RSHDR *xrsrc_load(const char *re_lpfname);
_WORD xrsrc_free(RSHDR *hdr);
_BOOL xrsrc_gaddr(RSHDR *handle, _WORD type, _WORD idx, void *gaddr);
_BOOL xrsrc_saddr(RSHDR *handle, _WORD type, _WORD idx, void *saddr);
_WORD xrsrc_obfix(OBJECT *re_otree, _WORD re_oobject);

_BOOL init_xrsrc(void);
void term_xrsrc(void);

#endif /* __XRSRC__ */
