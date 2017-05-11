#include <fcntl.h>
#include <stdio.h>
void set_fl(int fd, int flags) {
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl F_GETFL error\n");
    }

    val |= flags;
    if (fcntl(fd, F_SETFL, val) < 0) {
        fprintf(stderr, "fcntl F_SETFL error\n");
    }
}
