/***************************************************************************************
 * This file contains code for 'honeychecker' that can be only communicated via 'server'
 * program.
 * *************************************************************************************/


#include "communication.h"
#include "file_operations.h"
#include "utilities.h"
#include "status_codes.h"


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
        int res = msgrcv(msgid, &data, sizeof(data.text), 3, 0);
        
        if(res < 0)
        {
            printf("communication channel broken\n");
            clean(SIGINT);
        }
        
        // printf("received message = %s\n", data.text);

        int status = OK;

        char query_type[N] = {'\0'};
        char username[MAX_USERNAME_LENGTH] = {'\0'};
        int a;

        sscanf(data.text, "%s %s %d", query_type, username, &a);

        if(strcmp(query_type, "set") == 0)
            status = set(username, a); // store in the file


        else if(strcmp(query_type, "check") == 0)
        {
            status = check(username, a);    // match with the entry from the file

            if(status == HONEYWORD_HIT)
                raise_alarm(username, HONEYWORD_HIT);
        }


        // send back the response code
        struct mesg response;
        response.type = 4;
        sprintf(response.text, "%d", status);

        msgsnd(msgid, &response, sizeof(response.text), 0);
    }



    return 0;
}