#include <sys/resource.h>
#include <stdio.h>

#define doit(name) pr_limits(#name, name)
//#name 把name变为字符串传入形参

static void pr_limits(char * , int);

int main(int argc, char const *argv[]) {
    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);
    return 0;
}

static void pr_limits(char * name, int resource) {
    struct rlimit limit;
    unsigned long long lim;
    if (getrlimit(resource, &limit) < 0) {
        printf("getrlimit error for %s\n", name);
    }
    printf("%-14s ", name);
    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite) ");
    }
    else {
        lim = limit.rlim_cur;
        printf("%10lld ", lim);
    }
    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite) ");
    }
    else {
        lim = limit.rlim_max;
        printf("%10lld ", lim);
    }
    putchar('\n');
}
