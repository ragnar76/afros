CC=	gcc
CFLAGS=	-Wall -m68000 -mshort
LIBS= 	-lgem

TARGET=	link2u.prg

link2u.prg:	link2u.c link2u.h
	$(CC) $(CFLAGS) link2u.c -o $(TARGET) $(LIBS)

opt:	link2u.c link2u.h
	$(CC) $(CFLAGS) -O2 link2u.c -o $(TARGET) $(LIBS)
