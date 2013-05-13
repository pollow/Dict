//
//  main.c
//  CPD
//
//  Created by 邢 畅 on 13-5-12.
//  Copyright (c) 2013年 邢 畅. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct trieNode {
    int index;
    char *word;
    struct trieNode *son[16];
} root;

int _index;

void trieNodeInit(struct trieNode *a) {
    a->index = -1;
    a->word = NULL;
    memset(a->son,0,sizeof(a->son));
}

struct trieNode *newNode() {
    struct trieNode *tmp = (struct trieNode *)malloc(sizeof(struct trieNode));
    trieNodeInit(tmp);
    return tmp;
}

struct trieNode *trieInsert(struct trieNode *u, int *q, const char *word) {
    while (*q!=-1) {
        if(u->son[*q] == NULL) u->son[*q] = newNode();
        u = u->son[*q];
        q++;
    }
    u->index = _index;
    u->word = (char *) malloc(strlen(word)*sizeof(char));
    strcpy(u->word,word);
    return u;
}

struct trieNode *trieSearch(struct trieNode *u, int *p) {
    while (*p != -1) {
        u = u->son[*p];
		p++;
        if (!u) {
            return NULL;
        }
    }
    return u;
}

void hexConvert(int *a, char *b) {
    for(int i=0;i<strlen(b);i++) {
        a[i*2] = b[i]/16;
        a[i*2+1] = b[i]%16;
    }
    a[strlen(b)*2]=-1;
}

int init() {
    FILE *f = fopen("/Users/Deus/workspace/Dict/index.txt", "r");
    int hexStr[100];
    char str[100];
	int a;
    while(fscanf(f,"%d ",&_index)==1) {
        if(_index%2027 == 0) {
            a = 0;
        }
        printf("%d\n",_index);
        int i = 0; while((str[i++]=fgetc(f)) != '\n'); str[i-1] = '\0';
        hexConvert(hexStr,str);
        trieInsert(&root,hexStr,str);
    }
	fclose(f);
	return 1;
}

int main() {
    init();
    while(1) {
        int hexStr[100];
        char str[100];
        scanf("%s",str);
        hexConvert(hexStr,str);
        struct trieNode *a = trieSearch(&root,hexStr);
        printf("%d %s",a->index,a->word);
    }
    return 0;
}


