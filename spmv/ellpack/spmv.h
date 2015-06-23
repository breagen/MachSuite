/*
Based on algorithm described here:
http://www.cs.berkeley.edu/~mhoemmen/matrix-seminar/slides/UCB_sparse_tutorial_1.pdf
*/

#include <stdlib.h>
#include <stdio.h>

//#define NNZ 2474
//#define N 662
//#define L 10
#define NNZ 1666
#define N 494
#define L 10

#define TYPE double

#define MIN 2147483646
#define MAX -2147483646

void ellpack(TYPE nzval[N*L], int cols[N*L], TYPE vec[N], TYPE out[N]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE nzval[N*L];
  int cols[N*L];
  TYPE vec[N];
  TYPE out[N];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  ellpack( args->nzval, args->cols, args->vec, args->out );
}

////////////////////////////////////////////////////////////////////////////////
