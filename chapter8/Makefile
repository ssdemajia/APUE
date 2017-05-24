obj = 8-12.o
ROOT = ..
inc = $(ROOT)/myinclude
LDDIR = $(ROOT)/mylib#链接库所在文件夹
LDFLAG =#链接所需要的参数
PROGRAM = exec8.7 child8.7
vpath %.h ../myinclude# %意味匹配零或若干个字符
all: $(PROGRAM)
$(PROGRAM): *.c libss.a
	@echo $@
	cc $@.c $(LDDIR)/libss.a -o $@
libss.a:
	(cd $(LDDIR) && $(MAKE))#进入mylib目录，调用这个目录下的makefile，生成libss.a
.PHONY:clean
clean:
	-rm *.o $(PROGRAM) #前面加减号，表示忽略错误
