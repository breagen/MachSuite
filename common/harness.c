#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
extern int INPUT_SIZE;
void run_benchmark( void *args );

//#define CHECK_OUTPUT

#ifdef CHECK_OUTPUT
#include "check.h"
#endif

int main(int argc, char **argv)
{
  int status;
  int in_fd;
  char *in_file;
  char *input;
  #ifdef CHECK_OUTPUT
  int check_fd;
  char *check_file;
  char *check;
  #endif
  int n;

  //assert( argc==3 && "Usage: ./benchmark <input_file> <check_file>" );
  in_file = "input.data";
  #ifdef CHECK_OUTPUT
  check_file = "check.data";
  #endif
  if( argc>1 )
    in_file = argv[1];
  #ifdef CHECK_OUTPUT
  if( argc>2 )
    check_file = argv[2];
  #endif

  // Load input data
  input = malloc(INPUT_SIZE);
  assert( input!=NULL && "Out of memory" );
  in_fd = open( in_file, O_RDONLY );

  n = 0;
  while(n<INPUT_SIZE) {
    status = read(in_fd, &input[n], INPUT_SIZE-n);
    assert( status>=0 && "Failed to read input" );
    n += status;
  }
  close(in_fd);

  //run_benchmark( input );
  // Unpack and call
  run_benchmark( input );
  //#if WRITE_OUTPUT
  //FIXME: Maybe remove this.
  int out_fd, written=0;
  char *ptr = input;
  out_fd = open("output.data", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  assert( out_fd>0 && "Couldn't open output data file" );
  while( written<INPUT_SIZE ) {
    status = write( out_fd, ptr, INPUT_SIZE-written );
    assert( status>=0 && "Couldn't write output data file" );
    written += status;
  }
  //#endif

  // Load check data
  #ifdef CHECK_OUTPUT
  check = malloc(INPUT_SIZE);
  assert( check!=NULL && "Out of memory" );
  check_fd = open( check_file, O_RDONLY );
  n = 0;
  while(n<INPUT_SIZE) {
    status = read(check_fd, &check[n], INPUT_SIZE-n);
    assert( status>=0 && "Failed to read input" );
    n += status;
  }
  close(check_fd);

  // Validate benchmark results
  assert( !memcmp(input,check,INPUT_SIZE) && "Benchmark results are incorrect" );
  #endif

  printf("Success.\n");
  return 0;
}
