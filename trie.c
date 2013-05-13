#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct trieNode {
    int index;
    char *word;
    trieNode *son[16];
} root;

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

struct trieNode *trieInsert(struct trieNode *u, int index, int *q, const char *word) {
    if(*q == -1) {
        u->index = index;
        u->word = (char *)malloc(strlen(word)*sizeof(char));
        strcpy(u->word,word);
        return u;
    } else {
        if(u->son[*q]==NULL) u->son[*q] = newNode();
        return trieInsert(u->son[*q],index,q+1,word);
    }
}

struct trieNode *trieSearch(struct trieNode *u, int *p) {
    if(*p == -1) {
        return u;
    } else {
        return trieSearch(u->son[*p],p+1);
    }
}

void hexConvert(int *a, char *b) {
    for(int i=0;i<strlen(b);i++) {
        a[i*2] = b[i]/16;
        a[i*2+1] = b[i]%16;
    }
    a[strlen(b)*2]=-1;
}

int init() {
    freopen("index.txt","r",stdin);
    int hexStr[100],index;
    char str[100];
	int a;
    while(scanf("%d ",&index)==1) {
        if(index%91285 == 0) {
            a = 0;
        }
        printf("%d\n",index);
        int i = 0; while((str[i++]=getchar()) != '\n'); str[i-1] = '\0';
        hexConvert(hexStr,str);
        trieInsert(&root,index,hexStr,str);
    }
    //int a=fclose(stdin);
	for(int i = 0;i < 10;i++) printf("%d\n",i);
	return 1;
}

int main() {
    init();
    // while(1) {
	for(int i = 0;i < 10;i++) printf("%d\n",i);
    //     int hexStr[100];
    //     char str[100];
    //     scanf("%s",str);
    //     hexConvert(hexStr,str);
    //     struct trieNode *a = trieSearch(&root,hexStr);
    //     printf("%d %s",a->index,a->word);
    // }
    return 0;
}

