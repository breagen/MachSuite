---
title: MachSuite
layout: default
---
### Benchmarks for Accelerator Design and Customized Architectures

MachSuite is a set of 19 benchmarks designed to mimic low-level kernels suitable for hardware acceleration.

A full description, including characterization of all the algorithms, can be found in our [IISWC paper](http://www.eecs.harvard.edu/~reagen/papers/machsuite.pdf). If you use MachSite in your research, we'd appreciate a [citation]({{site.baseurl}}/bibtex.html).

For questions, please contact [Brandon Reagen](mailto:reagen@fas.harvard.edu).

 - [Compiling and Running MachSuite](#usage)
 - [The Benchmarks](#benchmarks)

### <a name="usage"></a>Compiling and Running MachSuite

To compile, just run `make`. There is a top-level Makefile which will recursively invoke the ones in each benchmark subdirectory.
You can also use this makefile to run all the MachSuite benchmarks at once using `make run`.

If you prefer to do it piecewise, each benchmark can be invoked using the same command line:

    <benchmark> [input-file] [check-file]

Where `input-file` contains the inputs given in each benchmark's subdirectory, and `check-file` is the answer file to check the output of the benchmark against. Both are optional&mdash;if you don't specify them, the benchmark will look for an `input.data` and a `check.data` file in the current directory.

Note that checking is disabled in the code by default, so you can safely leave off the `check-file` argument.

<a href="#" class="btn btn-default btn-small"><span class="glyphicon glyphicon-triangle-top"/> Top </a>

### <a name="benchmarks"></a>The Benchmarks

Kernel/Algorithm | Description
--- | ---
`aes/aes` | The Advanced Encryption Standard, a common block cipher.
`backprop/backprop` | A simple method for training neural networks.
`bfs/bulk` | Data-oriented version of breadth-first search.
`bfs/queue` | The "expanding-horizon" version of breadth-first search.
`fft/strided` | Recursive formulation of the Fast Fourier Transform.
`fft/transpose` | A two-level FFT optimized for a small, fixed-size butterfly.
`gemm/ncubed` | Naive, O(n<sup>3</sup>) algorithm for dense matrix multiplication.
`gemm/blocked` | A blocked version of matrix multiplication, with better locality.
`kmp/kmp` | The Knuth-Morris-Pratt string matching algorithm.
`md/knn` | n-body molecular dynamics, using k-nearest neighbors to compute only local forces.
`md/grid` | n-body molecular dynamics, using spatial decomposition to compute only local forces.
`nw/nw` | A dynamic programming algorithm for optimal sequence alignment.
`sort/merge` | The mergesort algorithm, on an integer array.
`sort/radix` | Sorts an integer array by comparing 4-bits blocks at a time.
`spmv/crs` | Sparse matrix-vector multiplication, using variable-length neighbor lists.
`spmv/ellpack` | Sparse matrix-vector multiplication, using fixed-size neighbor lists.
`stencil/stencil2d` | A two-dimensional stencil computation, using a 9-point square stencil.
`stencil/stencil2d` | A three-dimensional stencil computation, using a 7-point von Neumann stencil.
`viterbi/viterbi` | A dynamic programing method for computing probabilities on a Hidden Markov model.

<a href="#" class="btn btn-default btn-small"><span class="glyphicon glyphicon-triangle-top"/> Top </a>

