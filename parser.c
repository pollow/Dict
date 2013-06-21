/*
 * parser.c
 *
 * Copyright 2013 Chang Xing
 */

#include "parser.h"
#include "global.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int expNodetop=0;

int parser(char *str, int i) {
    while (i < (int) strlen(str)) {
        // 转意符略过。
        if(str[i]=='\\') i+=2;
        // 获取标签开头。
        else if(str[i]=='<') {
            i++;
            // 判断是否是结尾标签。
            if(str[i]=='/') {
                struct expTreeNode *node = (struct expTreeNode *) malloc(sizeof(struct expTreeNode));
                node->data = NULL;
                node->name[0] = '/';node->name[1] = str[i+1];node->name[2] = str[i+2];node->name[3] = '\0';
                expNodeList[expNodetop++] = node;
                return i+3;
            // 是头标签。
            } else {
                struct expTreeNode *node = (struct expTreeNode *) malloc(sizeof(struct expTreeNode));
                node->name[0] = str[i];node->name[1] = str[i+1];node->name[2] = '\0';
                node->data = NULL;
                expNodeList[expNodetop++] = node;
                i+=3;
                // 判断是否为内容标签。
                if(str[i]=='<' && str[i+1]=='!') {
                    i++;
                    i+=8;
                    char *tmpHead = str+i,*tmpTail = str+i;
                    while(*tmpTail != '>') tmpTail++;
                    int len = tmpTail - tmpHead - 2;
                    node->data = (char *) malloc(sizeof(char)*len);
                    strncpy(node->data,tmpHead,len);
                    i+=len+7;
                } else {
                    i = parser(str,i);
                }
            }
        }
        i++;
    }
    return i;
}

void parserProcess(int index) {
    char path[25]="./words/",explain[100000];
    memset(explain,0,sizeof(explain));
    int i=8;
    expNodetop=0;
    if(index!=0) {
        int len=log(index)/log(10)+0.0001;
        for(int j=i+len;j>=i;j--) {
            path[j] = '0'+index%10;
            index/=10;
        }
    } else {path[i]='0';}
    strcpy(path+strlen(path),".txt");
    FILE *f = fopen(path,"r");
    i = 0;
    while((explain[i++]=fgetc(f)) != EOF) {;}
    parser(explain,0);
}
