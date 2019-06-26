(*
 * Template file for Pascal-sourcecode-output
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
 *)

%BEGIN%
(*
 * Pascal Source output of %n
 *
 * created by ORCS %V
 *)

CONST
%D
(*** constants **********)

	NUM_BB	= %B;
	NUM_IB	= %I;
	NUM_CIB	= %C;
	NUM_CIC	= %c;
	NUM_TI	= %t;
	NUM_UD	= %U;
	NUM_FRSTR = %S;
	NUM_FRIMG = %F;
	NUM_OBS	= %O;
	NUM_TREE	= %T;

(** names ***************)

	FLAGS9  =   $0200;
	FLAGS10 =   $0400;
	FLAGS11 =   $0800;
	FLAGS12 =   $1000;
	FLAGS13 =   $2000;
	FLAGS14 =   $4000;
	FLAGS15 =   $8000;
	FL3DIND =   $0200;
	FL3DBAK =   $0400;
	FL3DACT =   $0600;

	STATE8  =   $0100;
	STATE9  =   $0200;
	STATE10 =   $0400;
	STATE11 =   $0800;
	STATE12 =   $1000;
	STATE13 =   $2000;
	STATE14 =   $4000;
	STATE15 =   $8000;

(** data ***************)

%d
	obfixed:	BOOLEAN = FALSE;

