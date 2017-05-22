#include "../myinclude/ss.h"
#include <sys/wait.h>

//extern int log_to_stderr;
int main(int argc, char const *argv[]) {
    pid_t pid;
    if ((pid = fork()) <0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execl("/Users/shaoshuai/Desktop/apue/chapter8/testinterp",
            "testinterp", "myarg1", "MY ARG2", (char*)0) < 0) {
            err_sys("execl error");
        }
    }
    //printf("log_to_stderr:%d\n", log_to_stderr);
    int statloc;
    if (waitpid(pid, &statloc, 0) < 0) {
        err_sys("waitpid error");
    }
    pr_exit(statloc);
    return 0;
}
