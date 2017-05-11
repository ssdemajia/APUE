/*
指定文件描述符，并对该描述符打印其所选择的文件标志说明
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char const *argv[]) {
    int val;
    if (argc != 2) {
        fprintf(stderr, "usage: a.out <descriptor#>");
    }
    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl error for fd %d\n", atoi(argv[1]));
    }
    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only\n");
            break;
        case O_WRONLY:
            printf("write only\n");
            break;
        case O_RDWR:
            printf("read write\n");
            break;
        default:
            fprintf(stderr, "unknown access mode\n");
    }
    if (val & O_APPEND) {
        printf("append\n");
    }
    if (val & O_NONBLOCK) {
        printf("non blocking\n");
    }
    if (val & O_SYNC) {
        printf("synchronous writes\n");
    }
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC) {
        printf("synchronous writes\n");
    }
#endif
    return 0;
}
