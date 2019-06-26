/*
 * Template file for C include files
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
 * resource set indices for %n
 *
 * created by ORCS %V
 */

/*
 * Number of Strings:        %s
 * Number of Bitblks:        %B
 * Number of Iconblks:       %I
 * Number of Color Iconblks: %C
 * Number of Color Icons:    %c
 * Number of Tedinfos:       %t
 * Number of Free Strings:   %S
 * Number of Free Images:    %F
 * Number of Objects:        %O
 * Number of Trees:          %T
 * Number of Userblks:       %U
 * Number of Images:         %i
 * Total file size:          %f
 */

#undef RSC_NAME
#ifndef __ALCYON__
#define RSC_NAME "%n"
#endif
#undef RSC_ID
#ifdef %n
#define RSC_ID %n
#else
#define RSC_ID 0
#endif

#ifndef RSC_STATIC_FILE
# define RSC_STATIC_FILE 0
#endif
#if !RSC_STATIC_FILE
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
#endif


%D


#ifdef __STDC__
#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif
extern _WORD %n_rsc_load(void);
extern _WORD %n_rsc_gaddr(_WORD type, _WORD idx, void *gaddr);
extern _WORD %n_rsc_free(void);
#endif
