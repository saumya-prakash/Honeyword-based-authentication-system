#include "crypt.h"
#include "communication.h"
#include "file_operations.h"

int msgid;

void clean(int a)
{
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}



int main()
{
    signal(SIGINT, clean);

    srand48(time(NULL));

    printf("Server is running...\n\n");

    msgid = get_msgid();

    struct mesg data;

    while(1)
    {
        msgrcv(msgid, &data, sizeof(data.text), 1, 0);
        printf("%s\n", data.text);

        char query_type[50] = {'\0'};
        sscanf(data.text, "%s", query_type);

        char c = '1';

        if(strcmp(query_type, "USERNAME_REGISTERED") == 0)
        {
            char username[N];
            scanf(data.text, "%s %s", query_type, username);

            int res = username_registered(username);

            c = 48+res;
        }


        else if(strcmp(query_type, "REGISTER") == 0)
        {
            // extract usernmae and password
            // get MD5 of the password
            // assign a random index
            // get a honeyindex set
            // add the entry to F1 and F2(update F2 after getting the honeyindex set)
            // send <username, correct_index> to honeychecker

            // return the status
            ;
        }

        else if(strcmp(query_type, "CHECK") == 0)
        {
            // extract username and password
            // get MD5 of the password
            // get the honeyindex set from F1 
            // Detect if it is a honeypot account
            // if not, verify the match with the honeychecker
            // return suitable status code
            ;
        }

        struct mesg response;
        response.type = 2;
        response.text[0] = c;

        msgsnd(msgid, &response, sizeof(response), 0);
    }




    return 0;
}