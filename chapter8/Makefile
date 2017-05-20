obj = 8-12.o
inc = ../myinclude
lib = ../mylib
vpath %.h ../myinclude# %意味匹配零或若干个字符
all: $(object) $(obj)
	cc -o $@ $(lib)/libss.a $(obj)  -L$(lib) 
makelib:
	cd ../mylib && $(MAKE)#进入mylib目录，调用这个目录下的makefile，生成libss.a
8-12:8-12.c
	cc $@.c -o $@.o
.PHONY:clean
clean:
	-rm *.o  #前面加减号，表示忽略错误
