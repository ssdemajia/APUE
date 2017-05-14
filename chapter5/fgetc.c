#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1024
int main(int argc, char const *argv[]) {
    char buf[MAXLINE];
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            printf("output error\n");
        }
    }
    if (ferror(stdin)) {
        printf("input error");
    }
    exit(0);
}
