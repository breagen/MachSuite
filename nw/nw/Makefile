nw: nw.c nw.h ../../common/harness.c
	$(CC) $(CFLAGS) -o nw nw.c ../../common/harness.c

run: nw input.data check.data
	./nw input.data check.data

hls: nw.c nw.h
	vivado_hls hls.tcl

clean:
	rm -f nw
