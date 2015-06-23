/*
Implementation based on algorithm described in:
A. Danalis, G. Marin, C. McCurdy, J. S. Meredith, P. C. Roth, K. Spafford, V. Tipparaju, and J. S. Vetter.
The scalable heterogeneous computing (shoc) benchmark suite.
In Proceedings of the 3rd Workshop on General-Purpose Computation on Graphics Processing Units, 2010
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int

#define N 2048
#define NUMOFBLOCKS 512

#define ELEMENTSPERBLOCK 4
#define RADIXSIZE 4
#define BUCKETSIZE NUMOFBLOCKS*RADIXSIZE
#define MASK 0x3

#define SCAN_BLOCK 16
#define SCAN_RADIX BUCKETSIZE/SCAN_BLOCK

void local_scan(int bucket[BUCKETSIZE]);
void sum_scan(int sum[SCAN_RADIX], int bucket[BUCKETSIZE]);
void last_step_scan(int bucket[BUCKETSIZE], int sum[SCAN_RADIX]);
void init(int bucket[BUCKETSIZE]);
void hist(int bucket[BUCKETSIZE], int a[N], int exp);
void update(int b[N], int bucket[BUCKETSIZE], int a[N], int exp);
void ss_sort(int a[N], int b[N], int bucket[BUCKETSIZE], int sum[SCAN_RADIX]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  int a[N];
  int b[N];
  int bucket[BUCKETSIZE];
  int sum[SCAN_RADIX];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  ss_sort( args->a, args->b, args->bucket, args->sum );
}

////////////////////////////////////////////////////////////////////////////////
