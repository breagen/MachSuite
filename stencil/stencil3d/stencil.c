/*
Implementation based on algorithm described in:
"Stencil computation optimization and auto-tuning on state-of-the-art multicore architectures"
K. Datta, M. Murphy, V. Volkov, S. Williams, J. Carter, L. Oliker, D. Patterson, J. Shalf, K. Yelick
SC 2008
*/

#include "stencil.h"

void stencil3d(TYPE C0, TYPE C1, TYPE orig[size], TYPE sol[size]) {
    int i, j, k;
    TYPE sum1, sum2, mul1, mul2, diff;

    loop_height : for(i = 1; i < height_size - 1; i++){
        loop_col : for(j = 1; j < col_size - 1; j++){
            loop_row : for(k = 1; k < row_size - 1; k++){
                sum1 = orig[indx(row_size, col_size, i, j, k + 1)] +
                       orig[indx (row_size, col_size, i, j, k - 1)] +
                       orig[indx (row_size, col_size, i, j + 1, k)] +
                       orig[indx (row_size, col_size, i, j - 1, k)] +
                       orig[indx (row_size, col_size, i + 1, j, k)] +
                       orig[indx (row_size, col_size, i - 1, j, k)];

                sum2 = orig[indx (row_size, col_size, i, j, k)];

                mul2 = sum2 * C0;
                mul1 = sum1 * C1;
                diff = mul1 - mul2;

                sol[indx(row_size, col_size, i, j, k)] = diff;
            }
        }
    }
}
