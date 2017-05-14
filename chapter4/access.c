#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("usage: a.out <pathname>\n");
        exit(2);
    }
    if (access(argv[1], R_OK) < 0) {
        printf("access error for %s\n", argv[1]);
        exit(1);
    }
    else
    {
        printf("read access ok\n");
    }
    if (open(argv[1], O_RDONLY) < 0) {
        printf("open error for %s \n", argv[1]);
        exit(3);
    }
    else{
        printf("open %s ok\n", argv[1]);
    }
    return 0;
}
