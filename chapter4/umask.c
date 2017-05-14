#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main(int argc, char const *argv[]) {
    umask(0);
    if (creat("foo", RWRWRW) < 0) {
        printf("creat error for foo\n");
        exit(2);
    }
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (creat("bar", RWRWRW) < 0) {
        printf("creat error for bar\n");
        exit(1);
    }
    return 0;
}
