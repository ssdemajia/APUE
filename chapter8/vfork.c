#include <unistd.h>
#include <stdio.h>

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
        _exit(0);
    } else {
        printf("I'm parent, pid = %d\n", getpid());
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
    return 0;
}
