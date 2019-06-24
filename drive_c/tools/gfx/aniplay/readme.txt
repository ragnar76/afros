Aniplayer V2.22 June 2004:
--------------------------
- Fix measure of video clock with an RGB monitor on a FALCON for 
display without GEM with screen set in 65K colors.
- Fix counter in seconds during reading of an AC3 sound file.
- Fix formats AVI rgb16/24 (Microsoft, thanks to Peter Slegg).
- Add some tests for the CT60, DSP is used only for Mpeg Audio when 
the caches are on.
- Add ID3 tags with special HTML codes.
- Add new True Color video modes on FALCON if the option 'Without GEM'
is checked:
  * VGA 640 x 480 CT60 50 MHz. 
  * SVGA 640 x 400 CT60 40 MHz.   
- New version of the SLB Avcodec, based on the current cvs version: 
MiNT 1.15.3 or MagiC 6 or MetaDOS 2.74 (or more). This is a list of 
new codecs supported: 
  * AVI/MOV files compressed in svq3 (Sorenson Video 3) played.
  * AVI/MOV compressed in h263 played.  
  * MPEG audio reading with video when the DSP is unchecked and a 
    68060 is found.
- QuickTime MP4 reading.
- Add informations about OGG Vorbis file inside the Playlist. 
- Add functions for search text and goto track inside the Playlist 
(popup menu with rigth click).
- With DivX files, inside the display configuration bus, the choice 
for MPEG movies allows to get this display:
  * Normal.
  * One frame by 2. 
  * Jump B-frames.
- SLBs 68060 recompiled with Gcc 3.3, FPU code faster.
- Add cookie test '_MCH' at $50000 for Aranym.
- Aniplayer is now Freeware.

Notes:  - Please read the JPEG, VORBIS, VORB_ENC or AVCODEC directory
------  for more informations about each library.
        - OPENDIVX.SLB is removed of the archive because AVCODEC.SLB can 
        decode divx, if you prefer use OPENDIVX.SLB you must remove 
        AVCODEC.SLB. You can found OPENDIVX.SLB inside this archive:
        http://perso.wanadoo.fr/didierm/files/anipl219.zip
        
If your computer is too slow for the DivX, use a CT60 !!!
http://www.czuba-tech.com/

If you want create CD-Audio from mpeg you must try CD-Writer 2.2 with Aniplayer :
http://www.cyberus.ca/~anodyne/
 
If you have a CENTurbo II and you want remove DSP_IRQ.PRG patch in
your auto-folder, please read ANIPLAY.HYP Questions/answers.



For any questions contact: aniplay@wanadoo.fr

Web: http://aniplay.atari.org

