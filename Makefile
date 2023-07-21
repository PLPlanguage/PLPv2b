P= PLP

CP= bin/IO.c bin/IO.h Compiler.c luasyntax.c luasyntax.h lib.c lib.h cmath.c cmath.h cs50.c cs50.h import Define Type fixconf Makefile

CFLAGS= -O2 -I. -Wall

OBJ= Compiler.o IO.o cmath.o luasyntax.o lib.o cs50.o

LUA= lua

OBJS= $(LUA)/hash.o $(LUA)/inout.o $(LUA)/lex_yy.o $(LUA)/opcode.o $(LUA)/table.o $(LUA)/y_tab.o $(LUA)/iolib.o $(LUA)/mathlib.o $(LUA)/strlib.o

BIN= /usr/bin

T= test.plp 

o= ./out.plp

all:	$P
	
$P:	$(OBJ)
	@cd $(LUA) && $(MAKE)
	$(CC) -o $@ $(OBJ) $(OBJS) -lm
	
install: 
	cp $(CP) $(BIN)
	cp -r $(LUA) $(BIN)
	@cd $(BIN) && $(MAKE)

deinstall:
	@cd $(BIN) && rm -rf $(CP)  $(OBJ) $(LUA) $P
	@cd $(BIN) && rm -rf $(TAR)

clean:
	rm -f $(OBJ) $(LUA)/$(OBJS) $(LUA)/$(LUA)$P $P core core.*

test:
	./$P -c $T
	./$P -o $o
	$o
help:
	@echo "make 	all: Compiles files PLP and LUA"
	@echo "	install: installation files PLP in /bin"
	@echo " 	deinstall: uninstallation files PLP in /bin"
	@echo "	clean: Removes all objects"
	@echo "	test: Test file PLP and LUA"
	@echo "	help: Makefile guide"
	
