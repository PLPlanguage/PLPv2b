OBJS= hash.o inout.o lex_yy.o opcode.o table.o y_tab.o lua.o iolib.o mathlib.o strlib.o

CFLAGS= -O2 -I.

T= luaPLP

Ts= print.plp

all:	$T
	
$T:	$(OBJS)
	$(CC) -o $@ $(OBJS) -lm
	
clean:  $T
	rm -f $(OBJS) core core.*
	
test:
	./$T $(Ts)

