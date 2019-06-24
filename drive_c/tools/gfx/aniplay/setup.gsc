<GEMSETUP 0180>

<GLOBAL>
	APP_FILE="ANIPLAY.PRG"
	APP_NAME="Aniplayer"
	APP_VERS="2.23"
	APP_TYPE="MV"

	URL="http://aniplay.atari.org"

	DEF_PATH="ENGLISH\"

	ROOTPATH=FALSE
	SERIALIZE=FALSE
	CALCSIZE=TRUE
	ARCSSIZE=0

	TEXT_BEG="$LOCAL\README.TXT"

	HYP_FILE="ANIPLAY.HYP"
	HYP_PAGE="Setup"
</GLOBAL>

<LOCAL>
	HELP="$LOCAL\ANIPLAY.HYP"
	HREF="$LOCAL\ANIPLAY.REF"
	RSRC="$LOCAL\N_FRENCH.TXT"
	SIZE=133594
</LOCAL>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="Shared Library JPEG"
	BHLP="You must install this file for the JPEG Encoder. You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74)."
	<FILE>
		TYPE=SLB
		TEXT="JPEG library from The Independent JPEG Group's JPEG software"
		NAME="JPEG.SLB"
		PATH="JPEG\JPEG.SLB"
		FCNT=1
		SIZE=212364
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="Shared Library Ogg Vorbis Encoder"
	BHLP="You must install this file for encode Ogg Vorbis files (.OGG). You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74). An FPU is required."
	<FILE>
		TYPE=SLB
		TEXT="Version FPU 68060 for Falcon, TT, Milan, Hades, MagiCMac, etc...VORB_ENC.SLB"
		NAME="VORB_ENC.SLB"
		PATH="VORB_ENC\68060\VORB_ENC.SLB"
		FCNT=1
		SIZE=1063325
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=RADIO
	NAME="-"
	TEXT="Shared Library Ogg Vorbis Decoder"
	BHLP="You must install this file for read Ogg Vorbis files (.OGG). You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74)."
	<FILE>
		TYPE=SLB
		TEXT="Version with integers for MagiCMac, etc..."
		NAME="VORBIS.SLB"
		PATH="VORBIS\IVORBIS\VORBIS.SLB"
		FCNT=1
		SIZE=203404
	</FILE>
	<FILE>
		TYPE=SLB
		TEXT="Version FPU 68060 for Falcon/CT60, Hades, etc..."
		NAME="VORBIS.SLB"
		PATH="VORBIS\68060\VORBIS.SLB"
		FCNT=1
		SIZE=174659
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=RADIO
	NAME="-"
	TEXT="Shared Library avcodec from ffmpeg (DivX3/4/5, Sorenson Video). You must install this file for avcodec codecs. You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74)."
	BHLP="You must install this file for avcodec codecs. You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74)."
	<FILE>
		TYPE=SLB
		TEXT="Version 68020 without FPU"
		NAME="AVCODEC.SLB"
		PATH="AVCODEC\68020\AVCODEC.SLB"
		FCNT=1
		SIZE=1296068
	</FILE>
	<FILE>
		TYPE=SLB
		TEXT="Version FPU 68060 for Falcon, TT, Milan, Hades, MagiCMac, etc...AVCODEC.SLB"
		NAME="AVCODEC.SLB"
		PATH="AVCODEC\68060\AVCODEC.SLB"
		FCNT=1
		SIZE=1106389
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="Shared Library lcd. You must install this file for eiffel LCD displays. You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74)."
	BHLP="You must install this file for avcodec codecs. You system must support Shared Library (MiNT >= 1.15.3 or MagiC 6 or MetaDOS 2.74)."
	<FILE>
		TYPE=SLB
		TEXT="Eiffel LCD displays"
		NAME="LCD.SLB"
		PATH="EIFFEL.LCD\LCD.SLB"
		FCNT=1
		SIZE=2297
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="OLGA Initialisation"
	BHLP="If OLGA is installed on your system, GEM-Setup will add the required tags for Aniplayer in the file 'OLGA.INF'."
	<FILE>
		TYPE=OLGA
		TEXT="Quicktime Movies (MOV)"
		OBJC_NAME="Quicktime Movie (MOV)"
		EXTENSION="MOV"
	</FILE>
	<FILE>
		TYPE=OLGA
		TEXT="Quicktime Movies (QT)"
		OBJC_NAME="Quicktime Movie (QT)"
		EXTENSION="QT"
	</FILE>
	<FILE>
		TYPE=OLGA
		TEXT="Video for Windows (AVI)"
		OBJC_NAME="Video for Windows"
		EXTENSION="AVI"
	</FILE>
	<FILE>
		TYPE=OLGA
		TEXT="Real Media (RM)"
		OBJC_NAME="Real Media"
		EXTENSION="RM"
	</FILE>
	<FILE>
		TYPE=OLGA
		TEXT="MPEG Video (MPG)"
		OBJC_NAME="MPEG Video"
		EXTENSION="MPG"
	</FILE>
	<FILE>
		TYPE=OLGA
		TEXT="Autodesk Animator Movie (FLI)"
		OBJC_NAME="Autodesk Animator"
		EXTENSION="FLI"
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="BubbleGEM"
	BHLP="A system extension for GEM, that enables bubble help. But you have it allready installed ;-)."
	<FILE>
		TYPE=MULTI
		TEXT="BubbleGEM extension"
		NAME="BUBBLE.APP"
		PATH="BUBBLE\BUBBLE.APP"
		FCNT=1
		SIZE=19686
	</FILE>
	<FILE>
		TYPE=CPX
		TEXT="BubbleGEM CPX"
		NAME="BUBBLGEM.CPX"
		PATH="BUBBLE\BUBBLGEM.CPX"
		FCNT=1
		SIZE=7286
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="Sounddriver"
	BHLP="A Sounddriver that allows Aniplayer to play sounds properly under MagiCMac, with the PSound/MV16 audiocard under Hades, or using SDL under Aranym."
	<FILE>
		TYPE=AUTO
		TEXT="PSound Cookie (Hades)"
		NAME="PSOUNDC.PRG"
		PATH="DRIVER\PSOUND\PSOUNDC.PRG"
		FCNT=1
		SIZE=622
	</FILE>
	<FILE>
		TYPE=AUTO
		TEXT="MagiCMac, Hades & Aranym XBIOS Sound Driver"
		REPL="Z_MSND.PRG,SET_FALC.PRG,MACSOUND.PRG,MAGICSND.PRG"
		NAME="ZMAGXSND.PRG"
		PATH="DRIVER\MAGXSND\AUTO\ZMAGXSND.PRG"
		FCNT=1
		SIZE=15384
	</FILE>
	<FILE>
		TYPE=CPX
		TEXT="CPX for MagiCMac & Hades XBIOS Sound Driver"
		REPL="Z_MSND.PRG,SET_FALC.PRG,MACSOUND.PRG,MAGICSND.PRG"
		NAME="MAGXSND.CPX"
		PATH="DRIVER\MAGXSND\CPX\MAGXSND.CPX"
		FCNT=1
		SIZE=2991
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="Synchronize CPX"
	BHLP="Demo for program GEM messages to/from Aniplayer. A CPX module to synchronise Aniplayer with other applications."
	<FILE>
		TYPE=CPX
		TEXT="[]"
		NAME="SYNCHRO.CPX"
		PATH="PROG\SYNCHRO.CPX\SYNCHRO.CPX"
		FCNT=1
		SIZE=9324
	</FILE>
</ENTRY>

<ENTRY>
	TYPE=CHECKBOX
	NAME="-"
	TEXT="Environment MOVIEPLAYER"
	BHLP="Sets the env. variable for Aniplayer."
	<FILE>
		TYPE=ENV
		TEXT="Sets the env. variable MOVIEPLAYER"
		NAME="MOVIEPLAYER"
		PATH="$APP\ANIPLAY.PRG"
	</FILE>
</ENTRY>

