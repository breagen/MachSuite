#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TYPE double

// Problem Constants
#define nAtoms        256
#define domainEdge    20.0
#define blockSide     4
//#define blockSide     1
#define nBlocks       (blockSide*blockSide*blockSide)
#define blockEdge     (domainEdge/((double)blockSide))
// Memory Bound
// This is an artifact of using statically-allocated arrays. We'll pretend that
// it doesn't exist and instead track the actual number of points.
#define densityFactor 10
// LJ coefficients
#define lj1           1.5
#define lj2           2.0

typedef struct {
  double x, y, z;
} dvector_t;
typedef struct {
  int x, y, z;
} ivector_t;

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  int n_points[blockSide][blockSide][blockSide];
  dvector_t d_force[blockSide][blockSide][blockSide][densityFactor];
  dvector_t position[blockSide][blockSide][blockSide][densityFactor];
};
int INPUT_SIZE = sizeof(struct bench_args_t);

void md( int n_points[blockSide][blockSide][blockSide],
         dvector_t d_force[blockSide][blockSide][blockSide][densityFactor],
         dvector_t position[blockSide][blockSide][blockSide][densityFactor]
       );

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  md( args->n_points, args->d_force, args->position );
}

////////////////////////////////////////////////////////////////////////////////
