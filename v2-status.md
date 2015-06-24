# v2.0 release status

## Updated benchmarks

Benchmark | Kernel | Generator | Checker
--------- | ------ | --------- | -------
`backprop` | | |
`viterbi` | | |

## I/O and checking
`Makefile`:
 - Add `support.c` to everything
 - Add a `generate` target

input->data:
 - Use `support.h` functions to read an input fd into the data struct

data->output:
 - Use `support.h` functions

header:
 - new prototypes
 - move wrapper to `support.c`

checker summary key:
 - (A) ASCII array needed
 -  (C) string comparison
 - (1) single number comparison
 - (+) additional work needed

Benchmark | make | in-data | data-out | hdr | checker (status) | checker (summary) | checker (description)
--------- | ---- | ------- | -------- | --- | ---------------- | ----------------- | ---------------------
`aes/aes` | | | | | |C|string compare
`backprop/backprop` | | | | | |+?|(more work needed)
`bfs/bulk` | | | | | |A|horizon counts
`bfs/queue` | | | | | |A|horizon counts
`fft/strided` | | | | | |A+|compare array ±eps; new input (known signal from combination of frequencies); check freq spikes
`fft/transpose` | | | | | |A+|compare array ±eps; new input (known signal from combination of frequencies); check freq spikes
`gemm/ncubed` | | | | | |A+|compare matrix ±eps; change data type to float
`gemm/blocked` | | | | | |A+|compare matrix ±eps; change data type to float
`kmp/kmp` | | | | | |1|match count
`md/knn` | | | | | |A|compare positions ±eps
`md/grid` | | | | | |A|compare positions ±eps
`nw/nw` | | | | | |C|Compare aligned sequences
`sort/merge` | | | | | |1+|Check sortedness and sum
`sort/radix` | | | | | |1+|Check sortedness and sum
`spmv/crs` | | | | | |A|Compare vector ±eps
`spmv/ellpack` | | | | | |A|Compare vector ±eps
`stencil/stencil2d` | | | | | |A|Compare matrix
`stencil/stencil3d` | | | | | |A|Compare matrix
`viterbi/viterbi` | | | | | |+?|(more work needed)

## Large Inputs
Benchmark | Generator | header | kernel | size tuned | runtime tuned
--------- | --------- | ------ | ------ | ---------- | -------------
`aes/aes` | | | | |
`backprop/backprop` | | | | |
`bfs/bulk` | | | | |
`bfs/queue` | | | | |
`fft/strided` | | | | |
`fft/transpose` | | | | |
`gemm/ncubed` | | | | |
`gemm/blocked` | | | | |
`kmp/kmp` | | | | |
`md/knn` | | | | |
`md/grid` | | | | |
`nw/nw` | | | | |
`sort/merge` | | | | |
`sort/radix` | | | | |
`spmv/crs` | | | | |
`spmv/ellpack` | | | | |
`stencil/stencil2d` | | | | |
`stencil/stencil3d` | | | | |
`viterbi/viterbi` | | | | |
