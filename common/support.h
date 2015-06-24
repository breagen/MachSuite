#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>

///// File and section functions

char *readfile(char *filename) {
  int fd; 
  char *p; 
  struct stat s;
  off_t len;

  assert(filename!=NULL);
  fd = open(filename, O_RDONLY);
  assert(fd>1);
  assert(0==fstat(fd, &s));
  len = s.st_size;
  assert(len>0);
  p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0); 
  assert(p!=NULL);
  return p;
}

char *find_section_start(char *s, int n) {
  int i=0;

  // Find the nth "%%\n" substring (if *s==0, there wasn't one)
  while(i<n && (*s)!=(char)0) {
    // This comparison will short-circuit before overrunning the string, so no length check.
    if( s[0]=='%' && s[1]=='%' && s[2]=='\n' ) {
      i++;
    }
    s++;
  }
  if(*s!=(char)0)
    return s+3; // %%\n"<string>"
  return s; // ""
}

///// Array read functions
#define generate_parse_TYPE_array(TYPE, STRTOTYPE) \
int parse_##TYPE##_array(char *s, TYPE *arr, int n) { \
  char *line, *endptr; \
  int i=0; \
  TYPE v; \
  \
  assert(s!=NULL); /* Invalid input string */ \
  \
  line = strsep(&s,"\n"); \
  while( line!=NULL && i<n ) { \
    endptr = line; \
    errno=0; \
    v = (TYPE)(STRTOTYPE(line, &endptr)); \
    assert((*endptr)==(char)0); /* Invalid input character */ \
    assert(errno==0); /* Couldn't convert the string */ \
    arr[i] = v; \
    i++; \
    line = strsep(&s,"\n"); \
  } \
  \
  return 0; \
}

#define strtol_10(a,b) strtol(a,b,10)
generate_parse_TYPE_array(uint8_t, strtol_10)
generate_parse_TYPE_array(uint16_t, strtol_10)
generate_parse_TYPE_array(uint32_t, strtol_10)
generate_parse_TYPE_array(uint64_t, strtol_10)
generate_parse_TYPE_array(int8_t, strtol_10)
generate_parse_TYPE_array(int16_t, strtol_10)
generate_parse_TYPE_array(int32_t, strtol_10)
generate_parse_TYPE_array(int64_t, strtol_10)

generate_parse_TYPE_array(float, strtof)
generate_parse_TYPE_array(double, strtod)

///// Array write functions
// Not strictly necessary, but nice for future-proofing.
#define generate_write_TYPE_array(TYPE, FORMAT) \
int write_##TYPE##array(int fd, TYPE *arr, int n) { \
  int i; \
  for( i=0; i<n; i++ ) { \
    fprintf(fd, FORMAT "\n", arr[i]); \
  } \
  return 0; \
}

generate_write_TYPE_array(uint8_t, PRIu8)
generate_write_TYPE_array(uint16_t, PRIu16)
generate_write_TYPE_array(uint32_t, PRIu32)
generate_write_TYPE_array(uint64_t, PRIu64)
generate_write_TYPE_array(int8_t, PRId8)
generate_write_TYPE_array(int16_t, PRId16)
generate_write_TYPE_array(int32_t, PRId32)
generate_write_TYPE_array(int64_t, PRId64)

generate_write_TYPE_array(float, "%f")
generate_write_TYPE_array(double, "%f")
