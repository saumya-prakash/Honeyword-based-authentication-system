/* This file contains the definitions of various file-related functions */

#include "file_operations.h"


/* function to check is a given username is registered */
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