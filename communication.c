#include "communication.h"

int get_msgid()
{
    return msgget(message_queue_key, 0666 | IPC_CREAT);
}




/*------------------------------------------------
client to server communication functions
------------------------------------------------*/

int check_credentials(int msgid, char *username, char *password)
{
    struct mesg data;

    data.type = 1;
    sprintf(data.text, "CHECK %s %s", username, password);    // send hashed password maybe??
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
    sprintf(data.text, "USERNAME_REGISTERED %s",username);
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
    sprintf(data.text, "REGISTER %s %d %s", username, k, password);
    msgsnd(msgid, &data, sizeof(data.text), 0);

    struct mesg response;
    msgrcv(msgid, &response, sizeof(response.text), 2, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return status;
}