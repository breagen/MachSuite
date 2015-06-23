spmv: spmv.c spmv.h ../../common/harness.c
	$(CC) $(CFLAGS) -o spmv spmv.c ../../common/harness.c

run: spmv input.data check.data
	./spmv input.data check.data

hls: spmv.c spmv.h	
	vivado_hls hls.tcl

clean:
	rm -f spmv
