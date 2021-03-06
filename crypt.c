#include "crypt.h"


/* This function returns MD5 hash value of a given input string */
void get_MD5(unsigned char *result, const unsigned char *input)
{
    unsigned char tmp[50] = {'\0'};

    MD5(input, strlen((const char*) input), tmp);   // get MD5 in binary form

    int i, j, a;

    result[32] = '\0';
    a = 31;

    for(i=15; i>=0; i--)    // convert the binary form into 32-character ASCII form
    {
        unsigned char c = tmp[i];
        for(j=0; j<2; j++)
        {
            unsigned char b = c & 15;
            c >>= 4;

            if(b < 10)  // vaule lies in ranges 0-9 -> convert to corresponding digit
                b += 48;
            
            else        // value lies in range 10-15 -> convert to alphabet (a-f)
                b += 87;
            
            result[a] = b;
            a--;
        }
    }

    return ;
}
