/*
 * med.c
 *
 * Minimum Edit Distance (DP)
 *
 * Copyright 2013 Chang Xing
 */

#include "med.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int min(int a, int b) {
    if ( a < b ) return a;
    else return b;
}

void cleanHeap() {
    for(int  i = 0; i <= HEAP_SIZE; i++) {
        free(heap[i]);
    }
    heapSize = 1;
}

int popHeap() {
    int ans = heap[1]->key, t=1;
    struct heapStruct *tmp;

    free(heap[1]);
    heap[1] = heap[--heapSize];
    while( t<<1 < heapSize ) {
        int k = t << 1;
        if(( k+1 < heapSize ) && (heap[ k ]->value < heap[ k + 1 ]->value)) k++;
        if(heap[ t ]->value <= heap[ k ]->value) {
            tmp = heap[ t ];
            heap[ t ] = heap[ k ];
            heap[ k ] = tmp;
        }
        t = k; 
    }

    return ans;
}

void addHeap(int key, int value) {
    if(heapSize > wordsNum+1 && value >= heap[1]->value) return;
    int t = heapSize++;
    struct heapStruct *tmp;

    heap[t] = (struct heapStruct *) malloc(sizeof(struct heapStruct));
    heap[t]->key = key;
    heap[t]->value = value;
    while(t > 1) {
        if(heap[ t ]->value > heap[ t >> 1 ]->value) {
            tmp = heap[t];
            heap[t] = heap[t >> 1];
            heap[t >> 1] = tmp;
        } else break;
        t = t >> 1;
    }
    if( heapSize > wordsNum+2 ) {
        popHeap();
    }

    return;
}

void MED(char *a) {
    int f[100][100];
    
    cleanHeap();
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
        addHeap(t,f[lena][lenb]);
    }

    return;
}

