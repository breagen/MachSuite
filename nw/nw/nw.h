#include <stdio.h>
#include <stdlib.h>

#define TYPE char

#define N 128
#define M 128
#define N1 (N+1)
#define M1 (M+1)
#define sum_size (M+N)
#define dyn_size  (M+1) * (N+1)


/*void needwun(char seqA[N], char seqB[M], char alignedA[N+M], char alignedB[M+N]);*/

void needwun(char SEQA[N], char SEQB[M], char alignedA[sum_size], char alignedB[sum_size],
             int A[dyn_size], char ptr[dyn_size]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  char seqA[N];
  char seqB[N];
  char alignedA[N+M];
  char alignedB[N+M];
  int A[dyn_size];
  char ptr[dyn_size];
};
int INPUT_SIZE = sizeof(struct bench_args_t);

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  needwun( args->seqA, args->seqB, args->alignedA, args->alignedB, args->A, args->ptr);
}

////////////////////////////////////////////////////////////////////////////////
