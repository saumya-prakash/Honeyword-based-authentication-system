/**********************************************************************************
 * This header file contains declarations for crytographic-hash related functions.
 * ********************************************************************************/

#include <string.h>
#include <openssl/md5.h>


void get_MD5(unsigned char *result, const unsigned char *input);
