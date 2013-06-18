#ifndef _LOOKUP
#define _LOOKUP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "med.h"
#include "trie.h"
#include "global.h"

bool isCapable(char *, char *);
int trieValid(char *);
void travel(char *, int);
extern int lookupProcess(char *str);

#endif