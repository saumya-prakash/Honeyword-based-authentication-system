#include "headers.h"



void login()
{
    char username[N];
    char *password;

    printf("Enter username:");

    scanf("%s", username);

    password = getpass("Enter password:");

    printf("Entered password = %s\n", password);

    return ;
}


void create_new_account()
{
    char username[N];
    char *passwd, *repeat_passwd;

    printf("Enter a username:");
    scanf("%s", username);

    passwd = getpass("Enter a password (should be 8-12 characters):");
    
    printf("%s\n", passwd);

    if(strlen(passwd) < 8 || strlen(passwd) > 12)
    {
        printf("Password must be of 8-12 characters.\n");
        return ;
    }

    repeat_passwd = getpass("Enter the password again:");

    printf("%s\n", repeat_passwd);

    if(strcmp(passwd, repeat_passwd) != 0)
    {
        printf("Paswords do not match.\n");
        return ;
    }

    return ;
}


int main()
{
    printf("Welcome to the Authentication System.\n\n");

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