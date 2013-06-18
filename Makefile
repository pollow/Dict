objects = main.o layout.o lookup.o trie.o med.o parser.o global.o
dict: $(objects)
	gcc -o dict $(objects) -lncurses -lpanel -std=c99

main.o: main.c main.h layout.o trie.o lookup.o med.o global.o
	gcc -c main.c -std=c99

lookup.o: lookup.c lookup.h med.o trie.o global.o
	gcc -c lookup.c -std=c99

trie.o: trie.c trie.h global.o
	gcc -c trie.c -std=c99

parser.o: parser.c parser.h global.o
	gcc -c parser.c -std=c99

layout.o: layout.c layout.h lookup.o global.o
	gcc -c layout.c -std=c99

global.o: global.c global.h
	gcc -c global.c -std=c99

clean:
	rm dict $(objects)
