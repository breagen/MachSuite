//Standard Libraries
#include <stdio.h>
#include <stdlib.h>

//Define compute data type
#define TYPE int

//Specify row/column sizes
#define row_size 64
#define col_size 64

//Define the input range to operate over
#define MIN 2147483646
#define MAX -2147483646

//Set number of iterations to execute
#define MAX_ITERATION 1

void gemm(TYPE m1[row_size * col_size], TYPE m2[row_size * col_size], TYPE prod[row_size * col_size]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE m1[row_size * col_size];
  TYPE m2[row_size * col_size];
  TYPE prod[row_size * col_size];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  gemm( args->m1, args->m2, args->prod );
}

////////////////////////////////////////////////////////////////////////////////
