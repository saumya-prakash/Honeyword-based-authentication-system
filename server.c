#include "crypt.h"
#include "communication.h"
#include "file_operations.h"

int msgid = -1;

void clean(int a)
{
    // msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}



int main()
{
    signal(SIGINT, clean);

    srand48(time(NULL));

    msgid = get_msgid();

    printf("Server is running...\n\n");

    /* always-on server */
    while(1)
    {
        struct mesg data;

        msgrcv(msgid, &data, sizeof(data.text), 1, 0);
        printf("received message = %s\n", data.text);

        int status = 1;

        char query_type[50] = {'\0'};
        sscanf(data.text, "%s", query_type);
        printf("query_type = %s\n", query_type);


        if(strcmp(query_type, "USERNAME_REGISTERED") == 0)
        {
            char username[N];
            sscanf(data.text, "%s %s", query_type, username);

            int res = username_registered(username);

            status = res;
        }


        else if(strcmp(query_type, "REGISTER") == 0)
        {
            char username[N] = {'\0'};
            unsigned char password[N] = {'\0'};
            int k = 6;
            // extract usernmae, k and password
            sscanf(data.text, "%s %s %d %s", query_type, username, &k, password);
            
            if(k < 6)
                k = 6;
            if(k > 20)
                k = 20;

            unsigned char hashed[50] = {'\0'};
            get_MD5(hashed, password);  // get MD5 of the password
            
            int a = get_random_index(); // assign a random index

            int honeyset[k];

            get_honeyindex_set(honeyset, a, k); // get a honeyindex set - OK

            printf("username = %s\n", username);
            printf("password = %s\n", hashed);
            printf("random_index = %d\n", a);
            int i;
            for(i=0; i<k; i++)
                printf("%d ", honeyset[i]);
            printf("\n");

            // send <username, correct_index> to honeychecker
            set_user(msgid, username, a);

            // add the entry to F1 and F2(update F2 after getting the honeyindex set) - OK
            add_to_file1(username, honeyset, k);
            add_to_file2(a, (char*) hashed);

            // return the status
            
        }

        else if(strcmp(query_type, "CHECK") == 0)
        {
            char username[N] = {'\0'};
            unsigned char password[N] = {'\0'};
            // extract username and password
            sscanf(data.text, "%s %s %s", query_type, username, password);

            // get MD5 of the password
            unsigned char hashed[50] = {'\0'};
            get_MD5(hashed, password);

            // get the honeyindex set from F1
            char num[MAX_LINE_LENGTH] = {'\0'};
            int res = get_file1_entry(num, username);

            if(res == -3)   // detect if it is a honeypot account
            {
                status = -1;
                printf("\aALRAM!!! HONEYPOT ACCOUNT HIT!");
            }

            else
            {
                // match with entries from F2
                int b = match_with_file2(num, (char*) hashed);

                if(b == -1)
                {
                    status = -1;
                    printf("Wrong password\n");
                }

                else
                {
                    // verify the match with the honeychecker
                    
                    // return suitable status code
                }
            }
        }

        struct mesg response;
        response.type = 2;
        sprintf(response.text, "%d", status);  

        msgsnd(msgid, &response, sizeof(response.text), 0);
    
        printf("\n");
    }




    return 0;
}