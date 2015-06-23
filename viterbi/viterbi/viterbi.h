#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define numStates 32
#define numObs 128

int viterbi(int Obs[numObs], float transMat[numStates*numObs], float obsLik[numStates*numObs], float v[numStates*numObs]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
        int Obs[numObs];
        float transMat[numStates*numObs];
        float obsLik[numStates*numObs];
        float v[numStates*numObs];
};
int INPUT_SIZE = sizeof(struct bench_args_t);

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  viterbi( args->Obs, args->transMat, args->obsLik, args->v);
}
////////////////////////////////////////////////////////////////////////////////
