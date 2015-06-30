/*
Implementation based on algorithm described in:
"Stencil computation optimization and auto-tuning on state-of-the-art multicore architectures"
K. Datta, M. Murphy, V. Volkov, S. Williams, J. Carter, L. Oliker, D. Patterson, J. Shalf, K. Yelick
SC 2008
*/

#include "stencil.h"

void stencil3d(TYPE C[2], TYPE orig[SIZE], TYPE sol[SIZE]) {
    int i, j, k;
    TYPE sum0, sum1, mul0, mul1;

    loop_height : for(i = 1; i < height_size - 1; i++){
        loop_col : for(j = 1; j < col_size - 1; j++){
            loop_row : for(k = 1; k < row_size - 1; k++){
                sum0 = orig[INDX(row_size, col_size, i, j, k)];
                sum1 = orig[INDX(row_size, col_size, i, j, k + 1)] +
                       orig[INDX(row_size, col_size, i, j, k - 1)] +
                       orig[INDX(row_size, col_size, i, j + 1, k)] +
                       orig[INDX(row_size, col_size, i, j - 1, k)] +
                       orig[INDX(row_size, col_size, i + 1, j, k)] +
                       orig[INDX(row_size, col_size, i - 1, j, k)];
                mul0 = sum0 * C[0];
                mul1 = sum1 * C[1];
                sol[INDX(row_size, col_size, i, j, k)] = mul0 + mul1;
            }
        }
    }
}
