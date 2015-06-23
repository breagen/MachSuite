#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 4096

void ms_mergesort(int a[size]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
        int a[size];
};
int INPUT_SIZE = sizeof(struct bench_args_t);

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  ms_mergesort( args->a);
}

////////////////////////////////////////////////////////////////////////////////
