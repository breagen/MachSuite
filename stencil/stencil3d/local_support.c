#include "stencil.h"
#include <string.h>

#ifdef __SDSCC__
#include "utils/sds_utils.h"
#endif

int INPUT_SIZE = sizeof(struct bench_args_t);

#define EPSILON (1.0e-6)

void run_benchmark(void *vargs)
{
  struct bench_args_t *args = (struct bench_args_t *)vargs;
#ifdef __SDSCC__
  reset();
  start();
#endif
  stencil3d(args->C, args->orig, args->sol);

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
TYPE[2]: stencil coefficients (inner/outer)
%% Section 2
TYPE[SIZE]: input matrix
*/

void input_to_data(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  char *p, *s;
  // Load input string
  p = readfile(fd);

  s = find_section_start(p, 1);
  STAC(parse_, TYPE, _array)
  (s, data->C, 2);

  s = find_section_start(p, 2);
  STAC(parse_, TYPE, _array)
  (s, data->orig, SIZE);
  free(p);
}

void data_to_input(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->C, 2);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->orig, SIZE);
}

/* Output format:
%% Section 1
TYPE[SIZE]: solution matrix
*/

void output_to_data(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  char *p, *s;
  // Load input string
  p = readfile(fd);

  s = find_section_start(p, 1);
  STAC(parse_, TYPE, _array)
  (s, data->sol, SIZE);
  free(p);
}

void data_to_output(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->sol, SIZE);
}

int check_data(void *vdata, void *vref)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  struct bench_args_t *ref = (struct bench_args_t *)vref;
  int has_errors = 0;
  int i;
  TYPE diff;

  for (i = 0; i < SIZE; i++)
  {
    diff = data->sol[i] - ref->sol[i];
    has_errors |= (diff < -EPSILON) || (EPSILON < diff);
  }

  // Return true if it's correct.
  return !has_errors;
}
