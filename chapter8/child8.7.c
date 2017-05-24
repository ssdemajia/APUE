#include "../myinclude/ss.h"
#include <fcntl.h>
int main(int argc, char const *argv[]) {
    int fd;
    sscanf(argv[1], "%d", &fd);
    if (fcntl(fd, F_GETFD) & FD_CLOEXEC,0) {
        printf("close and exec is on");
    } else {
        printf("close and exec is off");
    }
    if (fcntl(fd, F_GETFD,0) < 0) {
        err_sys("[child8.7]fcntl error");
    }
    return 0;
}
