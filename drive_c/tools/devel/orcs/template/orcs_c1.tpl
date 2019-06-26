/*
 * Template file for C-sourcecode-output
 * (old format, Atari RCS compatible)
 * 
 * ORCS version 2.16 11.12.2017
 * 
 * %N will be replaced by the RSC filename (without path)
 * %n will be replaced by the RSC filename
 *    (in lowercase and without .rsc extension)
 * %R will be replaced by the RSC filename
 *    (according to namerules and without .rsc extension)
 * %h will be replaced by the extension of include files
 * %d marks the place where the actual data is written
 * %D will output the definitions of the object names
 * 
 * %s: Number of all strings
 * %S: Number of free strings
 * %U: Number of USERDEFs
 * %i: Number of all images
 * %B: Number of BITBLKs
 * %F: Number of free images
 * %I: Number of ICONBLKs
 * %C: Number of CICONBLKs
 * %c: Number of CICONs
 * %t: Number of TEDINFOs
 * %O: Number of OBJECTs
 * %T: Number of TREEs
 * %%: the '%'-character
 * 
 * The first line of output is after %BEGIN%
 */

%BEGIN%
/*
 * GEM resource C output of %n
 *
 * created by ORCS %V
 */

#ifndef _LONG_PTR
#  define _LONG_PTR LONG
#endif

#ifndef OS_WHITEBAK
#  define OS_WHITEBAK 0x0040
#endif
#ifndef WHITEBAK
#  define WHITEBAK OS_WHITEBAK
#endif
#ifndef OS_DRAW3D
#  define OS_DRAW3D 0x0080
#endif
#ifndef DRAW3D
#  define DRAW3D OS_DRAW3D
#endif
#ifndef OF_FL3DIND
#  define OF_FL3DIND 0x0200
#endif
#ifndef FL3DIND
#  define FL3DIND OF_FL3DIND
#endif
#ifndef OF_FL3DBAK
#  define OF_FL3DBAK 0x0400
#endif
#ifndef FL3DBAK
#  define FL3DBAK OF_FL3DBAK
#endif
#ifndef OF_FL3DACT
#  define OF_FL3DACT 0x0600
#endif
#ifndef FL3DACT
#  define FL3DACT OF_FL3DACT
#endif
#ifndef G_SWBUTTON
#  define G_SWBUTTON 34
#endif
#ifndef G_POPUP
#  define G_POPUP 35
#endif
#ifndef G_EDIT
#  define G_EDIT 37
#endif
#ifndef G_SHORTCUT
#  define G_SHORTCUT 38
#endif
#ifndef G_SLIST
#  define G_SLIST 39
#endif
#ifndef G_EXTBOX
#  define G_EXTBOX 40
#endif
#ifndef G_OBLINK
#  define G_OBLINK 41
#endif

%d

#define NUM_STRINGS %s
#define NUM_FRSTR %S
#define NUM_UD %U
#define NUM_IMAGES %i
#define NUM_BB %B
#define NUM_FRIMG %F
#define NUM_IB %I
#define NUM_CIB %C
#define NUM_TI %t
#define NUM_OBS %O
#define NUM_TREE %T

BYTE pname[] = "%N";

WORD rs_numstrings = NUM_STRINGS;
WORD rs_nuser = NUM_UD;
WORD rs_numfrstr = NUM_FRSTR;
WORD rs_numimages = NUM_IMAGES;
WORD rs_numbb = NUM_BB;
WORD rs_numfrimg = NUM_FRIMG;
WORD rs_numib = NUM_IB;
WORD rs_numcib = NUM_CIB;
WORD rs_numti = NUM_TI;
WORD rs_numobs = NUM_OBS;
WORD rs_numtree = NUM_TREE;

WORD _rsc_format = 1; /* RSC_FORM_SOURCE1 */
