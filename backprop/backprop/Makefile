backprop: backprop.c backprop.h ../../common/harness.c
	$(CC) $(CFLAGS) -o backprop backprop.c ../../common/harness.c -lm

run: backprop input.data check.data
	./backprop input.data check.data

hls: backprop.c backprop.h
	vivado_hls hls.tcl

clean:
	rm -f backprop
