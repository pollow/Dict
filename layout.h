#ifndef _LAYOUT
#define _LAYOUT

#include <ncurses.h>
#include <panel.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "global.h"
#include "lookup.h"
#include "parser.h"

int max_col, max_row;
extern char waitingWord[1000];

PANEL *homePanel, *viewPanel;
WINDOW *inputBoxBorder, *wordsListBorder, *wordDetailBorder,*inputBox,*wordsList,*wordDetail;

extern void layoutInit();
extern void wordSelect();
extern int layoutProcess();

#endif