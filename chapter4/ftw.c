#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#include <unistd.h>


typedef int Myfunc(const char *, const struct stat *, int);
char * path_alloc(size_t *sizep);
static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char const *argv[]) {
    int ret;
    if (argc != 2) {
        fprintf(stderr, "usage: ftw <starting-pathname>");
        exit(1);
    }
    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0) {
        ntot = 1;
    }
    printf("普通文件 = %7ld, %5.2f%%\n", nreg, nreg*100.0/ntot);
    printf("文件夹 = %7ld, %5.2f%%\n", ndir, ndir*100.0/ntot);
    printf("块特殊文件 = %7ld, %5.2f%%\n", nblk, nblk*100.0/ntot);
    printf("字符特殊文件 = %7ld, %5.2f%%\n", nchr, nchr*100.0/ntot);
    printf("FIFO = %7ld, %5.2f%%\n", nfifo, nfifo*100.0/ntot);
    printf("符号链接 = %7ld, %5.2f%%\n", nslink, nslink*100.0/ntot);
    printf("sockets = %7ld, %5.2f%%\n", nsock, nsock*100.0/ntot);

    return 0;
}
#define FTW_F 1    //文件
#define FTW_D 2    //文件夹
#define FTW_DNR 3 //文件夹不能读
#define FTW_NS 4  //这个文件不能stat

static char *fullpath;
static size_t pathlen;
static int myftw(char *pathname, Myfunc *func) {
    fullpath = path_alloc(&pathlen);
    if (pathlen <= strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
            fprintf(stderr, "realloc error\n");
        }
    }
    strcpy(fullpath, pathname);
    return dopath(func);
}

static int dopath(Myfunc *func) {
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;
    if (lstat(fullpath, &statbuf) < 0) {
        return func(fullpath, &statbuf, FTW_NS);
    }
    if (S_ISDIR(statbuf.st_mode) == 0) {
        return func(fullpath, &statbuf, FTW_F);
    }
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
        return ret;
    }
    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen) {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
            printf("realloc error\n");
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dp = opendir(fullpath)) == NULL) {
        return func(fullpath, &statbuf, FTW_DNR);
    }
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 ||
            strcmp(dirp->d_name, "..") == 0) {
            continue;
        }
        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
            break;
    }
    fullpath[n-1] = 0;
    if (closedir(dp) < 0) {
        printf("can't close directory %s\n", fullpath);
    }
    return ret;
}
static int myfunc(const char *pathname, const struct stat *statptr, int type){
    switch (type) {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT) {
                case S_IFREG: nreg++; break;
                case S_IFBLK: nblk++; break;
                case S_IFCHR: nchr++; break;
                case S_IFIFO: nfifo++; break;
                case S_IFLNK: nslink++; break;
                case S_IFSOCK: nsock++; break;
                case S_IFDIR:
                    printf("for S_IFDIR error path:%s", fullpath);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            printf("stat error for %s\n", fullpath);
            break;
        default:
            printf("stat error for %s\n", fullpath);
            break;
    }
    return 0;
}
#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

#define PATH_MAX_GUESS 1024

char * path_alloc(size_t *sizep) {
    char *ptr;
    size_t size;
    if (posix_version == 0) {
        posix_version = sysconf(_SC_VERSION);
    }
    if (xsi_version == 0) {
        xsi_version = sysconf(_SC_XOPEN_VERSION);
    }
    if (pathmax == 0) {
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0) {
                pathmax = PATH_MAX_GUESS;
            }
            else
            {
                printf("pathconf error for _PC_PATH_MAX\n");
            }
        }
        else
        {
            pathmax++;
        }
    }
    if ((posix_version < 200112L) && (xsi_version < 4)) {
        size = pathmax + 1;
    }
    else
    {
        size = pathmax;
    }
    if ((ptr = (char*)malloc(size)) == NULL) {
        printf("malloc error\n");
    }
    if (sizep != NULL) {
        *sizep = size;
    }
    return ptr;
}
