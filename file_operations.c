/* ---------------------------------------------------------------------
This file contains the definitions of various file-related functions 
----------------------------------------------------------------------*/


#include "file_operations.h"
#include "utilities.h"


/* function to check if a given username is registered */
int username_registered(char *username)
{
    if(username == NULL)    /* NULL input not allowed */
        return 0;
    
    FILE *fptr = fopen(file1, "r"); /* open 'F1' file */

    if(fptr == NULL)
        return 0;
    

    char tmp[MAX_LINE_LENGTH];
    char *lineptr = tmp;
    size_t a = MAX_LINE_LENGTH;
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
    int index = (int)(2*drand48()*n) % n;

    // return element at the random index
    return brr[index];
}



int get_honeyindex_set(int honeyset[], int a, int k)
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

    fclose(fptr);   // close the file 

    int n = i;

    // select k-1 elements from arr[] randomly
    // append 'a' to set[]
    // randomly permutate set[]
    // return

    for(i=0; i<k-1; i++)
    {
        int index = (int)(2*n*drand48()) % n;

        honeyset[i] = arr[index];

        arr[index] = arr[n-1];
        n--;
    }

    honeyset[k-1] = a;

    permutate_array(honeyset, k);

    return 1;
}





int add_to_file1(char username[], int honeyset[], int k)
{
    FILE *fptr = fopen(file1, "a");

    if(fptr == NULL)
        return -1;
    

    fprintf(fptr, "%s ", username); // add usernmae

    int i;
    for(i=0; i<k; i++)  // add honeyset
        fprintf(fptr, "%d ", honeyset[i]);

    fprintf(fptr, "\n");

    fclose(fptr);


    return 1;
}


int add_to_file2(int a, char hashed[])
{
    FILE *fptr = fopen(file2, "a");

    if(fptr == NULL)
        return -1;

    fprintf(fptr, "%d:%s\n", a, hashed);

    fclose(fptr);

    return 1;
}




int get_file1_entry(char result[], char username[])
{
    FILE *fptr = fopen(file1, "r");

    if(fptr == NULL)
        return -1;
    

    char tmp[N];

    int cnt = 0;
    int found = 0;

    while(fscanf(fptr, "%s", tmp) != EOF)
    {
        cnt++;
        if(strcmp(username, tmp) == 0)
        {
            fscanf(fptr, "%[^\n]s", result);

            found = 1;
            break;
        }
    }

    fclose(fptr);

    if(found == 0)  // username not found
    {
        result[0] = '\0';
        return -2;
    }


    if(cnt <= 20)   // some honeypot account hit
        return -3;

    return 1;
}



int match_with_file2(char num[], char hashed[])
{
    int arr[MAX_K] = {0};

    int n = convert_to_int_array(arr, num);
    if(n <= 0)
        return -1;
    
    FILE *fptr = fopen(file2, "r");

    if(fptr == NULL)
        return -1;
    
    
    char line[MAX_LINE_LENGTH] = {'\0'};
    size_t a = sizeof(line);
    size_t len = 0;
    char *lineptr = line;

    int res = -1;

    while((len = getline(&lineptr, &a, fptr)) != EOF)
    {
        int index;
        char tmp[50] = {'\0'};

        sscanf(line, "%d:%s", &index, tmp);

        int i;
        for(i=0; i<n; i++)
        {
            if(arr[i] == index)
            {
                if(strcmp(hashed, tmp) == 0)
                {
                    res = index;
                    break;
                }
            }
        }

        if(res != -1)
            break;
    }

    fclose(fptr);


    return res;
}
