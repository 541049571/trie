
CFLAGS	=	-g 
LDFLAGS	=	


T	=	trie
O	=	trie.o

all: $T

${T}:${O}
	${CC} -o $@ ${O} ${LDFLAGS}

*.o:*.c
	${CC} -c $<

clean:
	rm -f *.o 

tags:
	ctags *.c *.h


