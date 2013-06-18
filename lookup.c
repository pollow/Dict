#include "lookup.h"

int trieValid(char *str) {
    for(int i=0;i <= strlen(str); i++) {
        if(str[i] == '*' || str[i] == '?') {
            return -1;
        }
    }
    return 1;
}

bool isCapable(char *a, char *b) {
    int j = 0;
    for(int i=0;i<=strlen(a);i++) {
        if(a[i] =! '*' && a[i] != '?') {
            if(a[i]!=b[j]) return false;
            j++;
        } else if(a[i] == '*') {
            j++;
        } else if(a[i] == '?') {
            for(int k=j;k<=strlen(b);k++) {
                if(isCapable(a+(i+1),b+k)) return true;
            }
            return false;
        }
    }
    if(j==(strlen(b)+1)) return true;
    else return false;
}

void travel(char *str,int num) {
// 处理一下连续问号的情况。
    for(int i=0;i<=MAXN;i++) {
        if(isCapable(str,words[i])) {
            num--;
            struct trieList *tmp = (struct trieList *) malloc(sizeof(struct trieList));
            tmp->next = trielist;
            tmp->key = wordsNode[i];
            trielist = tmp;
        }
        if(!num) break;
    }
}

int lookupProcess(char *str) {
    int hexStr[200];

    trielist = NULL;

    if(trieValid(str)==-1) {
        travel(str,20);
    } else {
        hexConvert(hexStr,str);
        struct trieNode *final = trieSearch(&trieRoot,hexStr);
        if(final == NULL) {
            int ap = MED(str);
            trielist = (struct trieList *) malloc(sizeof(struct trieList));
            trielist->next = NULL;
            hexConvert(hexStr,words[ap]);
            trielist->key = trieSearch(&trieRoot,hexStr);
        } else {
            trieGetList(final,&wordsNum);
        }
    }
    return 0;
}
