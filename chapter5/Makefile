f:fmem.o fmemopen.o
	cc -o f fmem.o fmemopen.o
fmem.o: fmem.c
	cc -c fmem.c
fmemopen.o: fmemopen.c
	cc -c fmemopen.c
clean:
	rm *.o
.PHONY: f clean
