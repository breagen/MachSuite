aes: aes.c aes.h support.c ../../common/harness.c ../../common/support.c ../../common/support.h
	$(CC) $(CFLAGS) -I../../common -o aes aes.c support.c ../../common/harness.c ../../common/support.c

run: aes input.data check.data
	./aes input.data check.data

generate: generate.c aes.c aes.h support.c ../../common/support.c ../../common/support.h
	$(CC) $(CFLAGS) -I../../common -o generate aes.c generate.c support.c ../../common/support.c

hls: aes.c aes.h
	vivado_hls hls.tcl

clean:
	rm -f aes
	rm -f generate
