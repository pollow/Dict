//  Created by 邢 畅 on 13-5-12.
//  Copyright (c) 2013年 邢 畅. All rights reserved.
//

#include "med.h"
#include "global.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int min(int a, int b) {
    if ( a < b ) return a;
    else return b;
}

int MED(char *a) {
    int f[100][100];
    int ans = 100000, index = 0;
    
    for( int t = 0; t < MAXN; t++ ) {
        memset(f,0,sizeof(f));
        char *b = words[t];
        if( !b ) continue;
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
        
        if( b[0] == 'g' ) printf("%d %s\n",f[lena][lenb],b);
        if( ans > f[lena][lenb] ) {
            ans = f[lena][lenb];
            index = t;
        }
    }
    return index;
}

