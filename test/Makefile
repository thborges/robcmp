ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALLOBJS=$(patsubst %.ll,%.o,${ALL_LL})
ALLASM=$(patsubst %.ll,%.s,${ALL_LL})
ALLBIN=$(patsubst %.ll,%,${ALL_LL})

COMPILER_NAME=../robcmp

all: ${ALL_LL} ${ALLASM} ${ALLOBJS} ${ALLBIN}

clean:
	rm -f ${ALLBIN} ${ALLASM} ${ALLOBJS} ${ALL_LL}

out/%.ll : %.rob ${COMPILER_NAME}
	${COMPILER_NAME} -Os $< > $@

%.o : %.ll
	llc $< -o $@ -filetype=obj

%.s : %.ll
	llc  $< -o $@ -filetype=asm

core.o : debug.c
	clang debug.c -o core.o -c

% : %.s core.o
	clang core.o $< -o $@ -lncurses

