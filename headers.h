#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/msg.h>

#include <openssl/md5.h>





#define N 256   // buffer size


#define MAX_USERS 65536 // maximum numbrt users supported by the system

