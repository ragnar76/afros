
 ILABEL TOS.Q

INC EQU ADDQ #1,
DEC EQU SUBQ #1,

MEMVALID EQU $420
RESVALID EQU $426
RESVECTOR EQU $42A
_COOKIE EQU $5A0

DEBUT:MOVE.L 4(SP),A5 ;D‚but de la basepage
 MOVE.L $C(A5),D0
 ADD.L $14(A5),D0
 ADD.L $1C(A5),D0
 ADD.L #256,D0
 SETBLOCK D0,(A5)
 MOVE.L #"PSND",D0
 BSR INIT_COOKIE;cr‚e cookie-jar
 BMI.S \1;erreur
 MOVE.L #"_SND",D0
 BSR GET_COOKIE
 BMI.S \2
 MOVE.L D0,A0
 MOVE.L #1,(A0)
\2:KEEPPROC #0,#FIN-DEBUT+$200;programme r‚sidant
\1:TERM
 RTS

INIT_COOKIE:;nom dans D0.L
;retourne le pointeur sur donn‚e cookie dans D0 ou < 0 si erreur

 MOVEM.L D1-A1/A6,-(SP)
 MOVE.L D0,D7
 BSR GET_COOKIE
 BPL \1;existe d‚ja
 SUB.L A6,A6
 SUPER 1
 TST.L D0
 BMI.S \8;mode superviseur
 SUPER 0
 MOVE.L D0,A6;sauve SSP
\8:MOVE.L _COOKIE,D0
 BEQ \2;le Cookie Jar n'existe pas TOS < 1.6
 MOVE.L D0,A0
 MOVEQ #1,D0;compteur nombre de cookies
\3:TST.L (A0)
  BEQ.S \4;dernier cookie
  ADDQ #8,A0
  INC D0
 BRA.S \3
\4:CMP.L 4(A0),D0
 BCC.S \5;plus de place
 CLR.L 8(A0);id dernier cookie
 MOVE.L 4(A0),12(A0);d‚place data dernier cookie (nombre max de cookie)
 MOVE.L D7,(A0)+;installe nouveau cookie
 MOVE.L A0,D7
 CLR.L (A0);contenu initialis‚ … 0
 BRA \9
\5:MOVE.L 4(A0),D1;taille
 BEQ \10;erreur
 MOVE.L D1,D2
 ASL.L #4,D2;double la taille (en octets)
 MOVE.L D2,D0
 BSR MALLOC_D0
 BMI \10;erreur
 MOVE.L _COOKIE,A0
 MOVE.L D0,A1
 MOVE.L D1,D2
 ADD.L D1,D1
 SUBQ.L #2,D2;recopie
 BMI.S \7
\6:MOVE.L (A0)+,(A1)+;id
  MOVE.L (A0)+,(A1)+;contenu
 SUBQ.L #1,D2
 BPL.S \6
 BRA.S \7
\2:MOVEQ #64,D0
 BSR MALLOC_D0;r‚serve la place pour 8 cookie si le Cookie Jar n'existe pas
 BMI.S \10;erreur
 MOVE.L D0,_COOKIE
 LEA DET_RESET,A0
 MOVE.L RESVECTOR,-4(A0)
 MOVE.L RESVALID,SAUVE_RESVALID
 MOVE.L A0,RESVECTOR;d‚tourne reset pour raz vecteur Cookie Jar
 MOVE.L #$31415926,RESVALID
 MOVE.L D0,A1
 MOVEQ #8,D1
\7:MOVE.L D7,(A1)+;installe nouveau cookie
 MOVE.L A1,D7
 CLR.L (A1)+;contenu initialis‚ … 0
 CLR.L (A1)+;id dernier cookie
 MOVE.L D1,(A1);taille
 BRA.S \9
\10:MOVEQ #-1,D7;erreur
\9:MOVE.L A6,D0
 BEQ.S \11
 SUPER (A6)
\11:MOVE.L D7,D0
\1:MOVEM.L (SP)+,D1-A1/A6
 RTS

GET_COOKIE:;nom dans D0.L, au retour si < 0 pas de cookie
;retourne le pointeur sur donn‚e cookie dans D0

 MOVEM.L D1-A1/A6,-(SP)
 MOVE.L D0,D6
 SUB.L A6,A6
 SUPER 1
 TST.L D0
 BMI.S \5;mode superviseur
 SUPER 0
 MOVE.L D0,A6;sauve SSP
\5:MOVEQ #0,D7
 MOVE.L _COOKIE,D0
 BEQ.S \1
 MOVE.L D0,A0
\2:TST.L (A0)
  BEQ.S \1
  CMP.L (A0),D6
  BNE.S \3
  MOVE.L A0,D7
  ADDQ #4,D7
  BRA.S \1
\3:ADDQ #8,A0
 BRA.S \2
\1:MOVE.L A6,D0
 BEQ.S \4
 SUPER (A6)
\4:MOVEQ #-1,D6
 MOVE.L D7,D0
 BEQ.S \6
 MOVEQ #0,D6
\6:TST D6
 MOVEM.L (SP)+,D1-A1/A6
 RTS

 DC.L "XBRA"
 DC.L "PSND"
 DC.L 0;adresse de retour

DET_RESET:

 CLR.L _COOKIE;vecteur Cookie Jar
 MOVE.L SAUVE_RESVALID,RESVALID
 MOVE.L DET_RESET-4,RESVECTOR
 JMP (A6)

MALLOC_D0:

 MOVE.L A0,-(SP)
 MOVE.L D0,-(SP)
 MALLOC #-1
 MOVE.L (SP)+,A0
 CMP.L D0,A0
 BCS.S \1
\3:MOVEQ #-39,D0
 BRA.S \2
\1:MALLOC A0
 TST.L D0
 BLE.S \3
\2:MOVE.L (SP)+,A0
 TST.L D0
 RTS

 BSS
SAUVE_RESVALID:DS.L 1

FIN:
 END
