#include "../myinclude/ss.h"
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>


static void err_doit(int, int, const char *, va_list);

/*
打印错误并返回
*/
void err_ret(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}

/*
因为系统调用而发生致命的错误，打印错误内容并返回
*/
void err_sys(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
非致命错误，错误代码通过参数显式传递打印错误并返回
*/
void err_cont(int error, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}

/*
系统调用产生的致命错误，错误代码通过参数显式传递打印错误并返回
*/
void err_exit(int error, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
系统调用产生的致命错误，错误代码通过参数显式传递
打印错误,并core dump产生，结束程序
*/
void err_dump(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort();
    exit(1);
}


/*
与系统调用无关的，非致命错误，
打印错误并返回
*/
void err_msg(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

/*
与系统调用相关的致命错误，
打印错误并退出
*/
void err_quit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
打印一个信息
*/
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap){
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if (errnoflag) {
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ":%s", strerror(error));
    }
    strcat(buf, "\n");
    fflush(stdout);//
    fputs(buf, stderr);
    fflush(NULL);//冲洗所有标准IO
}



/*
所有log函数,输出运行错误
*/

static void log_doit(int, int, int, const char*, va_list ap);

/*
调用者必须设置log_to_stderr，如果非0，这表示运行输出到stderr
等于0则表示为守护进程模式
*/
extern int log_to_stderr;

/*
初始化syslog(), 如果运行为守护模式
*/
void log_open(const char *ident, int option, int facility) {
    if (log_to_stderr == 0) {
        openlog(ident, option, facility);
    }
}

/*
与系统调用无关的致命错误
打印错误原因
*/
void log_ret(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}

/*
与系统调用有关的致命错误
打印错误原因并终止进程
*/
void log_sys(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
与系统调用无关的警告
打印错误原因并终止进程
*/
void log_msg(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
}

/*
与系统调用无关的致命错误
打印错误原因并终止进程
*/
void log_quit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
与系统调用有关的致命错误
显式传递错误代码
打印错误原因并终止进程
*/
void log_exit(int error, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    log_doit(1, error, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*打印错误代码，并返回到调用者
*/
static void log_doit(int errnoflag, int error, int priority, const char *fmt,
    va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if (errnoflag) {
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ":%s", strerror(error));
    }
    strcat(buf, "\n");
    if (log_to_stderr) {
        fflush(stdout);
        fputs(buf, stdout);
        fflush(stderr);
    } else {
        syslog(priority, "%s", buf);
    }
}
