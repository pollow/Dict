/*
 * layout.c
 *
 * Copyright 2013 Chang Xing
 */

#include "layout.h"
#include "global.h"
#include "lookup.h"
#include "parser.h"

#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <panel.h>

char waitingWord[1000];
static int max_col, max_row;

PANEL *homePanel, *viewPanel;
WINDOW *inputBoxBorder, *wordsListBorder, *wordDetailBorder,*inputBox,*wordsList,*wordDetail;

void layoutInit() {
    // 设置语言环境
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr,max_row,max_col);
    noecho();
    start_color();
    refresh();
    
    // init input box
    inputBoxBorder = newwin(3,max_col,0,0);
    wborder(inputBoxBorder,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LTEE,ACS_RTEE);
    wrefresh(inputBoxBorder);
    inputBox = newwin(1,max_col-2,1,1);
    wrefresh(inputBox);
    // init finish & init words list
    wordsListBorder = newwin(max_row-3,20,3,0);
    wborder(wordsListBorder,ACS_VLINE,' ',' ',ACS_HLINE,ACS_VLINE,' ',ACS_LLCORNER,ACS_HLINE);
    wrefresh(wordsListBorder); 
    wordsList = newwin(max_row-4,18,3,1);
    wrefresh(wordsList);
    // init finish & init detail list
    wordDetailBorder = newwin(max_row-3,max_col-20,3,20);
    wborder(wordDetailBorder,ACS_VLINE,ACS_VLINE,' ',ACS_HLINE,ACS_VLINE,ACS_VLINE,ACS_BTEE,ACS_LRCORNER);
    wrefresh(wordDetailBorder);
    wordDetail = newwin(max_row-5,max_col-22,4,21);
    wrefresh(wordDetail);
    // init finish
    refresh();
    wmove(inputBox,0,0); // 设置初始光标位置
    wrefresh(inputBox);
    // all init finish
    
    // color set
    init_pair(1,COLOR_BLACK,COLOR_WHITE);   // 高亮选中
    init_pair(2,COLOR_WHITE,COLOR_BLACK);   // 正常色
    wattron(wordsList,COLOR_PAIR(2));       // wordsList窗体颜色
    wattron(inputBox,COLOR_PAIR(2));        // inputBox窗体颜色
    wattron(wordDetail,COLOR_PAIR(2));      // wordDetail窗体颜色

    wordsNum = 20;
}

void wordSelect() {
    int item = 0,i=0;;
    int indexs[20];
    memset(indexs,0,sizeof(indexs));
    struct trieList *p = trielist;
    while(p) {
        indexs[i] = (p->key)->index;
        p = p->next;
        i++;
    }
    curs_set(0);
    mvwchgat(wordsList,0,0,-1,A_NORMAL,1,NULL);
    wrefresh(wordsList);
    while(1) {
        int ch = getch();
        switch(ch) {
            case KEY_UP :
                mvwchgat(wordsList,item,0,-1,A_NORMAL,2,NULL);
                if(item>0) item--;
                else {
                    curs_set(1);
                    return;
                }
                break;
            case KEY_DOWN :
                mvwchgat(wordsList,item,0,-1,A_NORMAL,2,NULL);
                if(item<20) item++;
                else {
                    curs_set(1);
                    return;
                }
                break;
        }
        mvwchgat(wordsList,item,0,-1,A_NORMAL,1,NULL);
        wrefresh(wordsList);
        // 向detail打印解释。
        parserProcess(indexs[item]);
        for(int i=0;i<expNodetop;i++) {
            wprintw(wordDetail,"%s \n",expNodeList[i]->name);
            if(expNodeList[i]->data != NULL) printf("%s\n",expNodeList[i]->data);
        }
 
    }
    curs_set(1);
}

int layoutProcess() {
    layoutInit();

    int ch,p=0,len=0;
    memset(waitingWord,0,sizeof(waitingWord));
    while(1) {
        // 焦点位于输入框时的键盘监控
        // TODO:
        //  1. F功能键区劫持。
        ch = getch();
        switch(ch) {
            case KEY_F(1) : 
                endwin();
                return 0;
            case KEY_BACKSPACE :
            case 127 :
                if(p>0) {
                    for(int i=p-1;i<len;i++) waitingWord[i]=waitingWord[i+1];
                    waitingWord[--len]='\0';
                    --p;
                    wclear(inputBox);
                    wclear(wordsList);
                }
                break;
            case KEY_LEFT :
                if(p>0) --p;
                break;
            case KEY_RIGHT :
                if(p<len) ++p;
                break;
            case KEY_DOWN :
                wordSelect();
                break;
            case KEY_UP :
                break;
            default :
                if(isprint(ch)) {
                    for(int i=len;i>p;i--) waitingWord[i]=waitingWord[i-1];
                    waitingWord[p]=ch;
                    len++;
                    p++;
                }
        }
        mvwprintw(inputBox,0,0,waitingWord);
        // for(int i=0;i<=max_row-4;i++) {
        //     mvwprintw(wordsList,i,0,waitingWord);
        // }
        lookupProcess(waitingWord);
        int i = 0;
        struct trieList *tl = trielist;
        while(tl) {
            mvwprintw(wordsList,i,0,(tl->key)->word);
            tl = tl->next;
            i++;
        }
        wrefresh(wordsList);
        wmove(inputBox,0,p);
        wrefresh(inputBox);
    }
    getch();
    endwin();
    return 0;
}
