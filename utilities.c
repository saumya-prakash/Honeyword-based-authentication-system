#include "utilities.h"
#include "communication.h"


int check_credentials(int msgid, char *username, char *password)
{
    struct mesg data;

    data.type = 1;
    sprintf(data.text, "CHECK %s %s", username, password);    // send hashed password maybe??

    msgsnd(msgid, &data, strlen(data.text), 0);

    struct mesg response;

    msgrcv(msgid, &response, sizeof(response.text), 2, 0);

    int status;
    sscanf(response.text, "%d", &status);

    return status;
}
