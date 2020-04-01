#include "gemm.h"
#include <string.h>

#ifdef __SDSCC__
#include "utils/sds_utils.h"
#endif

int INPUT_SIZE = sizeof(struct bench_args_t);

#define EPSILON ((TYPE)1.0e-6)

void run_benchmark(void *vargs)
{
  struct bench_args_t *args = (struct bench_args_t *)vargs;
#ifdef __SDSCC__
  reset();
  start();
#endif
  gemm(args->m1, args->m2, args->prod);

#ifdef __SDSCC__
  stop();

  uint64_t compute_Total_avg = avg_cpu_cycles();
  double delay = (compute_Total_avg * (1000000.0 / (sds_clock_frequency())));
  //AP freq is 1.2GHz
  printf("-> Number of CPU cycles halted for kernel %llu \t~\t %f(uS).\n", compute_Total_avg, delay);
  printf("-> For this AP Thick/S is %d.\n", sds_clock_frequency());
#endif
}

/* Input format:
%% Section 1
TYPE[N]: matrix 1
%% Section 2
TYPE[N]: matrix 2
*/

void input_to_data(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  char *p, *s;
  // Zero-out everything.
  memset(vdata, 0, sizeof(struct bench_args_t));
  // Load input string
  p = readfile(fd);

  s = find_section_start(p, 1);
  STAC(parse_, TYPE, _array)
  (s, data->m1, N);

  s = find_section_start(p, 2);
  STAC(parse_, TYPE, _array)
  (s, data->m2, N);
  free(p);
}

void data_to_input(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->m1, N);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->m2, N);
}

/* Output format:
%% Section 1
TYPE[N]: output matrix
*/

void output_to_data(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  char *p, *s;
  // Load input string
  p = readfile(fd);

  s = find_section_start(p, 1);
  STAC(parse_, TYPE, _array)
  (s, data->prod, N);
  free(p);
}

void data_to_output(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->prod, N);
}

int check_data(void *vdata, void *vref)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  struct bench_args_t *ref = (struct bench_args_t *)vref;
  int has_errors = 0;
  int r, c;
  TYPE diff;

  for (r = 0; r < row_size; r++)
  {
    for (c = 0; c < col_size; c++)
    {
      diff = data->prod[r * row_size + c] - ref->prod[r * row_size + c];
      has_errors |= (diff < -EPSILON) || (EPSILON < diff);
    }
  }

  // Return true if it's correct.
  return !has_errors;
}
