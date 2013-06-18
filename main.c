#include "global.h"
#include "layout.h"
#include "trie.h"
#include "lookup.h"
#include "med.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void readWords() {
    int index=0;
    char str[100]="";
    FILE *f = fopen("index.txt", "r");
    while(fscanf(f,"%d ",&index) == 1) {
        if(index==5660) {
            printf("fucker!");
        }
        int i = 0; while((str[i++]=fgetc(f)) != '\n') {}; str[i-1] = 0;
        words[index] = (char *) malloc(strlen(str)*sizeof(char));
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

int main() {
    // 初始化。
    init();
    // 调用主程序。
    layoutProcess();
    
    return 0;
}
