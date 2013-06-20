/*
 * layout.h
 *
 * Copyright 2013 Hongpu Ma
 */

#ifndef _LAYOUT_H
#define _LAYOUT_H

#include <ncurses.h>
#include <panel.h>

int printPos;

extern char waitingWord[1000];

extern void layoutInit();
extern void wordSelect();
extern int layoutProcess();

#endif
