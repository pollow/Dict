#include "lookup.h"

int valid(char *str) {
    for(int i=0;i <= strlen(str); i++) {
        if(str[i] == '*' || str[i] == '?') {
            return -1;
        }
    }
    return 1;
}

bool check(char *a, char *b) {
    j = 0;
    for(int i=0;i<=strlen(a);i++) {
        if(a[i] =! '*' && a[i] != '?') {
            if(a[i]!=b[j]) return false;
            j++;
        } else if(a[i] == '*') {
            j++;
        } else if(a[i] == '?') {
            for(int k=j;k<=strlen(b);k++) {
                if(check(a[i+1],b[k])) return true;
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
        if(check(str,words[i])) {
            num--
            struct *trieList tmp =(struct *trieList) malloc(sizeof(struct trieList));
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

    if(valid(str)==-1) {
        travel(str);
    } else {
        hexConvert(hexStr,str);
        struct trieNode *final = trieSearch(trieRoot,hexStr);
        if(final == NULL) {
            int ap = med(str);
            trielist = (struct trieList *) malloc(sizeof(struct trieList));
            *trielist->next = NULL;
            hexConvert(hexStr,words[ap]);
            *trielist->key = trieSearch(trieRoot,hexStr);
        } else {
            trieGetlist(trielist,wordNum);
            return trielist;
        }
    }
    return 0;
}


