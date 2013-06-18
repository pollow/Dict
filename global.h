#ifndef _GLOBAL_H
#define _GLOBAL_H

#define MAXN 100000

struct expTreeNode {
    char name[4];
    char *data;
};

struct trieNode {
    int index;
    char *word;
    struct trieNode *son[16];
};

struct trieList {
    struct trieNode *key;
    struct trieList *next;
};

extern struct trieList *trielist;
extern char *words[MAXN];
extern struct trieNode trieRoot, *wordsNode[MAXN];
extern struct expTreeNode *expNodeList[2000];
extern int expNodetop;
extern int wordsNum;

#endif
