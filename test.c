#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int index=0;
    char str[100]="";
    char *words[100000];
    int tot=0;
    FILE *f = fopen("index.txt", "r");
    while(fscanf(f,"%d ",&index) == 1) {

        int i = 0; while((str[i++]=fgetc(f)) != '\n') {}; str[i-1] = '\0';
        words[index] = (char *) malloc(strlen(str)*sizeof(char));
        strcpy(words[index],str);
        printf("%d %s\n",index,words[index]);
    }
    fclose(f);
    printf("\n%d\n",tot);
    return 0;
}