#include <stdio.h>
#include <stdlib.h>
#include "support.h"

#define size 1024
#define twoPI 6.28318530717959

void fft(double real[size], double img[size], double real_twid[size/2], double img_twid[size/2]);


////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
        double real[size];
        double img[size];
        double real_twid[size/2];
        double img_twid[size/2];
};
