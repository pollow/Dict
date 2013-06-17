#ifndef _TRIE
#define _TRIE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern struct trieNode {
    int index;
    char *word;
    struct trieNode *son[16];
} root;

extern struct trieList {
    int index;
    char *word;
    struct trieList *next;
};

extern struct trieList *trielist;

void trieNodeInit(struct trieNode *);
struct trieNode *newNode();
void hexConvert(int *, char *);
extern struct trieNode *trieInsert(struct trieNode *, int *, const char *, int);
extern struct trieNode *trieSearch(struct trieNode *, int *);
extern void trieGetList(struct trieNode *, int *);
extern int trieInit();

#endif