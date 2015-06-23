/*
Implementation based on http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
*/

#include "kmp.h"

void CPF(char pattern[PATTERN_SIZE], int kmpNext[PATTERN_SIZE]) {
    int k, q;
    k = 0;
    kmpNext[0] = 0;

    c1 : for(q = 1; q < PATTERN_SIZE; q++){
        c2 : while(k > 0 && pattern[k] != pattern[q]){
            k = kmpNext[q];
        }
        if(pattern[k] == pattern[q]){
            k++;
        }
        kmpNext[q] = k;
    }
}


int kmp(char pattern[PATTERN_SIZE], char input[STRING_SIZE], int kmpNext[PATTERN_SIZE]) {
    int i, q;
    int outs;
    outs = 0;

    CPF(pattern, kmpNext);

    q = 0;
    k1 : for(i = 0; i < STRING_SIZE; i++){
        k2 : while (q > 0 && pattern[q] != input[i]){
            q = kmpNext[q];
        }
        if (pattern[q] == input[i]){
            q++;
        }
        if (q >= PATTERN_SIZE){
            outs++;
            q = kmpNext[q - 1];
        }
    }
    return outs;
}
