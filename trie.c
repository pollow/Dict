/*
 * trie.c
 *
 * Word Tree
 *
 * Copyright 2013 Chang Xing
 */

#include "trie.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void trieNodeInit(struct trieNode *a) {
    a->index = -1;
    a->word = NULL;
    memset(a->son,0, sizeof(a->son));
}

struct trieNode *newNode() {
    struct trieNode *tmp = (struct trieNode *)malloc(sizeof(struct trieNode));
    trieNodeInit(tmp);
    return tmp;
}

void hexConvert(int *a, char *b) {
    for (int i = 0; i < (int)strlen(b); i++) {
        a[i*2] = b[i]/16;
        a[i*2+1] = b[i]%16;
    }
    a[strlen(b)*2] = -1;
}

struct trieNode *trieInsert(struct trieNode *u, int *q, const int index) {
    while (*q != -1) {
        if(u->son[*q] == NULL) u->son[*q] = newNode();
        u = u->son[*q];
        q++;
    }
    u->index = index;
    u->word = words[index];
    return u;
}

struct trieNode *trieSearch(struct trieNode *u, int *ch) {
    if(*ch == -1) {
        return u;
    } else {
        if(u->son[*ch] == NULL) {
            return NULL;
        } else {
            return trieSearch(u->son[*ch],ch+1);
        }
    }
}

void delTrieList(struct trieList *u) {
    if(u == NULL) {
        return;
    } else {
        delTrieList(u->next);
        free(u);
    }
}

void emptyTrieList() {
    delTrieList(trielist);
    trielist = NULL;
}

void trieGetList(struct trieNode *u, int *num) {
    if(u->index != -1) {
        struct trieList *tmp = (struct trieList *) malloc(sizeof(struct trieList));    
        tmp->key = u;
        tmp->next = trielist;
        trielist = tmp;
        (*num)--;
        if(!*num) return;
    }
    for(int i=0;i<16;i++) {
            if(u->son[i] && *num) trieGetList(u->son[i],num);
    }
}

void trieInit() {
    int hexStr[200];
    for(int i=0;i<MAXN;i++) {
        if(words[i] == NULL) {
            continue;
        }
        hexConvert(hexStr,words[i]);
        wordsNode[i] = trieInsert(&trieRoot,hexStr,i);
    }
}
