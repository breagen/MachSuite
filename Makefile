BENCHMARKS=\
	aes/aes \
	bfs/bulk \
	bfs/queue \
	fft/strided \
	fft/transpose \
	gemm/ncubed \
	gemm/blocked \
	kmp/kmp \
	md/knn \
	md/grid \
	sort/merge \
	sort/radix \
	spmv/crs \
	spmv/ellpack \
	stencil/stencil2d \
	stencil/stencil3d \
#FIXME\
	backprop/backprop \
	nw/nw \
	viterbi/viterbi

CFLAGS=-O3 -Wall -Wno-unused-label

build:
	@( for b in $(BENCHMARKS); do $(MAKE) CFLAGS="$(CFLAGS)" -C $$b || exit ; done )

run:
	@( for b in $(BENCHMARKS); do $(MAKE) CFLAGS="$(CFLAGS)" -C $$b run || exit ; done )

generate:
	@( for b in $(BENCHMARKS); do $(MAKE) CFLAGS="$(CFLAGS)" -C $$b generate || exit ; done )


### For regression tests
all: clean build generate run

test:
	$(MAKE) -C common/test
	$(MAKE) all CFLAGS="-O3 -Wall -Wno-unused-label -Werror"
	$(MAKE) all CFLAGS="-O3 -Wall -Wno-unused-label -Werror -std=c99"

clean:
	@( for b in $(BENCHMARKS); do $(MAKE) -C $$b clean || exit ; done )
