/*
 * Template file for RC-sourcecode-output
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
 * GEM resource RC output of %n
 *
 * created by ORCS %V
 */

#include <windows.h>
#include "%n.rh"

#define DIALOG_FONT 8, "MS Sans Serif"

#define ALERT DIALOG
#define ALERT_SYM_BASE 1000

#define MENU_HELP_BASE 1000


#ifndef WS_OVERLAPPED
#  define WS_OVERLAPPED 0
#endif
#ifndef DS_3DLOOK
#  define DS_3DLOOK 0x04
#endif


%d

