/************************************************************************************
 * This header file contains the declarations for communication-related functions.
 * **********************************************************************************/

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


/*==========================================================
    client-to-server communication functions
============================================================*/
int check_credentials(int msgid, char *username, char *password);
int username_available(int msgid, char *username);
int register_user(int msgid, char* username, char* password, int k);


/*===============================================================
    server-to-honeychecker communication functions
=================================================================*/
int set_user(int msgid, char username[], int a);
int check_user(int msgid, char username[], int a);
