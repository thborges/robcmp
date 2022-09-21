ALL_LL=$(patsubst %.txt,out/%.ll,$(wildcard *.txt))
ALLOBJS=$(patsubst %.ll,%.o,${ALL_LL})
ALLASM=$(patsubst %.ll,%.s,${ALL_LL})
ALLBIN=$(patsubst %.ll,%,${ALL_LL})

COMPILER_NAME=../robcmp

all: ${ALL_LL} ${ALLASM} ${ALLOBJS} ${ALLBIN}

clean:
	rm -f ${ALLBIN} ${ALLASM} ${ALLOBJS} ${ALL_LL}

out/%.ll : %.txt ${COMPILER_NAME}
	${COMPILER_NAME} -Os $< > $@

%.o : %.ll
	llc $< -o $@ -filetype=obj

%.s : %.ll
	llc  $< -o $@ -filetype=asm

core.o : debug.c
	gcc debug.c -o core.o -c

% : %.s core.o
	gcc core.o $< -o $@ -lncurses

