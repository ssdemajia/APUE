#include <stdio.h>
#include <stdlib.h>
void pr_stdio(const char *, FILE *);
int  is_unbuffered(FILE *);
int  is_linebuffered(FILE *);
int  buff_size(FILE *);

int main(int argc, char const *argv[]) {
    FILE *fp;
    fputs("enter any character\n", stdout);
    if (getchar() == EOF) {
        fprintf(stderr, "putchar error\n");
    }
    fputs("one line to standard error\n", stderr);
    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL) {
        fprintf(stderr, "fopen error\n");
    }
    if (getc(fp) == EOF) {
        fprintf(stderr, "getc error\n");
    }
    pr_stdio("/etc/passwd", fp);
    exit(0);
}
void pr_stdio(const char *name, FILE *fp) {
    printf("stream = %s, ", name);
    if (is_unbuffered(fp)) {
        printf("unbuffered");
    }
    else if (is_linebuffered(fp)) {
        printf("line buffered");
    }
    else {
        printf("fully buffered");
    }
    printf(", buffer size = %d\n", buff_size(fp));
}
#if defined(__SNBF)//Darwin
int is_unbuffered(FILE *fp) {
    return fp->_flags & __SNBF;
}
int is_linebuffered(FILE *fp) {
    return fp->_flags & __SLBF;
}
int buff_size(FILE *fp) {
    return (fp->_bf._size);
}
#endif
