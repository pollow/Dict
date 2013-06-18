//  Created by 邢 畅 on 13-5-12.
//  Copyright (c) 2013年 邢 畅. All rights reserved.
//  Bugs:
//		有一点奇怪的词汇会导致崩溃。共同特点是比较长，但并不是最长的那些。有些奇怪，删掉后正常运行。这些词可以用diff对比备份文件查看。
//		在Linux下运行会崩溃。不知道为什么。Windows下运行不稳定。明明都是简单代码。
//

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
    int breaknum = 0;
    for(int i=0;i<MAXN;i++) {
        if(words[i] == NULL) {
            continue;
        }
        hexConvert(hexStr,words[i]);
        wordsNode[i] = trieInsert(&trieRoot,hexStr,i);
    }
}
