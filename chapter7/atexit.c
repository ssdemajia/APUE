#include <stdio.h>
#include <stdlib.h>
static void my_exit1(void);
static void my_exit2(void);
int main(int argc, char const *argv[]) {
    if (atexit(my_exit2) != 0) {
        printf("can't register fun exit2\n");
    }
    if (atexit(my_exit1) != 0) {
        printf("can't register fun exit1\n");
    }
    if (atexit(my_exit1) != 0) {
        printf("can't register fun exit1\n");
    }
    printf("main is done \n");
    return 0;
}
static void my_exit1(void) {
    printf("first func handle\n");
}
static void my_exit2(void) {
    printf("second func handle\n");
}
