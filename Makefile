objects = main.o layout.o lookup.o trie.o med.o parser.o global.o

all: $(objects)
	gcc -o dict $(objects) -lncurses -lpanel -lm -std=c99

%.o : %.c
	gcc -c $< -o $@ -std=c99

main.c: main.h layout.h trie.h lookup.h med.h global.h

lookup.c: lookup.h med.h trie.h global.h

trie.c: trie.h global.h

parser.c: parser.h global.h

layout.c: layout.h lookup.h global.h parser.h

med.c: med.h global.h

global.c: global.h

clean:
	rm -rf dict $(objects)
