;
; Template file for Assembler-sourcecode-output
; 
; ORCS version 2.16 11.12.2017
; 
; %N will be replaced by the RSC filename (without path)
; %n will be replaced by the RSC filename
;    (in lowercase and without .rsc extension)
; %R will be replaced by the RSC filename
;    (according to namerules and without .rsc extension)
; %h will be replaced by the extension of include files
; %d marks the place where the actual data is written
; %D will output the definitions of the object names
; 
; %s: Number of all strings
; %S: Number of free strings
; %U: Number of USERDEFs
; %i: Number of all images
; %B: Number of BITBLKs
; %F: Number of free images
; %I: Number of ICONBLKs
; %C: Number of CICONBLKs
; %c: Number of CICONs
; %t: Number of TEDINFOs
; %O: Number of OBJECTs
; %T: Number of TREEs
; %%: the '%'-character
; 
; The first line of output is after %BEGIN%
; 

%BEGIN%
;
; GEM resource assembler output of %n
;
; created by ORCS %V
;

%D

	.data

%d

rs_nstrings  equ %s ; total number of strings
rs_nuser     equ %U ; total number of USERBLKs
rs_nfrstr    equ %S ; number of free strings
rs_nimages   equ %i ; total number of images
rs_nbb       equ %B ; number of BITBLKs
rs_nfrimg    equ %F ; number of free images
rs_nib       equ %I ; number of ICONBLKs
rs_ncib      equ %C ; number of CICONBLKs
rs_nted      equ %t ; number of TEDINFOs
rs_nobs      equ %O ; total number of OBJECTs
rs_ntree     equ %T ; number of OBJECT trees

_rsc_format  equ 2 ; RSC_FORM_SOURCE2

rs_name: dc.b "%N",0
