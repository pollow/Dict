/*
 * layout.c
 *
 * Copyright 2013 Chang Xing & Hongpu Ma
 */

#include "layout.h"
#include "global.h"
#include "lookup.h"
#include "parser.h"

#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
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
    // wordDetail = newwin(max_row-5,max_col-22,3,21);
    wordDetail = newpad(2000,max_col-22);
    // scrollok(wordDetail,TRUE);
    // wsetscrreg(wordDetail,0,max_row-6);
    // wrefresh(wordDetail);
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

    wordsNum = max_row-4;
}

void printDetail() {
    for(int i=0; i<expNodetop; i++) {
        if (strcmp(expNodeList[i]->name, "DC") == 0) {
            //词头
        } else if (strcmp(expNodeList[i]->name, "YX") == 0) {
            //子词条开始
            wattrset(wordDetail, A_STANDOUT);
            wprintw(wordDetail, "\n%s\n\n", expNodeList[i]->data);
            wattrset(wordDetail, A_NORMAL);
        } else if (strcmp(expNodeList[i]->name, "DX") == 0) {
            wattrset(wordDetail, A_BOLD);
            wprintw(wordDetail, "词性: ");
            wattrset(wordDetail, A_NORMAL);
            wprintw(wordDetail, "%s\n", expNodeList[i]->data);
        } else if (strcmp(expNodeList[i]->name, "JX") == 0) {
            /*wattrset(wordDetail, A_BOLD);
            wprintw(wordDetail, "Explanation: ");
            wattrset(wordDetail, A_NORMAL);
            wprintw(wordDetail, "%s\n", expNodeList[i]->data);*/
        } else if (strcmp(expNodeList[i]->name, "GZ") == 0) {
            wattrset(wordDetail, A_BOLD);
            wprintw(wordDetail, "释义: ");
            wattrset(wordDetail, A_NORMAL);
            wprintw(wordDetail, "%s\n", expNodeList[i]->data);
        } else if (strcmp(expNodeList[i]->name, "LY") == 0) {
            wattrset(wordDetail, A_BOLD);
            wprintw(wordDetail, "例句: ");
            wattrset(wordDetail, A_NORMAL);
            wprintw(wordDetail, "%s\n", expNodeList[i]->data);
        } else if (strcmp(expNodeList[i]->name, "LS") == 0) {
            wattrset(wordDetail, A_BOLD);
            wprintw(wordDetail, "翻译: ");
            wattrset(wordDetail, A_NORMAL);
            wprintw(wordDetail, "%s\n", expNodeList[i]->data);
        }
    }
    wrefresh(wordDetail);
}

void wordSelect() {
    int item = 0,i = 0, listlen, py = 0;
    int indexs[200];
    memset(indexs,0,sizeof(indexs));
    struct trieList *p = trielist;
    // 建立索引数组
    while(p) {
        indexs[i] = (p->key)->index;
        p = p->next;
        i++;
    }
    listlen = --i;
    for(int j = 0; j < i/2 ; j++) {
        int tmp = indexs[j];
        indexs[j] = indexs[i-j];
        indexs[i-j] = tmp;
    }
    // 隐藏光标
    curs_set(0);
    mvwchgat(wordsList,0,0,-1,A_NORMAL,1,NULL);
    // 打印第一个释义
    parserProcess(indexs[item]);
    werase(wordDetail);
    printDetail();
    prefresh(wordDetail,0,0,3,21,max_row-2,max_col-1);
    wrefresh(wordsList);

    while(1) {
        int ch = getch();
        bool flag = false;
        switch(ch) {
            case KEY_F(1) : 
                endwin();
                exit(0);
            case KEY_UP :
                mvwchgat(wordsList,item,0,-1,A_NORMAL,2,NULL);
                if(item>0) item--;
                else {
                    curs_set(1);
                    return;
                }
                py = 0;
                break;
            case KEY_DOWN :
                mvwchgat(wordsList,item,0,-1,A_NORMAL,2,NULL);
                if(item < listlen) item++;
                else {
                    curs_set(1);
                    return;
                }
                py = 0;
                break;
            case KEY_LEFT :
                py--;
                flag = true;
                break;
            case KEY_RIGHT :
                py++;
                flag = true;
                break;
        }
        if(flag) {
            prefresh(wordDetail,py,0,3,21,max_row-2,max_col-1);
            continue;
        }
        mvwchgat(wordsList,item,0,-1,A_NORMAL,1,NULL);
        wrefresh(wordsList);
        // 向detail打印解释。
        parserProcess(indexs[item]);
        werase(wordDetail);
        printDetail();
        prefresh(wordDetail,py,0,3,21,max_row-2,max_col-1);
    }
    curs_set(1);
}

void printWords(struct trieList *tl) {
    if(tl==NULL) {
        return;
    } else {
        printWords(tl->next);
        mvwprintw(wordsList,printPos,0,"%d %s",printPos,(tl->key)->word);
        printPos++;
    }
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
        werase(wordsList);

        printPos = 0;
        printWords(trielist);

        wrefresh(wordsList);
        wmove(inputBox,0,p);
        wrefresh(inputBox);
    }
    getch();
    endwin();
    return 0;
}
