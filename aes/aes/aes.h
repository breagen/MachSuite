/*
*   Byte-oriented AES-256 implementation.
*   All lookup tables replaced with 'on the fly' calculations.
*/
#ifndef uint8_t
#define uint8_t  unsigned char
#endif

typedef struct {
  uint8_t key[32];
  uint8_t enckey[32];
  uint8_t deckey[32];
} aes256_context;

void aes256_encrypt_ecb(aes256_context *ctx, uint8_t k[32], uint8_t buf[16]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  aes256_context ctx;
  uint8_t k[32];
  uint8_t buf[16];
};
int INPUT_SIZE = sizeof(struct bench_args_t);


void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;
  aes256_encrypt_ecb( &(args->ctx), args->k, args->buf );
}

////////////////////////////////////////////////////////////////////////////////
