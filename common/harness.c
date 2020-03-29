#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>

#define WRITE_OUTPUT
#define CHECK_OUTPUT

#include "support.h"

#ifdef __SDSCC__
#include "utils/sds_utils.h"
#define generic_alloc sds_alloc
#define generic_free sds_free
#else
#define generic_alloc malloc
#define generic_free free
#endif

int main(int argc, char **argv)
{

  printf("-> Starting the program. Number of argc: %d", argc);
  // Parse command line.
  const char *in_file;
#ifdef CHECK_OUTPUT
  const char *check_file;
#endif
  
  if (argc < 4)
  {
    printf("x> Usage: ./benchmark <input_file> <check_file>");
    return -1;
  }

  in_file = "input.data";
#ifdef CHECK_OUTPUT
  check_file = "check.data";
#endif
  if (argc > 1)
    in_file = argv[1];
#ifdef CHECK_OUTPUT
  if (argc > 2)
    check_file = argv[2];
#endif

  // Load input data
  int in_fd;
  char *data;
  data = generic_alloc(INPUT_SIZE);
  assert(data != NULL && "Out of memory");
  in_fd = open(in_file, O_RDONLY);
  assert(in_fd > 0 && "Couldn't open input data file");
  input_to_data(in_fd, data);

#ifdef __SDSCC__
  reset();
  start();
#endif

  // Unpack and call
  run_benchmark(data);

#ifdef __SDSCC__
  stop();
#endif

#ifdef WRITE_OUTPUT
  int out_fd;
  out_fd = open("output.data", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  assert(out_fd > 0 && "Couldn't open output data file");
  data_to_output(out_fd, data);
  close(out_fd);
#endif

// Load check data
#ifdef CHECK_OUTPUT
  int check_fd;
  char *ref;
  ref = generic_alloc(INPUT_SIZE);
  assert(ref != NULL && "Out of memory");
  check_fd = open(check_file, O_RDONLY);
  assert(check_fd > 0 && "Couldn't open check data file");
  output_to_data(check_fd, ref);
#endif

// Validate benchmark results
#ifdef CHECK_OUTPUT
  if (!check_data(data, ref))
  {
    fprintf(stderr, "Benchmark results are incorrect\n");
    return -1;
  }
#endif
  generic_free(data);
  generic_free(ref);

#ifdef __SDSCC__
  uint64_t compute_Total_avg = avg_cpu_cycles();
  float delay = (compute_Total_avg * (1000000.0 / (sds_clock_frequency())));
  //AP freq is 1.5GHz
  printf("-> Number of CPU cycles halted for kernel %d \t~\t %f(uS).\n", compute_Total_avg, delay);
  printf("-> For this AP Thick/S is %d.\n", sds_clock_frequency());
#endif

  printf("Success.\n");
  return 0;
}
