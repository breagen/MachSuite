/*
Implementations based on:
V. Volkov and B. Kazian. Fitting fft onto the g80 architecture. 2008.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TYPE double
//#define TYPE int

typedef struct complex_t {
        TYPE x;
        TYPE y;
} complex;

#define PI 3.1415926535
#ifndef M_SQRT1_2
#define M_SQRT1_2      0.70710678118654752440f
#endif
void fft1D_512(TYPE work_x[512], TYPE work_y[512]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
        TYPE work_x[512];
        TYPE work_y[512];
};
int INPUT_SIZE = sizeof(struct bench_args_t);

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  fft1D_512( args->work_x, args->work_y);
}

////////////////////////////////////////////////////////////////////////////////
