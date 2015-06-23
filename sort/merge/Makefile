sort: sort.c sort.h ../../common/harness.c
	$(CC) $(CFLAGS) -o sort sort.c ../../common/harness.c

run: sort input.data check.data
	./sort input.data check.data

hls: sort.c sort.h
	vivado_hls hls.tcl

clean:
	rm -f sort
