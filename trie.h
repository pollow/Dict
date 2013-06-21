/*
 * trie.h
 *
 * Copyright 2013 Hongpu Ma
 */

#ifndef _TRIE_H
#define _TRIE_H

#include "global.h"

extern void trieGetList(struct trieNode *, int *);
extern void trieInit();
extern void emptyTrieList();
extern void hexConvert(int *, char *);
extern struct trieNode *trieInsert(struct trieNode *, int *, int);
extern struct trieNode *trieSearch(struct trieNode *, int *);

#endif
