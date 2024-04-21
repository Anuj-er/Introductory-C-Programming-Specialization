#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main (void)
{
    int array1[]={};
    int max1 = maxSeq(array1,0);
    if (max1!=0){return EXIT_FAILURE;}

    int array2[] = {1};
    int max2 = maxSeq(array2,1);
    if (max2!=1){return EXIT_FAILURE;}


    int array3[] = {1,0};
    int max3 = maxSeq(array3,2);
    if (max3!=1){return EXIT_FAILURE;}

    int array4[] = { 1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
    int max4 = maxSeq(array4,10);
    if (max4!=4){return EXIT_FAILURE;}   

    int array5[] = { 1, 3, 3, 3, 3, 3, 2, 4, 6, 9};
    int max5 = maxSeq(array5,10);
    if (max5!=4){return EXIT_FAILURE;}   

    int array6[] = {-5,-3,-2,0,1,2,3,2,9};
    int max6 = maxSeq(array6,9);
    if (max6!=7){return EXIT_FAILURE;}   

    return EXIT_SUCCESS;
}