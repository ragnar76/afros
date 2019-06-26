REM
REM Template file for Basic include files
REM 
REM ORCS version 2.16 11.12.2017
REM 
REM %N will be replaced by the RSC filename (without path)
REM %n will be replaced by the RSC filename
REM    (in lowercase and without .rsc extension)
REM %R will be replaced by the RSC filename
REM    (according to namerules and without .rsc extension)
REM %h will be replaced by the extension of include files
REM %d marks the place where the actual data is written
REM %D will output the definitions of the object names
REM 
REM %s: Number of all strings
REM %S: Number of free strings
REM %U: Number of USERDEFs
REM %i: Number of all images
REM %B: Number of BITBLKs
REM %F: Number of free images
REM %I: Number of ICONBLKs
REM %C: Number of CICONBLKs
REM %c: Number of CICONs
REM %t: Number of TEDINFOs
REM %O: Number of OBJECTs
REM %T: Number of TREEs
REM %%: the '%'-character
REM 
REM The first line of output is after %BEGIN%
REM

%BEGIN%
REM
REM resource set indices for %n
REM
REM created by ORCS %V
REM
%D