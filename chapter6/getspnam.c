#include <shadow.h>
int int main(int argc, char const *argv[]) {
    struct spwd *ptr;
    if ((ptr = getspnam("sar")) == NULL) {
        printf("getspnam error\n");
    }
    printf("sp_pwdp = %s\n", ptr->sp_pwdp == NULL ||
    ptr->sp_pwdp[0] == 0 ? "(null)" : ptr->sp_pwdp);
    
    return 0;
}
