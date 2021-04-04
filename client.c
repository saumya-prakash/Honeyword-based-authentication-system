#include "headers.h"
#include "communication.h"
#include "utilities.h"


int msgid;


void login()
{
    char username[N];
    char *password;

    printf("Enter username:");

    scanf("%s", username);

    password = getpass("Enter password:");

    int status = check_credentials(msgid, username, password);

    if(status == 1)
        printf("Login Successful!\n");

    else if(status == -1)
        printf("Username or password wrong\n");

    else if(status == -2)
        printf("Honeypot account hit - ALARM!!!\n");
    
    else if(status == -3)
        printf("Honeyword hit - ALARM!!!\n");
    


    return ;
}


void create_new_account()
{
    char username[N], password[N];
    char *p1;

    // do{
        printf("Enter a username:");
        scanf("%s", username);

        // if(username_available(username) == 0)
        // {
        //     printf("Username already taken. Try again.\n");
        // }

    // }while(1)

    p1 = getpass("Enter a password (should be 8-12 characters):");
    
    if(strlen(p1) < 8 || strlen(p1) > 12)
    {
        printf("Password must be of 8-12 characters.\n");
        return ;
    }

    strcpy(password, p1);

    p1 = getpass("Enter the password again:");

    if(strcmp(password, p1) != 0)
    {
        printf("Passwords do not match. Try Again!\n");
        return ;
    }
    
    // int status = register_user(msgid, username, password);
    

    return ;
}


int main()
{
    printf("Welcome to the Authentication System.\n\n");

    msgid = get_msgid();

    int option = 0;

    while(option != 3)
    {
        printf("Select an option:\n");
        printf("\t1 - Login\n");
        printf("\t2 - Create a new account\n");
        printf("\t3 - Exit\n");

        scanf("%d", &option);

        switch(option)
        {
            case 1: login();
                    break;
            
            case 2: create_new_account();
                    break;
            
            case 3: break;

            default: printf("Please select a valid option.\n");
                     break;
        }

        printf("\n");
    }

    printf("Thank you for using the system.\n");


    return 0;
}