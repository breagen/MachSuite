#include "gemm.h"

void gemm( TYPE m1[row_size * col_size],
           TYPE m2[row_size * col_size],
           TYPE prod[row_size * col_size]){

    int i, j, k;
    TYPE mult, k_col, i_col;

    mult = 0;
    k_col = 0;
    i_col = 0;

    outter:for(i=0;i<row_size;i++) {
        middle:for(j=0;j<col_size;j++) {
            i_col = i * col_size;
            TYPE sum = 0;
            inner:for(k=0;k<row_size;k++) {
                k_col = k * col_size;
                mult = m1[i_col + k] * m2[k_col + j];
                sum += mult;
            }
            prod[i_col + j]  = sum;
        }
    }
}
