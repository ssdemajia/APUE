#include <unistd.h>
#include <stdio.h>
#define BUFFSIZE 4096

int main(int argc, char const *argv[]) {
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            printf("write error\n");
        }
    }
    if (n < 0) {
        printf("read error\n");
    }
    return 0;
}
