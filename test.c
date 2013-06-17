#include <stdio.h>

int main() {
    FILE *f = fopen("0.txt","r");
    char c;
    while((c = fgetc(f)) != EOF) {
        printf("%c",c);
    }
    return 0;
}