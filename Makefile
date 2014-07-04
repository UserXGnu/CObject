CC=gcc
LIBS=Scanner.* String.* Out.*
SLIB=String.o Scanner.o Out.o Stream.*
OBJ=Scanner.o String.o Out.o Stream.o
DOTC=String.c Scanner.c Out.c
STREAM=stream.c
TRASH=*.*.gch
MAIN=main.c
LFLAG=-c
FLAG=-o
EXEC=Scanner
PIC= -Wall -Werror -fpic
SHARED=-shared
SHARED_LIBS=libstring.so libscanner.so libout.so libstream.so
INSTALL_DIR=/usr/lib
PERM=chmod 0755

c.o:all

shared:
	$(CC) $(LFLAG) $(PIC) $(DOTC)
	$(CC) $(LFLAG) $(PIC) $(SLIB)
	$(CC) $(SHARED) $(FLAG) libstring.so String.o
	$(CC) $(SHARED) $(FLAG) libscanner.so Scanner.o
	$(CC) $(SHARED) $(FLAG) libout.so Out.o
	$(CC) $(SHARED) $(FLAG) libstream.so Stream.o
	
libs:
	$(CC) $(LIBS) $(LFLAG)
	$(CC) $(SLIB) $(LFLAG)
	rm -f $(TRASH)

clean:
	rm -f $(OBJ) $(TRASH) $(EXEC)

all:libs
	$(CC) $(OBJ) $(MAIN) $(FLAG) $(EXEC)
	rm -f *.o
	

