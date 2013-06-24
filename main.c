/*
 * main.c
 *
 * Copyright 2013 Chang Xing
 */
#define __DEBUG 0

#include "global.h"
#include "layout.h"
#include "trie.h"
#include "lookup.h"
#include "parser.h"
#include "med.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void readWords() {
    int index=0;
    char str[100]="";
    FILE *f = fopen("index.txt", "r");
    while(fscanf(f,"%d ",&index) == 1) {
        int i = 0; while((str[i++]=fgetc(f)) != '\n') {}; str[i-1] = 0;
        words[index] = (char *) malloc((strlen(str)+1)*sizeof(char));
        strcpy(words[index],str);
    }
    fclose(f);
}

int init() {
    // 读入索引文件，建立<索引,单词>关系，words。
    readWords();
    // 建立trie树，建立<索引,trie节点>关系，wordsNode
    trieInit();
    // 界面初始化。
    layoutInit();
    return 0;
}

void test() {
    readWords();
    trieInit();
    wordsNum = 20;
    lookupProcess("ap*l?");
    while(trielist) {
        int _index_ = trielist->key->index;
        printf("%s %d\n",(trielist->key)->word,_index_);
        // parserProcess(_index_);
        // for(int i=0; i<expNodetop;i++) {
        //     printf("%s %s\n",expNodeList[i]->name,expNodeList[i]->data);
        // }
        trielist = trielist->next;
    }
}

int main() {
    if(__DEBUG) {
        test();
    } else {

    // 初始化。
    init();
    // 调用主程序。
    layoutProcess();
   
    }
    
    return 0;
}
