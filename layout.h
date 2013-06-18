#ifndef _LAYOUT_H
#define _LAYOUT_H

#include <ncurses.h>
#include <panel.h>

int max_col, max_row;
extern char waitingWord[1000];

PANEL *homePanel, *viewPanel;
WINDOW *inputBoxBorder, *wordsListBorder, *wordDetailBorder,*inputBox,*wordsList,*wordDetail;

extern void layoutInit();
extern void wordSelect();
extern int layoutProcess();

#endif
