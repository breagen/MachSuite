#include "md.h"
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

  md_kernel(args->force_x, args->force_y, args->force_z,
            args->position_x, args->position_y, args->position_z,
            args->NL);

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
TYPE[nAtoms]: x positions
%% Section 2
TYPE[nAtoms]: y positions
%% Section 3
TYPE[nAtoms]: z positions
%% Section 4
int32_t[nAtoms*maxNeighbors]: neighbor list
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
  (s, data->position_x, nAtoms);

  s = find_section_start(p, 2);
  STAC(parse_, TYPE, _array)
  (s, data->position_y, nAtoms);

  s = find_section_start(p, 3);
  STAC(parse_, TYPE, _array)
  (s, data->position_z, nAtoms);

  s = find_section_start(p, 4);
  parse_int32_t_array(s, data->NL, nAtoms * maxNeighbors);
  free(p);
}

void data_to_input(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->position_x, nAtoms);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->position_y, nAtoms);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->position_z, nAtoms);

  write_section_header(fd);
  write_int32_t_array(fd, data->NL, nAtoms * maxNeighbors);
}

/* Output format:
%% Section 1
TYPE[nAtoms]: new x force
%% Section 2
TYPE[nAtoms]: new y force
%% Section 3
TYPE[nAtoms]: new z force
*/

void output_to_data(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  char *p, *s;
  // Zero-out everything.
  memset(vdata, 0, sizeof(struct bench_args_t));
  // Load input string
  p = readfile(fd);

  s = find_section_start(p, 1);
  STAC(parse_, TYPE, _array)
  (s, data->force_x, nAtoms);

  s = find_section_start(p, 2);
  STAC(parse_, TYPE, _array)
  (s, data->force_y, nAtoms);

  s = find_section_start(p, 3);
  STAC(parse_, TYPE, _array)
  (s, data->force_z, nAtoms);
  free(p);
}

void data_to_output(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->force_x, nAtoms);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->force_y, nAtoms);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, data->force_z, nAtoms);
}

int check_data(void *vdata, void *vref)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  struct bench_args_t *ref = (struct bench_args_t *)vref;
  int has_errors = 0;
  int i;
  TYPE diff_x, diff_y, diff_z;

  for (i = 0; i < nAtoms; i++)
  {
    diff_x = data->force_x[i] - ref->force_x[i];
    diff_y = data->force_y[i] - ref->force_y[i];
    diff_z = data->force_z[i] - ref->force_z[i];
    has_errors |= (diff_x < -EPSILON) || (EPSILON < diff_x);
    has_errors |= (diff_y < -EPSILON) || (EPSILON < diff_y);
    has_errors |= (diff_z < -EPSILON) || (EPSILON < diff_z);
  }

  // Return true if it's correct.
  return !has_errors;
}
