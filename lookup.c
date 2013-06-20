/*
 * lookup.c
 *
 * Copyright 2013 Chang Xing
 */

#include "lookup.h"
#include "med.h"
#include "trie.h"
#include "global.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int trieValid(char *str) {
    for (int i = 0; i <= (int)strlen(str); i++) {
        if(str[i] == '*' || str[i] == '?') {
            return -1;
        }
    }
    return 1;
}

bool isCapable(char *a, char *b) {
    int j = 0;
    for (int i = 0; i <= (int)strlen(a); i++) {
        if(a[i] != '*' && a[i] != '?') {
            if(a[i] != b[j]) return false;
            j++;
        } else if(a[i] == '*') {
            j++;
        } else if(a[i] == '?') {
            for (int k = j; k <= (int)strlen(b); k++) {
                if (isCapable(a+(i+1),b+k)) return true;
            }
            return false;
        }
    }
    if (j == (int)strlen(b) + 1) return true;
    else return false;
}

void travel(char *str,int num) {
// 处理一下连续问号的情况。
    for (int i = 0; i <= MAXN; i++) {
        if (isCapable(str, words[i])) {
            num--;
            struct trieList *tmp = (struct trieList *) malloc(sizeof(struct trieList));
            tmp->next = trielist;
            tmp->key = wordsNode[i];
            trielist = tmp;
        }
        if (!num) break;
    }
}

int lookupProcess(char *str) {
    int hexStr[200];

    trielist = NULL;

    if (trieValid(str) == -1) {
        travel(str,wordsNum);
    } else {
        hexConvert(hexStr, str);
        struct trieNode *final = trieSearch(&trieRoot, hexStr);
        if(final == NULL) {
            MED(str);
            trielist = NULL;
            while(heapSize-1) {
                struct trieList *tmp = (struct trieList *) malloc(sizeof(struct trieList));
                tmp->key = wordsNode[popHeap()];
                tmp->next = trielist;
                trielist = tmp;
                // ap->key = wordsNode[popHeap()];
                // if(heapSize) {
                //     ap->next = (struct trieList *) malloc(sizeof(struct trieList));
                //     ap = ap->next;
                // } else ap->next = NULL;
            }
            // trielist->next = NULL;
            // trielist->key = wordsNode[ap];
            // hexConvert(hexStr, words[ap]);
            // trielist->key = trieSearch(&trieRoot, hexStr);
        } else {
            trieGetList(final, &wordsNum);
        }
    }
    return 0;
}
