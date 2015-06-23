/*
Implemenataion based on:
A. Danalis, G. Marin, C. McCurdy, J. S. Meredith, P. C. Roth, K. Spafford, V. Tipparaju, and J. S. Vetter.
The scalable heterogeneous computing (shoc) benchmark suite.
In Proceedings of the 3rd Workshop on General-Purpose Computation on Graphics Processing Units, 2010.
*/

#include <stdlib.h>
#include <stdio.h>

#define TYPE double

// Problem Constants
#define nAtoms        256
#define maxNeighbors  16
// LJ coefficients
#define lj1           1.5
#define lj2           2.0

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE d_force_x[nAtoms];
  TYPE d_force_y[nAtoms];
  TYPE d_force_z[nAtoms];
  TYPE position_x[nAtoms];
  TYPE position_y[nAtoms];
  TYPE position_z[nAtoms];
  TYPE NL[nAtoms*maxNeighbors];
};
int INPUT_SIZE = sizeof(struct bench_args_t);

void md_kernel(TYPE d_force_x[nAtoms],
               TYPE d_force_y[nAtoms],
               TYPE d_force_z[nAtoms],
               TYPE position_x[nAtoms],
               TYPE position_y[nAtoms],
               TYPE position_z[nAtoms],
               TYPE NL[nAtoms*maxNeighbors]);

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  md_kernel( args->d_force_x, args->d_force_y, args->d_force_z,
             args->position_x, args->position_y, args->position_z,
             args->NL );
}

////////////////////////////////////////////////////////////////////////////////
