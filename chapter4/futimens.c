#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>


int main(int argc, char const *argv[]) {
    int i, fd;
    struct stat statbuf;
    struct timespec times[2];
    for (i = 1; i < argc; i++) {
        if (stat(argv[1], &statbuf) < 0) {
            fprintf(stderr, "%s: stat error\n", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
            fprintf(stderr, "%s: open error\n", argv[i]);
            continue;
        }
        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;
        if (futimens(fd, times) < 0) {
            fprintf(stderr, "%s: futimnes error\n", argv[i]);
        }
    }
    return 0;
}
