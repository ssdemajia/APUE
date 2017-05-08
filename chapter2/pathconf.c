//pathconf 和 sysconf 函数使用
#include "../include/apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char* mesg, char* path, int name);

int main(int argc, char const *argv[]) {
    if (argc!=2) {
        err_quit("usage: pathconf <dirname>");
    }

#ifdef ARG_MAX
    printf("ARG_MAX defined to be %ld\n", (long)ARG_MAX + 0);
#else
    printf("no symbol for ARG_MAX\n");
#endif
#ifdef _SC_ARG_MAX
    pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
#else
    printf("no symbol for _SC_ARG_MAX\n");
#endif

#ifdef ATEXIT_MAX
    printf("ATEXIT_MAX defined to be %ld\n", (long)ATEXIT_MAX + 0);
#else
    printf("no symbol for ATEXIT_MAX\n");
#endif
#ifdef _SC_ATEXIT_MAX
    pr_sysconf("ATEXIT_MAX =", _SC_ATEXIT_MAX);
#else
    printf("no symbol for _SC_ATEXIT_MAX\n");
#endif

#ifdef CHILD_MAX
    printf("CHILD_MAX defined to be %ld\n", (long)CHILD_MAX + 0);
#else
    printf("no symbol for CHILD_MAX\n");
#endif
#ifdef _SC_ARG_MAX
    pr_sysconf("CHILD_MAX =", _SC_CHILD_MAX);
#else
    printf("no symbol for _SC_CHILD_MAX\n");
#endif

#ifdef HOST_NAME_MAX
    printf("HOST_NAME_MAX defined to be %ld\n", (long)HOST_NAME_MAX + 0);
#else
    printf("no symbol for HOST_NAME_MAX\n");
#endif
#ifdef _SC_HOST_NAME_MAX
    pr_sysconf("HOST_NAME_MAX =", _SC_HOST_NAME_MAX);
#else
    printf("no symbol for _SC_HOST_NAME_MAX\n");
#endif

#ifdef LINE_MAX
    printf("LINE_MAX defined to be %ld\n", (long)LINE_MAX + 0);
#else
    printf("no symbol for LINE_MAX\n");
#endif
#ifdef _SC_LINE_MAX
    pr_sysconf("LINE_MAX =", _SC_LINE_MAX);
#else
    printf("no symbol for _SC_LINE_MAX\n");
#endif

#ifdef PAGE_MAX
    printf("PAGE_MAX defined to be %ld\n", (long)PAGE_MAX + 0);
#else
    printf("no symbol for PAGE_MAX\n");
#endif
#ifdef _SC_PAGE_MAX
    pr_sysconf("PAGE_MAX =", _SC_PAGE_MAX);
#else
    printf("no symbol for _SC_PAGE_MAX\n");
#endif

#ifdef OPEN_MAX
    printf("OPEN_MAX defined to be %ld\n", (long)OPEN_MAX + 0);
#else
    printf("no symbol for OPEN_MAX\n");
#endif
#ifdef _SC_OPEN_MAX
    pr_sysconf("OPEN_MAX =", _SC_OPEN_MAX);
#else
    printf("no symbol for _SC_OPEN_MAX\n");
#endif

#ifdef LOGIN_NAME_MAX
    printf("LOGIN_NAME_MAX defined to be %ld\n", (long)LOGIN_NAME_MAX + 0);
#else
    printf("no symbol for LOGIN_NAME_MAX\n");
#endif
#ifdef _SC_LOGIN_NAME_MAX
    pr_sysconf("LOGIN_NAME_MAX =", _SC_LOGIN_NAME_MAX);
#else
    printf("no symbol for _SC_LOGIN_NAME_MAX\n");
#endif

#ifdef MAX_CANON
    printf("MAX_CANON defined to be %ld\n", (long)MAX_CANON + 0);
#else
    printf("no symbol for MAX_CANON\n");
#endif
#ifdef _PC_MAX_CANON
    pr_pathconf("LOGIN_NAME_MAX =", argv[1], _PC_MAX_CANON);
#else
    printf("no symbol for _PC_MAX_CANON\n");
#endif

    return 0;
}
static void pr_sysconf(char*mesg, int name){
    long val;
    fputs(mesg, stdout);
    errno = 0;
    if ((val = sysconf(name))<0){
        if (errno != 0) {
            fputs("(not supported)\n", stdout);
        }
        else{
            err_sys("sysconf error\n");
        }
    }
    else{
        printf("%ld\n", val);
    }
}
static void pr_pathconf(char*mesg, char* path, int name){
    long val;
    fputs(mesg, stdout);
    errno = 0;
    if ((val = pathconf(path, name))<0){
        if (errno != 0) {
            if (errno == EINVAL) {
                fputs("(not supported)\n", stdout);
            }
            else err_sys("pathconf error, path = %s",path);
        }
        else{
            err_sys("sysconf error\n");
        }
    }
    else{
        printf("%ld\n", val);
    }
}
