#ifndef _LAYOUT_H
#define _LAYOUT_H

#include <ncurses.h>
#include <panel.h>

extern char waitingWord[1000];

extern void layoutInit();
extern void wordSelect();
extern int layoutProcess();

#endif
