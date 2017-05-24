#include "../myinclude/ss.h"

int main(int argc, char const *argv[]) {
    pid_t pid;
    int status;
    if((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        exit(0);
        printf("child ppid = %d\n", getppid());
    } else {
        sleep(10);
        status = system("ps -o pid,ppid,state,tty,command");
    }
    return 0;
}
