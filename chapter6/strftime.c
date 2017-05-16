#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char const *argv[]) {
    time_t t;
    struct tm *temp;
    char buf1[16];
    char buf2[64];

    time(&t);
    temp = localtime(&t);
    if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y%n", temp) == 0) {
        printf("buffer length 16 is too small\n");
    }
    else{
        printf("%s\n", buf1);
    }
    if (strftime(buf2, 64, "%G年 %m月%d日 %b %H时%M分%S秒 %Z%n", temp) == 0) {
        printf("buffer length 64 is too small\n");
    }
    else{
        printf("%s\n", buf2);
    }
    return 0;
}
