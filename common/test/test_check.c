#include "check.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <assert.h>

#define generate_test_TYPE_array(TYPE) \
void test_##TYPE##_array() { \
  char *p; \
  TYPE a[10]; \
  int i; \
  \
  p = readfile("input_" #TYPE "_10"); \
  assert( parse_##TYPE##_array(p, a, 10)==0 ); \
  for(i=0; i<10; i++) { \
    assert(a[i]==((TYPE)i)); \
  } \
}
generate_test_TYPE_array(uint8_t)
generate_test_TYPE_array(uint16_t)
generate_test_TYPE_array(uint32_t)
generate_test_TYPE_array(uint64_t)
generate_test_TYPE_array(float)
generate_test_TYPE_array(double)

void test_section_jumping() {
  char *p;
  p = readfile("input_sections");
}

int main(int argc, char **argv)
{
  test_section_jumping();
  test_uint8_t_array();
  test_uint16_t_array();
  test_uint32_t_array();
  test_uint64_t_array();
  test_float_array();
  test_double_array();

  return 0;
}
