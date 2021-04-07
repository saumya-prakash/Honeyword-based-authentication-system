#include "headers.h"

#include <sys/msg.h>


#define message_queue_key 131

#define message_length 1024


struct mesg
{
    long type;
    char text[message_length];
};


/* to initialize a message queue */
int get_msgid();

/* cleint to server communication functions */
int check_credentials(int, char*, char*);
int username_available(int, char*);
int register_user(int msgid, char* username, char* password, int k);


