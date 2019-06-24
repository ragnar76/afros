**********************************************************************
*  MagiCMac Sound driver  v0.96  *  Didier MEQUIGNON  *  2002 April  *
**********************************************************************

Features:
---------
Emulation of Falcon's XBIOS, there are no matrix like the falcon
in the MacOS system nevertheless it's possible to :
- Play samples in 8/16 bits mono and stereo (with/without D2D).
- Record 16 bits samples in stereo like the Falcon (with/without D2D).
- Select the input source (the current input source when MagiCMac is 
started or the number one).
- Connnect or remove the audio source to the audio output.
- Set the level output on the two channels.
- Set the gain input on the two channels.
- Emulation on the selection of tracks (1 to 4).
- FDI external clock selection compatible. 
- Extended functions added like the GSXB/MilanBlaster drivers,
for example it's possible to choice the true frequency. The bit 5
of the _SND cookie is set. 24/32 bits and mixer are not supported, 
and only Mororola format is supported.

With the CPX, you can change the audio source. 

Special Futures:
----------------
- This driver can runs on Hades ! The output is the YAMAHA or the 
MV16/PSOUND card. In this case audio input functions are removed.
The Timer A of the MFP2 is used.
- This driver can run on Aranym ! The driver use SDL calls inside 
Aranym. Record isn't possible.

Install:
--------
Under MagiCMac, just copy ZMAGXSND.PRG in the AUTO folder and restart 
MagiCMac, you can select the input audio source with the CPX.
Under Hades, if you want the MV16 (on the Ropocop), PSOUND (// port),  
or the YAMAHA (internal) output, you need to select to select the 
audio output with the CPX.
Under Aranym, just copy ZMAGXSND.PRG in the AUTO folder. You need 
Aranym 0.1.7 or more.

Copying:
--------
This program and sources are free.
                               
Problems:
---------
Please contact me: didier.mequignon@wanadoo.fr

List of sound XBIOS functions supported:
----------------------------------------

Locksound()    XBIOS Function 128.
Unlocksound()  XBIOS Function 129.
Soundcmd()     XBIOS Function 130.
Setbuffer()    XBIOS Function 131.
Setmode()      XBIOS Function 132.
Settracks()    XBIOS Function 133.
Setmontracks() XBIOS Function 134.
Setinterrupt() XBIOS Function 135.
Buffoper()     XBIOS Function 136.
Gpio()         XBIOS Function 138. Just used for clock selection.
Devconnect()   XBIOS Function 139.
Sndstatus()    XBIOS Function 140.
Buffptr()      XBIOS Function 141.

Some functions are not 100% compatible with GSXB/MilanBlaster because 
the way under MacOS with sound devices is different.
