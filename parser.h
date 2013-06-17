#ifndef _PARSER
#define _PARSER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern struct expTreeNode {
    char name[4];
    char *data;
};

extern struct expTreeNode *expNodeList[2000];
extern int expNodetop=0;

#endif