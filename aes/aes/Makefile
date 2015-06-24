aes: aes.c aes.h support.c ../../common/harness.c ../../common/support.c ../../common/support.h
	$(CC) $(CFLAGS) -o aes aes.c -I../../common ../../common/harness.c ../../common/support.c support.c

run: aes input.data check.data
	./aes input.data check.data

generate: generate.c aes.c aes.h support.c ../../common/support.c ../../common/support.h
	$(CC) $(CFLAGS) -o generate -I../../common aes.c generate.c support.c ../../common/support.c

hls: aes.c aes.h
	vivado_hls hls.tcl

clean:
	rm -f aes
	rm -f generate
