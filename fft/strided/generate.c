#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "fft.h"

int main(int argc, char **argv)
{
  struct bench_args_t data;
  int i, n, fd;
  double typed;
  struct prng_rand_t state;

  // Fill data structure
  prng_srand(1, &state);
  for(i=0; i<size; i++){
    data.real[i] = ((double)prng_rand(&state))/((double)PRNG_RAND_MAX);
    data.img[i] = ((double)prng_rand(&state))/((double)PRNG_RAND_MAX);
  }

  //Pre-calc twiddles
  for(n=0; n<(size>>1); n++){
      typed = (double)(twoPI*n/size);
      data.real_twid[n] = cos(typed);
      data.img_twid[n] = (-1.0)*sin(typed);
  }

  // Open and write
  fd = open("input.data", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  assert( fd>0 && "Couldn't open input data file" );
  data_to_input(fd, (void *)(&data));

  return 0;
}
