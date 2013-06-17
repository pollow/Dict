#ifndef _MAIN
#define _MAIN

#include "layout.h"
#include "trie.h"
#include "lookup.h"
#include "med.h"

extern char *words[MAXN];
extern struct trieNode wordsNode[MAXN];

void readWords();
int init();
int main();

#endif