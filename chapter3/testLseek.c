//lseek(STDIN_FILENO, 0, SEEK_CUR)用于测试能否使用offset来插入文件中
#include "../include/apue.h"
int main(int argc, char const *argv[]) {
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        printf("can't seek\n");
    }
    else
    {
        printf("seek ok\n");
    }
    return 0;
}
