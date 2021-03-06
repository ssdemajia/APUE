#include "../myinclude/ss.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(int argc, char const *argv[]) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execle("/Users/shaoshuai/Desktop/apue/chapter8/echoall",
            "echoall", "myarg1", "MY ARG2", (char*)0, env_init) < 0) {
            err_ret("execle error");
        }
    }
    if (waitpid(pid, NULL, 0) < 0) {
        err_sys("wait error");
    }
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid == 0) {
        if (execlp("echoall", "echoall", "only 1 arg", (char*)0) <0) {
            err_sys("execlp error");
        }
    }
    return 0;
}
