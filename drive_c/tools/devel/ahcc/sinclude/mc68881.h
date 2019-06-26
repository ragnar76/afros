MC68881		equ	0xfa40

COMMAND		equ	0x0a
OPERAND		equ	0x10
RESTORE		equ	0x06
BIZY		equ	0x8900

sf0		equ	0x0000;		floating point source registers
sf1		equ	0x0400;		B12,B11,B10 -- B14=0
sf2		equ	0x0800
sf3		equ	0x0c00
sf4		equ	0x1000
sf5		equ	0x1400
sf6		equ	0x1800
sf7		equ	0x1c00

f0		equ	0x0000;		floating point destination registers
f1		equ	0x0080;		B9,B8,B7
f2		equ	0x0100
f3		equ	0x0180
f4		equ	0x0200
f5		equ	0x0280
f6		equ	0x0300
f7		equ	0x0380

L		equ	0x4000;		operand sizes indien geen! src fp reg gegeven
S		equ	0x4400;		dus: memory to fp reg operations
X		equ	0x4800;		B12,B11,B10 -- B14=1
P		equ	0x4c00
W		equ	0x5000
D		equ	0x5400
B		equ	0x5800
__S__	equ	0x5c00


TO		equ	0x0000;		richting: B13 -- 0=naar floating point reg
FROM	equ	0x2000;		                 1=naar memory
FR		equ	FROM

MOVE	equ	0x0000;		operation codes (B6-B0)
ADD		equ	0x0022
SUB		equ	0x0028
MUL		equ	0x0023
DIV		equ	0x0020
MOD		equ	0x0021
REM		equ	0x0025

ABS		equ	0x0018
ACOS	equ	0x001c
ASIN	equ	0x000c
ATAN	equ	0x000a
ATANH	equ	0x000d
CMP		equ	0x0038
COS		equ	0x001d
COSH	equ	0x0019
EXP		equ	0x0010
ETOX	equ	EXP
EXPM1	equ	0x0008
ETOXM1	equ	EXPM1
GETEXP	equ	0x001e
GETMAN	equ	0x001f
INT		equ	0x0001
INTRZ	equ	0x0003
LOGN	equ	0x0014
LOG		equ	LOGN
LOGNP1	equ	0x0006
LOGPM1	equ	LOGNP1
LOG2	equ	0x0016
LOG10	equ	0x0015
NEG		equ	0x001a
SCALE	equ	0x0026
SGLDIV	equ	0x0024
SGLMUL	equ	0x0027
SIN		equ	0x000e
SINCOS	equ	0x0030
SINH	equ	0x0002
SQRT	equ	0x0004
TAN		equ	0x000f
TANH	equ	0x0009
TENTOX	equ	0x0012
EXP10	equ	TENTOX
TEST	equ	0x003a
TWOTOX	equ	0x0011
EXP2	equ	TWOTOX

MACRO 	tak
		tst.b	(a2)
		beq.b	*-2
ENDM
MACRO	tok
		cmpi	#BIZY,-1(a2)
		beq.b	*-6
ENDM
MACRO	fcpres
		move.L	a2,-(sp)
		move	#MC68881+1,a2
		move	#0,RESTORE-1(a2)
ENDM
MACRO	fcp		code
		move	code,COMMAND-1(a2)
		tok
ENDM
MACRO	fp		code
		move	code,(a3)
		tok
ENDM