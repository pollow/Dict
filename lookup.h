#ifndef _LOOKUP_H
#define _LOOKUP_H

#include <stdbool.h>

bool isCapable(char *, char *);
int trieValid(char *);
void travel(char *, int);
extern int lookupProcess(char *str);

#endif
