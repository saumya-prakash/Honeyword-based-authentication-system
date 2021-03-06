#include "utilities.h"


/* This function randomly permutates a given array */
void permutate_array(int arr[], int n)
{
    int i;
    int a = n;

    for(i=0; i<n; i++)
    {
        int index = (int)(2*drand48()*a) % a;

        int tmp = arr[index];
        arr[index] = arr[a-1];
        arr[a-1] = tmp;

        a--;
    }
    
    return ;
}



/* This function converts a string of integers to an array of integers */
int convert_to_int_array(int arr[], char num[])
{
    char tmp[50] = {'\0'};

    int a = 0;
    int i = 0;
    
    while(num[i] != '\0')
    {
        if(num[i] == ' ')
        {
            i++;
            continue;
        }

        else
        {
            int k = 0;
            while(num[i] != '\0' && num[i] != ' ')
            {
                tmp[k] = num[i];
                k++;
                i++;
            }

            tmp[k] = '\0';
            arr[a] = atoi(tmp);
            a++;
        }
    }


    return a;
}


/* This function raises an alarm by ringing an alert bell and printing diagnostic
message */
void raise_alarm(char username[], int type)
{
    printf("\a");   // sound alert bell
    
    if(type == HONEYPOT_HIT)
        printf("ALARM!!! HONEYPOT ACCOUNT HIT!\n");
    else if(type == HONEYWORD_HIT)
        printf("ALARM!!! HONEYWORD HIT\n");
    
    printf("The username entered was -> %s\n", username);
    
    printf("\n");

    return ;
}