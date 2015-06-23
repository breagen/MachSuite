/*
Implementation based on algorithm described in:
"Stencil computation optimization and auto-tuning on state-of-the-art multicore architectures"
K. Datta, M. Murphy, V. Volkov, S. Williams, J. Carter, L. Oliker, D. Patterson, J. Shalf, K. Yelick
SC 2008
*/

#include <stdio.h>
#include <stdlib.h>

//Define input sizes
#define height_size 32
#define col_size 32
#define row_size 16
//Data Bounds
#define MIN 2147483646
#define MAX -2147483646
//Data Type
#define TYPE int
//Set number of iterations to execute
#define MAX_ITERATION 1
//MACROs
#define size (row_size * col_size * height_size)
#define indx(_row_size,_col_size,_i,_j,_k) ((_i)+_row_size*((_j)+_col_size*(_k)))

void stencil3d( TYPE C0, TYPE C1, TYPE orig[row_size * col_size * height_size],
                TYPE sol[row_size * col_size * height_size] );

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE C0;
  TYPE C1;
  TYPE orig[row_size * col_size * height_size];
  TYPE sol[row_size * col_size * height_size];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  stencil3d( args->C0, args->C1, args->orig, args->sol );
}

////////////////////////////////////////////////////////////////////////////////
