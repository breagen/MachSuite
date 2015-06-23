#include <stdio.h>
#include <stdlib.h>

//Define input sizes
#define col_size 64
#define row_size 128
#define f_size 9

//Data Bounds
#define MIN 2147483646
#define MAX -2147483646
#define TYPE int

//Set number of iterations to execute
#define MAX_ITERATION 1

void stencil( TYPE orig[row_size * col_size],
        TYPE sol[row_size * col_size],
        TYPE filter[f_size] );

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
    TYPE orig[row_size*col_size];
    TYPE sol[row_size*col_size];
    TYPE filter[f_size];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
    struct bench_args_t *args = (struct bench_args_t *)vargs;
    stencil( args->orig, args->sol, args->filter );
}

////////////////////////////////////////////////////////////////////////////////
