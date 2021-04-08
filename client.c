#include "headers.h"
#include "communication.h"
#include "utilities.h"


int msgid = -1;


void login()
{
    char username[MAX_USERNAME_LENGTH] = {'\0'};
    char *password;

    printf("Enter username:");  // input username
    scanf("%s", username);

    password = getpass("Enter password:");  // input password without echoing

    // check the inputted credentials with the server
    int status = check_credentials(msgid, username, password);

    if(status == 1)
        printf("Login Successful!\n");

    else if(status < 0)
        printf("Username or password wrong\n");


    return ;
}


void create_new_account()
{
    char username[MAX_USERNAME_LENGTH] = {'\0'};
    char password[N] = {'\0'};
    char *p1;

    printf("Enter a username:");    // input username
    scanf("%s", username);

    while(username_available(msgid, username) == 0) // check if username is already registered
    {    
        printf("Username already taken. Try again.\n\n");
    
        printf("Enter a username:");
        scanf("%s", username);
    }


    p1 = getpass("Enter a password (should be 8-12 characters):");  // input password
    
    if(strlen(p1) < 8 || strlen(p1) > 12)
    {
        printf("Password must be of 8-12 characters.\n");
        return ;
    }

    strcpy(password, p1);   // put password in the buffer

    p1 = getpass("Enter the password again:");  // ask to repeat the password

    if(strcmp(password, p1) != 0)   // if passwords do not match
    {
        printf("Passwords do not match. Try Again!\n");
        return ;
    }

    int k;
    printf("Enter k [default is 6]: "); // input k
    scanf("%d", &k);
    
    // communicate with server to register the user
    int status = register_user(msgid, username, password, k);

    if(status == 1)
        printf("Registration successful!\n");
    else
        printf("Registration failed. Try again.\n");

    return ;
}



int main()
{
    printf("Welcome to the Authentication System.\n\n");


    msgid = get_msgid();    // get message-queue key

    int option = 0;

    while(option != 3)
    {
        printf("Options:\n");
        printf("\t1 - Login\n");
        printf("\t2 - Create a new account\n");
        printf("\t3 - Exit\n\n");

        printf("Select an option: ");
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