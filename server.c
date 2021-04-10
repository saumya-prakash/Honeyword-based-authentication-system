/**************************************************************************************
 * This file contains the code for 'server' program that handles 'F1' and 'F2' files
 * and communicates with the honeychecker.
 * ************************************************************************************/


#include "crypt.h"
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


int check_for_username(char message[])
{
    char username[MAX_USERNAME_LENGTH] = {'\0'};
    char query_type[N] = {'\0'};
    sscanf(message, "%s %s", query_type, username);

    return username_registered(username);
}


int add_user(char message[])
{
    char query_type[N] = "\0";
    char username[MAX_USERNAME_LENGTH] = {'\0'};
    unsigned char password[N] = {'\0'};
    int k = MIN_K;

    // extract usernmae, k and password
    sscanf(message, "%s %s %d %s", query_type, username, &k, password);
    
    if(k < MIN_K)
        k = MIN_K;
    if(k > MAX_K)
        k = MAX_K;

    unsigned char hashed[N] = {'\0'};
    get_MD5(hashed, password);  // get MD5 of the password
    
    int a = get_random_index(); // assign a random index

    if(a < 0)   // error happened
        return a;


    int honeyset[k];
    int res = get_honeyindex_set(honeyset, a, k); // get a honeyindex set
    if(res < 0)
        return res;

    printf("username = %s\n", username);
    printf("password = %s\n", hashed);
    printf("random_index = %d\n", a);
    int i;
    for(i=0; i<k; i++)
        printf("%d ", honeyset[i]);
    printf("\n");

    // send <username, correct_index> to honeychecker
    res = set_user(msgid, username, a);
    if(res < 0)
        return res;

    // add the entry to F1 and F2(update F2 after getting the honeyindex set) - OK
    add_to_file1(username, honeyset, k);
    add_to_file2(a, (char*) hashed);

    
    return 1;
}



int verify_credentials(char message[])
{
    char query_type[N] = {'\0'};
    char username[MAX_USERNAME_LENGTH] = {'\0'};
    unsigned char password[N] = {'\0'};
    // extract username and password
    sscanf(message, "%s %s %s", query_type, username, password);

    // get MD5 of the password
    unsigned char hashed[50] = {'\0'};
    get_MD5(hashed, password);

    // get the honeyindex set from F1
    char num[MAX_LINE_LENGTH] = {'\0'};
    int res = get_file1_entry(num, username);

    if(res == HONEYPOT_HIT)   // detect if it is a honeypot account
    {
        raise_alarm(username, HONEYPOT_HIT);
        return res;
    }

    if(res == ERROR)
    {
        printf("Wrong username or password\n");
        return res;
    }
    
    // match with entries from F2
    int a = match_with_file2(num, (char*) hashed);

    if(a == WRONG_PASSWORD || a == ERROR)
    {
        printf("Wrong username or password\n");
        return a;
    }

    // verify the match with the honeychecker
    res = check_user(msgid, username, a);

    if(res == HONEYWORD_HIT)
    {
        raise_alarm(username, HONEYWORD_HIT);
        return res;
    }

    // return suitable status code
    return res;
}


int main()
{
    signal(SIGINT, clean);  // for handling unexpected terminations
    srand48(time(NULL));    // seed random-number generator

    msgid = get_msgid();    // get message-queue key

    printf("Server is running...\n\n");

    /* always-on server */
    while(1)
    {
        struct mesg data;
        // get a message from the queue
        int res = msgrcv(msgid, &data, sizeof(data.text), 1, 0);
        
        if(res < 0) // if queue is broken, then terminate
        {
            printf("comunication channel broken\n");
            clean(SIGINT);
        }

        printf("received message = %s\n", data.text);

        int status = 1;

        char query_type[N] = {'\0'};
        sscanf(data.text, "%s", query_type);
        printf("query_type = %s\n", query_type);


        if(strcmp(query_type, "username_registered") == 0)
            status = check_for_username(data.text);


        else if(strcmp(query_type, "register") == 0)
            status = add_user(data.text);


        else if(strcmp(query_type, "check") == 0)
            status = verify_credentials(data.text);


        struct mesg response;
        response.type = 2;
        sprintf(response.text, "%d", status);  

        msgsnd(msgid, &response, sizeof(response.text), 0);
    
        printf("\n");
    }




    return 0;
}