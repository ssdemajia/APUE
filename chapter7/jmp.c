#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1024
#define TOK_ADD 5

jmp_buf jmpbuffer;

void do_line(char *);
void cmd_add(void);
int  get_token(void);

int main(int argc, char const *argv[]) {
    char line[MAXLINE];
    int val;
    if ((val = setjmp(jmpbuffer)) == 1) {
        printf("come from cmd_add\n");
    } else if(val != 0){
        printf("error\n");
    }
    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }
    return 0;
}

char *tok_ptr;
void do_line(char *ptr) {
    int cmd;
    tok_ptr = ptr;
    while((cmd = get_token()) > 0) {
        switch (cmd) {
            case TOK_ADD:
                cmd_add();
                break;
        }
    }
}
void cmd_add(void) {
    int token;
    token = get_token();
    token = -5;
    if (token < 0) {
        longjmp(jmpbuffer, 1);
    }
}

int get_token(void) {
    return atoi(tok_ptr);
}
