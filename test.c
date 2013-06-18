#include <stdio.h>
#include <ncurses.h>

int main() {
    initscr();
    cbreak();
    noecho();

    mvprintw(10,10,"hello world!");

    refresh();
    getch();
    endwin();
    return 0;
}