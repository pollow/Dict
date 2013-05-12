#include <ncurses.h>
#include <locale.h>
#include <string.h>

int main() {
    setlocale(LC_ALL, "");
    initscr();
    char *ch = "UTF-8 测试";
    char p[100];
    char a[10],s=0;
    printw(ch);
    scanw("%s",p);

    printw(p);
    int tmp = p[0]-s;
    int i=0;
    while(tmp) {
        a[i]=(tmp%10)+'0';
        tmp/=10;
        i++;
    }
    a[i]='\0';
    getch();
    printw(a);
    getch();
    endwin();

    return 0;
}

