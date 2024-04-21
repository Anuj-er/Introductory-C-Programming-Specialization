#include<stdio.h>
#include<stdlib.h>



int maxSeq(int * array, size_t n)
{
    if (n==0)
    {
        return 0;
    }
    int length_final = 1;

    for (int i =0;i<n;i++)
    {
        int temp = array[i];
        int length_temp = 1;
        for (int j=i+1;j<n;j++)
        {
            if (array[j]>temp)
            {
                temp = array[j];
                length_temp = length_temp +1;
            }
            else
            {
                break;
            }

        if (length_temp > length_final)
        {
            length_final = length_temp;
        }
            
        }
    }
    return length_final;
}