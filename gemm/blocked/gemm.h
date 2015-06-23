/*
Implementation based on algorithm described in:
The cache performance and optimizations of blocked algorithms
M. D. Lam, E. E. Rothberg, and M. E. Wolf
ASPLOS 1991
*/

#include <stdio.h>
#include <stdlib.h>

//Data Type
#define TYPE int

//Algorithm Parameters
#define row_size 64
#define col_size 64
#define N row_size*row_size
#define block_size 8
#define NUMOFBLOCKS N/block_size/block_size

//Define the input range to operate over
#define MIN 2147483646
#define MAX -2147483646

//Set number of iterations to execute
#define MAX_ITERATION 1

void bbgemm(TYPE m1[N], TYPE m2[N], TYPE prod[N]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE m1[N];
  TYPE m2[N];
  TYPE prod[N];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  bbgemm( args->m1, args->m2, args->prod );
}

////////////////////////////////////////////////////////////////////////////////
