#include<stdio.h>
#include<stdlib.h>

unsigned power (unsigned x, unsigned y)
{
    if (y==0)
    {
        return 1;
    }

    return x*power(x,y-1);
}













































//This code is written by Anuj CSE 1st year
