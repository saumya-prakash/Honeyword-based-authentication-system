#include "communication.h"
#include "file_operations.h"


int msgid = -1;


void clean(int a)
{
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
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
        char username[N] = {'\0'};
        int a;

        sscanf(data.text, "%s %s %d", query_type, username, &a);

        if(strcmp(query_type, "SET") == 0)
        {
            int res = set(username, a); // store in the file
            
            // if(res != -1)
        }

        else if(strcmp(query_type, "CHECK") == 0)
        {
            status = check(username, a);    // match with the entry from the file

            if(status == -2)
            {
                printf("\aALRAM!!! HONEYWORD HIT!\n");
            }

        }


        // send back the response code
        struct mesg response;
        response.type = 4;
        sprintf(response.text, "%d", status);

        msgsnd(msgid, &response, sizeof(response.text), 0);
    }



    return 0;
}