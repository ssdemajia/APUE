#include "../myinclude/ss.h"

int main(int argc, char const *argv[]) {
    printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
    return 0;
}
