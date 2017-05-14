#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
void make_temp(char *template);

int main(int argc, char const *argv[]) {
    char good_template[] = "/tmp/dir123456";
    char *bad_template = "/tmp/dir123456";
    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
    return 0;
}

void make_temp(char *template) {
    int fd;
    struct stat sbuf;
    if ((fd = mkstemp(template)) < 0) {
        printf("can't create temp file\n");
    }
    printf("temp file name:%s\n", template);
    close(fd);
    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT) {//Not such file or directory
            printf("temp file dosen't exist\n");
        }
        else
        {
            printf("stat file\n");
        }
    }
    else
    {
        printf("file exists\n");
        unlink(template);
    }
}
