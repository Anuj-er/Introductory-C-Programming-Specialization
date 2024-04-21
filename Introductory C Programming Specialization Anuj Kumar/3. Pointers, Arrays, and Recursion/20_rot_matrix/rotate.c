#include<stdio.h>
#include<stdlib.h>



void rotate(char matrix[10][10])
{
    char temp[100];
    int count =0;
    for (int i =0; i<10;i++)
    {
        for (int j =0;j<10;j++)
        {
            temp[count] = matrix[i][j];
            count++;
        }
    }
    count =0;
    for (int k =0;k<10;k++)
    {
        for (int l =0; l<10;l++)
        {
            matrix[l][9-k] = temp[count];
            count++;
        }
    }



}