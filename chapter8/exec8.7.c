#include "../myinclude/ss.h"
#include <dirent.h>
#include <fcntl.h>
int main(int argc, char const *argv[]) {
    pid_t pid;

    DIR *dirp;
    if ((dirp = opendir("/")) == NULL) {
        err_sys("opendir error");
    }
    int dir_fd;
    dir_fd = dirfd(dirp);
    char buf[4];
    if (fcntl(dir_fd, F_GETFD,0) & FD_CLOEXEC) {
        printf("close and exec is on");
    } else {
        printf("close and exec is off");
    }
    sprintf(buf, "%d", dir_fd);
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        execlp("/Users/shaoshuai/Desktop/apue/chapter8/child8.7.c",
        "child8.7", buf, (char*)0);
        exit(0);
    }
    return 0;
}
