//Varun Chennamadhava
//Algorthims Class
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;



void merge_sort(int *a, int *aux, int length)
{
    int i, j1, j2, j3,  temp;
    if(length <= 2)
    {
        if(length == 2)
        if(a[1] < a[0])
        {   int temp = a[0];
            a[0] = a[1];
            a[1] = temp;
        }
        return;
    }
    else
    {
        merge_sort(a, aux, (length/3) );
        merge_sort(a + (length/3), aux, (length/3));
        merge_sort(a + (length/3)*2, aux, length - (length/3)*2);
        for(int i = 0, j1 = 0, j2 = (length/3), j3 = (length/3)*2; i < length;)
        {
            if(j1 < length/3 && a[j1] <= a[j2] && a[j1] <= a[j3] && j2 < (length/3)*2 && j3 < length)
                aux[i++] = a[j1++];
            else if(j2 < (length/3)*2 && a[j2] <= a[j1] && a[j2] <= a[j3] && j1 < length/3 && j3 < length)
                aux[i++] = a[j2++];
            else if(j3 < length && a[j3] <= a[j1] && a[j3] <= a[j2] && j1 < length/3 && j2 < (length/3)*2)
                aux[i++] = a[j3++];
            else if(j3 == length && a[j1] <= a[j2] && j2 < (length/3)*2 && j1 < length/3)
                aux[i++] = a[j1++];
            else if(j3 == length && a[j2] <= a[j1] && j2 < (length/3)*2 && j1 < length/3)
                aux[i++] = a[j2++];
            else if(j2 == (length/3)*2 && a[j1] <= a[j3]  && j1 < length/3 && j3 < length)
                aux[i++] = a[j1++];
            else if(j2 == (length/3)*2 && a[j3] <= a[j1] && j1 < length/3 && j3 < length)
                aux[i++] = a[j3++];
            else if(j1 == length/3 && a[j2] <= a[j3] && j3 < length && j2 < (length/3)*2 )
                aux[i++] = a[j2++];
            else if(j1 == length/3 && a[j3] <= a[j2] && j3 < length && j2 < (length/3)*2)
                aux[i++] = a[j3++];
            else if(j1 >= length/3 && j2 >= (length/3)*2 && j3 < length)
                aux[i++] = a[j3++];
            else if(j2 >= (length/3)*2 && j3 >= length && j1 < length/3 )
                aux[i++] = a[j1++];
            else if(j3 >= length && j1 >= length/3 && j2 < (length/3)*2)
                aux[i++] = a[j2++];
        }
        for( i = 0; i< length; i++)
        a[i] = aux[i];
    }
}

int main()
{  int *r, *s; long i;
    printf("Allocating Array. "); fflush(stdout);
    r = (int *) malloc(3000000 * sizeof(int));
    s = (int *) malloc(3000000 * sizeof(int));
    printf("Filling array. "); fflush(stdout);
    for( i = 0; i< 3000000; i++)
    r[i] = 3 * ((137 * i)%3000000);
    printf("Sorting. "); fflush(stdout);
    merge_sort( r, s, 3000000 );
    printf("Checking. \n"); fflush(stdout);
    for(i=0; i< 3000000; i++)
    if( r[i] != 3*i )
    {  printf("Error at %d; is %d, should be %d\n", i, r[i], 3*i );
        fflush(stdout); exit(-1);
    }
    printf("Passed Test.\n");
}
