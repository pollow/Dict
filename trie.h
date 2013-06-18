#ifndef _TRIE_H
#define _TRIE_H

#include "global.h"

void trieNodeInit(struct trieNode *);
extern void trieGetList(struct trieNode *, int *);
extern void trieInit();
struct trieNode *newNode();
void hexConvert(int *, char *);
extern struct trieNode *trieInsert(struct trieNode *, int *, const char *, int);
extern struct trieNode *trieSearch(struct trieNode *, int *);

#endif
