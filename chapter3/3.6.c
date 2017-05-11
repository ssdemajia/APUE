#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int fd = open("tmp", O_RDWR|O_APPEND);
    if (fd < 0) {
        printf("open file error\n");
    }
    int offset;
    if ((offset = lseek(fd, 1, SEEK_SET)) < 0){
        printf("lseek error\n");
    }

    char buf[] = "ssde";
    if (write(fd, buf, strlen(buf)) < 0) {
        printf("write error\n");
    }
    return 0;
}
