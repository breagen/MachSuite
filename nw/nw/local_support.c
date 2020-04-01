#include "nw.h"
#include <string.h>

#ifdef __SDSCC__
#include "utils/sds_utils.h"
#endif

int INPUT_SIZE = sizeof(struct bench_args_t);

void run_benchmark(void *vargs)
{
  struct bench_args_t *args = (struct bench_args_t *)vargs;

#ifdef __SDSCC__
  reset();
  start();
#endif

  needwun(args->seqA, args->seqB, args->alignedA, args->alignedB, args->M, args->ptr);

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
char[]: sequence A
%% Section 2
char[]: sequence B
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
  parse_string(s, data->seqA, ALEN);

  s = find_section_start(p, 2);
  parse_string(s, data->seqB, BLEN);
  free(p);
}

void data_to_input(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  write_string(fd, data->seqA, ALEN);

  write_section_header(fd);
  write_string(fd, data->seqB, BLEN);

  write_section_header(fd);
}

/* Output format:
%% Section 1
char[sum_size]: aligned sequence A
%% Section 2
char[sum_size]: aligned sequence B
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
  parse_string(s, data->alignedA, ALEN + BLEN);

  s = find_section_start(p, 2);
  parse_string(s, data->alignedB, ALEN + BLEN);
  free(p);
}

void data_to_output(int fd, void *vdata)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  write_section_header(fd);
  write_string(fd, data->alignedA, ALEN + BLEN);

  write_section_header(fd);
  write_string(fd, data->alignedB, ALEN + BLEN);

  write_section_header(fd);
}

int check_data(void *vdata, void *vref)
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  struct bench_args_t *ref = (struct bench_args_t *)vref;
  int has_errors = 0;

  has_errors |= memcmp(data->alignedA, ref->alignedA, ALEN + BLEN);
  has_errors |= memcmp(data->alignedB, ref->alignedB, ALEN + BLEN);

  // Return true if it's correct.
  return !has_errors;
}
