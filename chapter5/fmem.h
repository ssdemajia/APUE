#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct memstream
{
    char *buf;
    size_t rsize;//缓冲实际大小
    size_t vsize;//缓冲虚拟大小
    size_t curpos;//缓冲中目前的位置
    int flags;
};
/*flags*/
#define MS_READ 0x01 //打开读取
#define MS_WRITE 0x02 //写入
#define MS_APPEND 0x04 //插入到流中
#define MS_TRUNC 0x08//截断打开
#define MS_FREB  0x10//关闭流，清空buff

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

static int mstream_read(void *, char *, int);
static int mstream_write(void *, const char *, int);
static fpos_t mstream_seek(void *, fpos_t, int);
static int mstream_close(void *);
static int type_to_flags(const char *__restrict type);
static off_t find_end(char *buf, size_t len);
FILE * fmemopen(void *__restrict buf, size_t size, const char *__restrict type);
