bfs: bfs.c bfs.h ../../common/harness.c
	$(CC) $(CFLAGS) -o bfs bfs.c ../../common/harness.c

run: bfs input.data check.data
	./bfs input.data check.data

hls: bfs.c bfs.h
	vivado_hls hls.tcl

clean:
	rm -f bfs
