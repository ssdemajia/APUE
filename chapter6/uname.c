/*
exercise 6.3
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <errno.h>
int main(int argc, char const *argv[]) {
    struct utsname ptr;
    if (uname(&ptr) < 0) {
        printf("uname error\n");
        perror("uname");
        exit(1);
    }
    printf("system name : %s\n", ptr.sysname);
    printf("node name : %s\n", ptr.nodename);
    printf("current release : %s\n", ptr.release);
    printf("current version : %s\n", ptr.version);
    printf("hardware type : %s\n", ptr.machine);
    return 0;
}
