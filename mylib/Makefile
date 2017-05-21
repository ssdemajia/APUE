obj = my_error.o tellwait.o pr_exit.o
lib = libss.a
ROOT = ..
RANLIB = ranlib
$(lib) : $(obj)
	$@
	@echo 正在编译libss.a
	$(AR) rv $(lib) $(obj) #r表示替换lib.a中的变化了的obj，不动没有发生变化的obj文件
	$(RANLIB) $(lib)
$(obj): %.o: %.c
	@cc -c $< -o $@  #  $<表示所有满足的依赖， $@表示所有目标
