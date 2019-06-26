c
c     Template file for fortran include files
c     
c     ORCS version 2.16 11.12.2017
c     
c     %N will be replaced by the RSC filename (without path)
c     %n will be replaced by the RSC filename
c        (in lowercase and without .rsc extension)
c     %R will be replaced by the RSC filename
c        (according to namerules and without .rsc extension)
c     %h will be replaced by the extension of include files
c     %d marks the place where the actual data is written
c     %D will output the definitions of the object names
c     
c     %s: Number of all strings
c     %S: Number of free strings
c     %U: Number of USERDEFs
c     %i: Number of all images
c     %B: Number of BITBLKs
c     %F: Number of free images
c     %I: Number of ICONBLKs
c     %C: Number of CICONBLKs
c     %c: Number of CICONs
c     %t: Number of TEDINFOs
c     %O: Number of OBJECTs
c     %T: Number of TREEs
c     %%: the '%'-character
c     
c     The first line of output is after %BEGIN%
c

%BEGIN%
c
c     resource set indices for %n
c
c     created by ORCS %V
c
%D