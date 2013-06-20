#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INS 1
#define DEL 1
#define SUB 1

int min(int a, int b) {
    if ( a < b ) return a;
    else return b;
}

int main() {
    int f[100][100];
    // for( int t = 0; t < MAXN; t++ ) {
    memset(f,0,sizeof(f));
    char *a = "godoy";
    char *b = "goody";
    size_t lena = strlen(a), lenb = strlen(b);
    for(size_t i = 1; i <= lena; i++) f[i][0] = f[i-1][0]+DEL;
    for(size_t i = 1; i <= lenb; i++) f[0][i] = f[0][i-1]+INS;
    
    for(size_t i = 1; i <= lena; i++)
        for(size_t j=1; j <= lenb; j++) {
            f[i][j] = min(f[i-1][j]+DEL,f[i][j-1]+INS);
            if( toupper(a[i-1]) != toupper(b[j-1]) ) {
                f[i][j] = min(f[i][j],f[i-1][j-1]+SUB);
            } else {
                f[i][j] = min(f[i][j],f[i-1][j-1]);
            }
        }
    // }
    return 0;
}
