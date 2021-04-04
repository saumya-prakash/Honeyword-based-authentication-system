#include "headers.h"

#define message_queue_key 131

#define message_length 1024


struct mesg
{
    long type;
    char text[message_length];
};


int get_msgid();