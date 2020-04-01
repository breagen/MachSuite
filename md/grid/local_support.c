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

  md(args->n_points, args->force, args->position);

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
int32_t[blockSide^3]: grid populations
%% Section 2
TYPE[blockSide^3*densityFactor]: positions
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
  parse_int32_t_array(s, (int32_t *)(data->n_points), blockSide * blockSide * blockSide);

  s = find_section_start(p, 2);
  STAC(parse_, TYPE, _array)
  (s, (double *)(data->position), 3 * blockSide * blockSide * blockSide * densityFactor);
  free(p);
}

void data_to_input(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  write_int32_t_array(fd, (int32_t *)(data->n_points), blockSide * blockSide * blockSide);

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, (double *)(data->position), 3 * blockSide * blockSide * blockSide * densityFactor);
}

/* Output format:
%% Section 1
TYPE[blockSide^3*densityFactor]: force
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
  (s, (double *)data->force, 3 * blockSide * blockSide * blockSide * densityFactor);
  free(p);
}

void data_to_output(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  STAC(write_, TYPE, _array)
  (fd, (double *)data->force, 3 * blockSide * blockSide * blockSide * densityFactor);
}

int check_data(void *vdata, void *vref)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  struct bench_args_t *ref = (struct bench_args_t *)vref;
  int has_errors = 0;
  int i, j, k, d;
  TYPE diff_x, diff_y, diff_z;

  for (i = 0; i < blockSide; i++)
  {
    for (j = 0; j < blockSide; j++)
    {
      for (k = 0; k < blockSide; k++)
      {
        for (d = 0; d < densityFactor; d++)
        {
          diff_x = data->force[i][j][k][d].x - ref->force[i][j][k][d].x;
          diff_y = data->force[i][j][k][d].y - ref->force[i][j][k][d].y;
          diff_z = data->force[i][j][k][d].z - ref->force[i][j][k][d].z;
          has_errors |= (diff_x < -EPSILON) || (EPSILON < diff_x);
          has_errors |= (diff_y < -EPSILON) || (EPSILON < diff_y);
          has_errors |= (diff_z < -EPSILON) || (EPSILON < diff_z);
        }
      }
    }
  }

  // Return true if it's correct.
  return !has_errors;
}
