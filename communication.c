#include "communication.h"

int get_msgid()
{
    return msgget(message_queue_key, 0666 | IPC_CREAT);
}

// clean(int a) finction needed for non-existent message queue case-handling????? 



/*===================================================
client-to-server communication functions
=====================================================*/

int check_credentials(int msgid, char *username, char *password)
{
    struct mesg data;

    data.type = 1;
    sprintf(data.text, "check %s %s", username, password);    // send hashed password maybe??
    msgsnd(msgid, &data, sizeof(data.text), 0);

    struct mesg response;

    msgrcv(msgid, &response, sizeof(response.text), 2, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return status;
}


int username_available(int msgid, char *username)
{
    struct mesg data;

    data.type = 1;
    sprintf(data.text, "username_registered %s",username);
    msgsnd(msgid, &data, sizeof(data.text), 0);

    struct mesg response;

    msgrcv(msgid, &response, sizeof(response.text), 2, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return !status;
}



int register_user(int msgid, char *username, char *password, int k)
{
    struct mesg data;

    data.type = 1;
    sprintf(data.text, "register %s %d %s", username, k, password);
    msgsnd(msgid, &data, sizeof(data.text), 0);

    struct mesg response;

    msgrcv(msgid, &response, sizeof(response.text), 2, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return status;
}




/*=========================================================
server-to-honeychecker communication functions
===========================================================*/


int set_user(int msgid, char username[], int a)
{
    struct mesg data;
    data.type = 3;
    sprintf(data.text, "set %s %d", username, a);

    msgsnd(msgid, &data, sizeof(data.text), 0);

    struct mesg response;

    msgrcv(msgid, &response, sizeof(response.text), 4, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return status;
}



int check_user(int msgid, char username[], int a)
{
    struct mesg data;
    data.type = 3;
    sprintf(data.text, "check %s %d", username, a);

    msgsnd(msgid, &data, sizeof(data.text), 0);

    struct mesg response;
    
    msgrcv(msgid, &response, sizeof(response.text), 4, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return status;
}