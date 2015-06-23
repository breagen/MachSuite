CFLAGS=-Wall -Werror

test: input_* test_check
	./test_check

test_check: test_check.c ../check.h
	cc -o test_check $(CFLAGS) -I.. test_check.c

clean:
	rm -f test_check
	rm -rf test_check.dSYM
