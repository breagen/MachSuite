/*
Based on algorithm described here:
http://www.cs.berkeley.edu/~mhoemmen/matrix-seminar/slides/UCB_sparse_tutorial_1.pdf
*/

#include <stdlib.h>
#include <stdio.h>

//#define NNZ 2474
//#define N 662
#define NNZ 1666
#define N 494

#define TYPE double

void spmv(TYPE val[NNZ], int cols[NNZ], int rowDelimiters[N + 1],
          TYPE vec[N], TYPE out[N]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE val[NNZ];
  int cols[NNZ];
  int rowDelimiters[N+1];
  TYPE vec[N];
  TYPE out[N];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  spmv( args->val, args->cols, args->rowDelimiters, args->vec, args->out );
}

////////////////////////////////////////////////////////////////////////////////
