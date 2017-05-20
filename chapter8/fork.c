#include <unistd.h>
#include <stdio.h>

int globval = 6;
char buf[] = "a write to stdout";
int main(int argc, char const *argv[]) {
    int var;
    pid_t pid;
    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        printf("write error");
    }
    printf("before fork\n");
    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        printf("I'm child, pid = %d\n", getpid());
        globval++;
        var++;
    } else {
        printf("I'm parent, pid = %d\n", getpid());
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
    return 0;
}
