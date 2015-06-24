#include "support.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

///// File and section functions
char *readfile(int fd) {
  char *p; 
  struct stat s;
  off_t len;

  assert(fd>1 && "Invalid file descriptor");
  assert(0==fstat(fd, &s) && "Couldn't determine file size");
  len = s.st_size;
  assert(len>0 && "File is empty");
  p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0); 
  assert(p!=NULL && "Couldn't mmap file");
  close(fd); // Does not un-map *p
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
    return s+2; // Skip the section header itself, return pointer to the content
  return s; // Hit the end, return an empty string
}

///// Array read functions
#define generate_parse_TYPE_array(TYPE, STRTOTYPE) \
int parse_##TYPE##_array(char *s, TYPE *arr, int n) { \
  char *line, *endptr; \
  int i=0; \
  TYPE v; \
  \
  assert(s!=NULL && "Invalid input string"); \
  \
  line = strsep(&s,"\n"); \
  while( line!=NULL && i<n ) { \
    endptr = line; \
    errno=0; \
    v = (TYPE)(STRTOTYPE(line, &endptr)); \
    if( (*endptr)!=(char)0 ) { \
      fprintf(stderr, "Invalid input: line %d of section\n", i); \
    } \
    /*assert((*endptr)==(char)0 && "Invalid input character"); */\
    if( errno!=0 ) { \
      fprintf(stderr, "Couldn't convert string \"%s\": line %d of section\n", line, i); \
    } \
    assert(errno==0 && "Couldn't convert the string"); \
    arr[i] = v; \
    i++; \
    line[strlen(line)] = '\n'; /* Undo the strsep replacement.*/ \
    line = strsep(&s,"\n"); \
  } \
  if(line!=NULL) { /* stopped because we read all the things */ \
    line[strlen(line)] = '\n'; /* Undo the strsep replacement.*/ \
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
int write_##TYPE##_array(int fd, TYPE *arr, int n) { \
  int i; \
  assert(fd>1 && "Invalid file descriptor"); \
  for( i=0; i<n; i++ ) { \
    dprintf(fd, "%" FORMAT "\n", arr[i]); \
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

generate_write_TYPE_array(float, "f")
generate_write_TYPE_array(double, "f")

int write_section_header(int fd) {
  assert(fd>1 && "Invalid file descriptor");
  dprintf(fd, "%%%%\n"); // Just prints %%
  return 0;
}
