#include <stdio.h>
#include <stdlib.h>
#include "support.h"

//Define input sizes
#define col_size 64
#define row_size 128
#define f_size 9

//Data Bounds
#define TYPE int32_t
#define MAX 1000
#define MIN 1

//Set number of iterations to execute
#define MAX_ITERATION 1

#pragma SDS data zero_copy(       \
    orig [0:row_size * col_size], \
    sol [0:row_size * col_size],  \
    filter [0:f_size])

#pragma SDS data access_pattern( \
    orig                         \
    : SEQUENTIAL,                \
      sol                        \
    : SEQUENTIAL,                \
      filter                     \
    : SEQUENTIAL)

void stencil(TYPE orig[row_size * col_size],
             TYPE sol[row_size * col_size],
             TYPE filter[f_size]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t
{
    TYPE orig[row_size * col_size];
    TYPE sol[row_size * col_size];
    TYPE filter[f_size];
};
