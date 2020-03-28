#ifndef __FFT_STR_HEADER__
#define __FFT_STR_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include "support.h"

#define FFT_SIZE 1024
#define twoPI 6.28318530717959

#ifdef __cplusplus
extern "C"
{
#endif

#pragma SDS data zero_copy(     \
    real [0:FFT_SIZE],          \
    img [0:FFT_SIZE],           \
    real_twid [0:FFT_SIZE / 2], \
    img_twid [0:FFT_SIZE / 2])

#pragma SDS data access_pattern( \
    real                         \
    : SEQUENTIAL,                \
      img                        \
    : SEQUENTIAL,                \
      real_twid                  \
    : SEQUENTIAL,                \
      img_twid                   \
    : SEQUENTIAL)

        void fft(double real[FFT_SIZE], double img[FFT_SIZE], double real_twid[FFT_SIZE / 2], double img_twid[FFT_SIZE / 2]);

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t
{
        double real[FFT_SIZE];
        double img[FFT_SIZE];
        double real_twid[FFT_SIZE / 2];
        double img_twid[FFT_SIZE / 2];
};

#endif