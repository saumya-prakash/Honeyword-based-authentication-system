#include "headers.h"


#define MAX_LINE_LENGTH (512)

#define MAX_K (20)

#define file1 "F1"
#define file2 "F2"

#define index_file "index"


#define HONEYPOT_COUNT 2



int username_registered(char *username);

int get_random_index();

int get_honeyindex_set(int index_set[], int a, int k);

int add_to_file1(char username[], int honeyset[], int k);

int add_to_file2(int a, char hashed[]);

int get_file1_entry(char result[], char username[]);

int match_with_file2(char num[], char hashed[]);




/*===============================================================
    honeychecker functions
=================================================================*/

int set(char username[], int a);
int check(char username[], int a);