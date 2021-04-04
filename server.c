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

    printf("Server is running...\n\n");

    msgid = get_msgid();

    struct mesg data;

    while(1)
    {
        msgrcv(msgid, &data, sizeof(data.text), 1, 0);
        printf("%s\n", data.text);

        struct mesg response;
        response.type = 2;
        response.text[0] = '1';

        msgsnd(msgid, &response, sizeof(response), 0);
    }




    return 0;
}