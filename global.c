/*
 * global.c
 *
 * Copyright 2013 Hongpu Ma
 */

#include "global.h"

struct trieList *trielist;
char *words[MAXN];
struct trieNode trieRoot, *wordsNode[MAXN];
struct expTreeNode *expNodeList[2000];
int expNodetop;
int wordsNum;
