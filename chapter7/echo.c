#include <stdio.h>

int main(int argc, char const *argv[]) {
    for (size_t i = 0; i < argc; i++) {
        printf("argv[%zu] : %s\n", i, argv[i]);
    }
    return 0;
}
