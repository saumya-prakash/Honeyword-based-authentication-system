#include "utilities.h"

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
