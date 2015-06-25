SRCS=aes.c support.c ../../common/support.c
FILES=$(SRCS) aes.h ../../common/support.h

aes: $(FILES) ../../common/harness.c
	$(CC) $(CFLAGS) -I../../common -o aes $(SRCS) ../../common/harness.c

run: aes input.data check.data
	./aes input.data check.data

generate: $(FILES) generate.c
	$(CC) $(CFLAGS) -I../../common -o generate $(SRCS) generate.c

hls: aes.c aes.h
	vivado_hls hls.tcl

clean:
	rm -f aes
	rm -f generate
