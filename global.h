/*
 * global.h
 *
 * Copyright 2013 Hongpu Ma
 */

#ifndef _GLOBAL_H
#define _GLOBAL_H

#define MAXN 91286
#define HEAP_SIZE 200

struct expTreeNode {
    char name[4];
    char *data;
};

struct trieNode {
    int index;
    char *word;
    struct trieNode *son[16];
};

struct trieList {
    struct trieNode *key;
    struct trieList *next;
};

struct heapStruct {
    int key,value;
};

extern struct heapStruct *heap[HEAP_SIZE];
extern struct trieList *trielist;
extern char *words[MAXN];
extern struct trieNode trieRoot, *wordsNode[MAXN];
extern struct expTreeNode *expNodeList[2000];
extern int expNodetop;
extern int wordsNum;
extern int heapSize;

#endif
