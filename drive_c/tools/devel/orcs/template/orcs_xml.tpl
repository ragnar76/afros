<-- 
    Template file for xml files
    
    ORCS version 2.16 11.12.2017
    
    %N will be replaced by the RSC filename (without path)
    %n will be replaced by the RSC filename
       (in lowercase and without .rsc extension)
    %R will be replaced by the RSC filename
       (according to namerules and without .rsc extension)
    %h will be replaced by the extension of include files
    %d marks the place where the actual data is written
    %D will output the definitions of the object names
    
    %s: Number of all strings
    %S: Number of free strings
    %U: Number of USERDEFs
    %i: Number of all images
    %B: Number of BITBLKs
    %F: Number of free images
    %I: Number of ICONBLKs
    %C: Number of CICONBLKs
    %c: Number of CICONs
    %t: Number of TEDINFOs
    %O: Number of OBJECTs
    %T: Number of TREEs
    %%: the '%'-character
    
    The first line of output is after %BEGIN%
 -->

%BEGIN%
<?xml version="1.0" encoding="utf-8" ?>
<!DOCTYPE rscfile SYSTEM "http://www.tho-otto.de/dtd/resource.dtd" [
<!ENTITY nul "&#9216;">              <!-- 0x00 U+2400 -->
<!ENTITY uparrow "&#8679;">          <!-- 0x01 U+21E7 -->
<!ENTITY downarrow "&#8681;">        <!-- 0x02 U+21E9 -->
<!ENTITY rightarrow "&#8680;">       <!-- 0x03 U+21E8 -->
<!ENTITY leftarrow "&#8678;">        <!-- 0x04 U+21E6 -->
<!ENTITY ballotbox "&#9744;">        <!-- 0x05 U+2610 -->
<!ENTITY ballotboxcheck "&#9745;">   <!-- 0x06 U+2611 -->
<!ENTITY ballotboxx "&#9746;">       <!-- 0x07 U+2612 -->
<!ENTITY checkmark "&#10003;">       <!-- 0x08 U+2713 -->
<!ENTITY watch "&#8986;">            <!-- 0x09 U+231A -->
<!ENTITY bell "&#9086;">             <!-- 0x0a U+237E -->
<!ENTITY br "<br/>">                 <!-- 0x0a        -->
<!ENTITY eightnote "&#9834;">        <!-- 0x0b U+266a -->
<!ENTITY ff "&#9228;">               <!-- 0x0c U+240c -->
<!ENTITY cr "&#9229;">               <!-- 0x0d U+240d -->
<!ENTITY mountain "&#9968;">         <!-- 0x0e U+26f0 -->
<!ENTITY umbrella "&#9969;">         <!-- 0x0f U+26f1 -->
<!ENTITY circledzero "&#9450;">      <!-- 0x10 U+24ea -->
<!ENTITY circledone "&#9312;">       <!-- 0x11 U+2460 -->
<!ENTITY circledtwo "&#9313;">       <!-- 0x12 U+2461 -->
<!ENTITY circledthree "&#9314;">     <!-- 0x13 U+2462 -->
<!ENTITY circledfour "&#9315;">      <!-- 0x14 U+2463 -->
<!ENTITY circledfive "&#9316;">      <!-- 0x15 U+2464 -->
<!ENTITY circledsix "&#9317;">       <!-- 0x16 U+2465 -->
<!ENTITY circledseven "&#9318;">     <!-- 0x17 U+2466 -->
<!ENTITY circledeight "&#9319;">     <!-- 0x18 U+2467 -->
<!ENTITY circlednine "&#9320;">      <!-- 0x19 U+2468 -->
<!ENTITY capitalschwa "&#399;">      <!-- 0x1a U+018f -->
<!ENTITY esc "&#9243;">              <!-- 0x1b U+241b -->
<!ENTITY fountain "&#9970;">         <!-- 0x1c U+26f2 -->
<!ENTITY flaginhole "&#9971;">       <!-- 0x1d U+26f3 -->
<!ENTITY ferry "&#9972;">            <!-- 0x1e U+26f4 -->
<!ENTITY sailboat "&#9973;">         <!-- 0x1f U+26f5 -->
<!ENTITY del "&#9249;">              <!-- 0x7f U+2421 -->
<!ENTITY increment "&#8710;">        <!-- 0x7f U+2206 -->
]>
<!-- created by ORCS %V -->


<rscfile name="%N" generator="ORCS" version="%V">
%d</rscfile>

