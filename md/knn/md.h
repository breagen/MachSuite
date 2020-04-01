/*
Implemenataion based on:
A. Danalis, G. Marin, C. McCurdy, J. S. Meredith, P. C. Roth, K. Spafford, V. Tipparaju, and J. S. Vetter.
The scalable heterogeneous computing (shoc) benchmark suite.
In Proceedings of the 3rd Workshop on General-Purpose Computation on Graphics Processing Units, 2010.
*/

#include <stdlib.h>
#include <stdio.h>
#include "support.h"

#define TYPE double

// Problem Constants
#define nAtoms 256
#define maxNeighbors 16
// LJ coefficients
#define lj1 1.5
#define lj2 2.0

#ifdef __cplusplus
extern "C"
{
#endif

#pragma SDS data zero_copy( \
    force_x [0:nAtoms],     \
    force_y [0:nAtoms],     \
    force_z [0:nAtoms],     \
    position_x [0:nAtoms],  \
    position_y [0:nAtoms],  \
    position_z [0:nAtoms],  \
    NL [0:nAtoms * maxNeighbors])

#pragma SDS data access_pattern( \
    force_x                      \
    : SEQUENTIAL,                \
      force_y                    \
    : SEQUENTIAL,                \
      force_z                    \
    : SEQUENTIAL,                \
      position_x                 \
    : SEQUENTIAL,                \
      position_y                 \
    : SEQUENTIAL,                \
      position_z                 \
    : SEQUENTIAL,                \
      NL                         \
    : SEQUENTIAL)

  void md_kernel(TYPE force_x[nAtoms],
                 TYPE force_y[nAtoms],
                 TYPE force_z[nAtoms],
                 TYPE position_x[nAtoms],
                 TYPE position_y[nAtoms],
                 TYPE position_z[nAtoms],
                 int32_t NL[nAtoms * maxNeighbors]);
  ////////////////////////////////////////////////////////////////////////////////
  // Test harness interface code.

#ifdef __cplusplus
}
#endif

struct bench_args_t
{
  TYPE force_x[nAtoms];
  TYPE force_y[nAtoms];
  TYPE force_z[nAtoms];
  TYPE position_x[nAtoms];
  TYPE position_y[nAtoms];
  TYPE position_z[nAtoms];
  int32_t NL[nAtoms * maxNeighbors];
};
