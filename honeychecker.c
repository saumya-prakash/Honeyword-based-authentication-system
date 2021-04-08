#include "communication.h"
#include "file_operations.h"


int msgid = -1;


void clean(int a)
{
    msgctl(msgid, IPC_RMID, NULL);
}


int main()
{
    signal(SIGINT, clean);

    msgid = get_msgid();

    printf("Honeychecker is running...\n\n");

    /* always-on server */
    while(1)
    {
        struct mesg data;

        msgrcv(msgid, &data, sizeof(data.text), 3, 0);
        printf("received message = %s\n", data.text);

        int status = 1;

        char query_type[50] = {'\0'};
        sscanf(data.text, "%s", query_type);

        if(strcmp(query_type, "SET") == 0)
        {
            // extract username and index
            // store in the file
            // return status
        }

        else if(strcmp(query_type, "CHECK") == 0)
        {
            // extract username and index
            // match with the entry from the file
            // take appropriate actions if required
        }


        // send back the response code
        struct mesg response;
        response.type = 4;
        sprintf(response.text, "%d", status);

        msgsnd(msgid, &response, sizeof(response.text), 0);
    }



    return 0;
}