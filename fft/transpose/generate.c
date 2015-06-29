#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "fft.h"

int main(int argc, char **argv)
{
  struct bench_args_t data;
  int i, fd;

  // Fill data structure
  srand(1);
  for(i=0; i<512; i++){
    data.work_x[i] = ((TYPE)rand())/((TYPE)RAND_MAX);
    data.work_y[i] = ((TYPE)rand())/((TYPE)RAND_MAX);
  }

  // Open and write
  fd = open("input.data", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  assert( fd>0 && "Couldn't open input data file" );
  data_to_output(fd, (void *)(&data));

  return 0;
}
