/* ---------------------------------------------------------------------
This file contains the definitions of various file-related functions 
----------------------------------------------------------------------*/


#include "file_operations.h"


/* function to check if a given username is registered */
int username_registered(char *username)
{
    if(username == NULL)    /* NULL input not allowed */
        return 0;
    

    FILE *fptr = fopen(file1, "r"); /* open 'F1' file */

    if(fptr == NULL)
        return 0;
    

    char tmp[N];
    char *lineptr = tmp;
    size_t a = N;
    size_t len;
    

    /* examine each username in the file */
    while((len = getline(&lineptr, &a, fptr)) != EOF)
    {
        int i = 0;
        while(i < len && tmp[i] != ' ')
            i++;
        
        tmp[i] = '\0';

        if(strcmp(username, tmp) == 0)
            return 1;
    }


    fclose(fptr);   /* close the file */

    return 0;
}



int get_random_index()
{
    FILE *fptr = fopen(file2, "r");

    if(fptr == NULL)
        return -1;  // file can't be opened, so no random index can be generated

    int arr[MAX_USERS] = {0};
    int i;
    for(i=0; i<MAX_USERS; i++)
        arr[i] = 0;
    
    
    char line[MAX_LINE_LENGTH] = {'\0'};

    while(fscanf(fptr, "%s", line) != EOF)
    {
        char *colon = strstr(line, ":");    // locate the colon    
        *colon = '\0';  // separate the index part

        int num = atoi(line);
        arr[num] = 1;
    }

    fclose(fptr);


    int brr[MAX_USERS] = {0};
    int n = 0, a = 0;

    for(i=0; i<MAX_USERS; i++)
    {
        if(arr[i] == 0)
        {
            brr[a] = i;
            a++;
            n++;
        }
    }

    if(n == 0)      // user-capacity full - no more new registrations
        return -1;

    // get a random index
    int index = (int)(drand48()*n) % n;

    // return element at the random index
    return brr[index];
}



int get_honeyindex_set(int index_set[], int a, int k)
{
    FILE *fptr = fopen(file2, "r");

    if(fptr == NULL)    // file cannot be opened, so no honeyindex set can be made
        return -1;


    int arr[MAX_USERS] = {0};
    char line[MAX_LINE_LENGTH] = {'\0'};

    int i = 0;    
    while(fscanf(fptr, "%s", line) != EOF)
    {
        char *colon = strstr(line, ":");    // locate the colon
        *colon = '\0';  // extract the index part

        int num = atoi(line);
        arr[i] = num;
        i++;
    }

    fclose(fptr);    

    int n = i;

    for(i=0; i<n; i++)
        printf("%d\n", arr[i]);







    return 1;
}