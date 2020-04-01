#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "support.h"

#define TYPE double

// Problem Constants
#define nAtoms 256
#define domainEdge 20.0
#define blockSide 4
//#define blockSide     1
#define nBlocks (blockSide * blockSide * blockSide)
#define blockEdge (domainEdge / ((TYPE)blockSide))
// Memory Bound
// This is an artifact of using statically-allocated arrays. We'll pretend that
// it doesn't exist and instead track the actual number of points.
#define densityFactor 10
// LJ coefficients
#define lj1 1.5
#define lj2 2.0

typedef struct __attribute__((packed, aligned(8)))
{
  TYPE x, y, z;
} dvector_t;
typedef struct __attribute__((packed, aligned(8)))
{
  int32_t x, y, z;
} ivector_t;

#ifdef __cplusplus
extern "C"
{
#endif
/*
#pragma SDS data zero_copy(                                      \
    n_points [0:blockSide * blockSide * blockSide],              \
    force [0:blockSide * blockSide * blockSide * densityFactor], \
    position [0:blockSide * blockSide * blockSide * densityFactor])
#pragma SDS data access_pattern( \
    n_points                     \
    : SEQUENTIAL,                \
      force                      \
    : SEQUENTIAL,                \
      position                   \
    : SEQUENTIAL)
*/
#pragma SDS data mem_attribute(n_points               \
                               : PHYSICAL_CONTIGUOUS, \
                                 force                \
                               : PHYSICAL_CONTIGUOUS, \
                                 position             \
                               : PHYSICAL_CONTIGUOUS)

  void md(int32_t n_points[blockSide][blockSide][blockSide],
          dvector_t force[blockSide][blockSide][blockSide][densityFactor],
          dvector_t position[blockSide][blockSide][blockSide][densityFactor]);

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t
{
  int32_t n_points[blockSide][blockSide][blockSide];
  dvector_t force[blockSide][blockSide][blockSide][densityFactor];
  dvector_t position[blockSide][blockSide][blockSide][densityFactor];
};
