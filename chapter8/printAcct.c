#include "../myinclude/ss.h"
#include <sys/acct.h>

#if defined(BSD)
#define acct acctv2
#define ac_flag ac_trailer.ac_flag
