/*
Implementation based on http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define PATTERN_SIZE 4
#define STRING_SIZE (32411)

int kmp(char pattern[PATTERN_SIZE], char input[STRING_SIZE], int kmpNext[PATTERN_SIZE]);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  char pattern[PATTERN_SIZE];
  char input[STRING_SIZE];
  int kmpNext[PATTERN_SIZE];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  kmp( args->pattern, args->input, args->kmpNext);
}

////////////////////////////////////////////////////////////////////////////////
