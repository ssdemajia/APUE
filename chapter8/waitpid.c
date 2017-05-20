#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error\n");
    }
    else if (pid == 0) {
        if ((pid = fork()) < 0) {
            printf("fork 2 error\n");
        }
        else if (pid > 0) {
            exit(0);
        }
        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        fflush(stdout);
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid) {
        printf("waitpid error\n");
    }
    printf("the original process%lld\n", (long long)getpid());
    return 0;
}
