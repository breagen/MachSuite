#include <stdio.h>
#include <stdlib.h>
#include "support.h"

#define N 128
#define M 128
#define sum_size (M+N)
#define dyn_size  (M+1) * (N+1)

void needwun(char SEQA[N], char SEQB[M],
             char alignedA[N+M], char alignedB[N+M],
             int A[(M+1)*(N+1)], char ptr[(M+1)*(N+1)]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  char seqA[N];
  char seqB[N];
  char alignedA[N+M];
  char alignedB[N+M];
  int A[(M+1)*(N+1)];
  char ptr[(M+1)*(N+1)];
};
