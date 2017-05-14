#include <sys/stat.h>
#include <stdio.h>
int main(int argc, char const *argv[]) {
    struct stat statbuf;
    if (stat("foo", &statbuf) < 0) {
        printf("stat error\n");
    }
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
        printf("chmod error for foo\n");
    }
    if (chmod("bar", S_IRGRP|S_IWUSR|S_IRUSR|S_IXUSR) < 0) {
        printf("chmod error for bar\n");
    }
    return 0;
}
