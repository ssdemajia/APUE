#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int globval = 6;

int main(int argc, char const *argv[]) {
    int var;
    pid_t pid;
    var = 88;

    printf("before fork\n");
    if ((pid = vfork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        printf("I'm child, pid = %d\n", getpid());
        globval++;
        var++;
        exit(0);
    } else {
        printf("I'm parent, pid = %d\n", getpid());
    }
    int ret = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
    printf("printf return = %d\n", ret);
    return 0;
}
