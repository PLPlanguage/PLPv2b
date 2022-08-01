P= PLP

CP= bin/IO.c Compiler.c luasyntax.c luasyntax.h lib.c lib.h IO.h cmath.c cmath.h cs50.c cs50.h import Define Type fixconf Makefile

CFLAGS= -O2 -I. -Wall

OBJ= Compiler.o IO.o cmath.o luasyntax.o lib.o cs50.o

INTERPRETER = interpreter

OBJS= $(INTERPRETER)/hash.o $(INTERPRETER)/inout.o $(INTERPRETER)/lex_yy.o $(INTERPRETER)/opcode.o $(INTERPRETER)/table.o $(INTERPRETER)/y_tab.o $(INTERPRETER)/iolib.o $(INTERPRETER)/mathlib.o $(INTERPRETER)/strlib.o

BIN= /usr/bin

T= test.plp 

o= ./out.plp

all:	$P
	
$P:	$(OBJ)
	@cd $(INTERPRETER) && $(MAKE)
	$(CC) -o $@ $(OBJ) $(OBJS) -lm
	
install: 
	cp $(CP) $(BIN)
	cp -r $(INTERPRETER) $(BIN)
	@cd $(BIN) && $(MAKE)

deinstall:
	@cd $(BIN) && rm -rf $(CP)  $(OBJ) $(INTERPRETER) $P
	@cd $(BIN) && rm -rf $(TAR)

clean:
	rm -f $(OBJ) $(OBJS) $(INTERPRETER)/lua$P $P core core.*

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
	
