#include "../myinclude/ss.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void charatatime(char *);

int main(int argc, char const *argv[]) {
    pid_t pid;

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        WAIT_PARENT();
        charatatime("out put from child\n");
    } else {
        charatatime("out put from parent\n");
        TELL_CHILD(pid);
    }
    return 0;
}
static void charatatime(char *str) {
    char *ptr;
    int   c;
    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr); ptr++) {
        putc(c, stdout);
    }
}
