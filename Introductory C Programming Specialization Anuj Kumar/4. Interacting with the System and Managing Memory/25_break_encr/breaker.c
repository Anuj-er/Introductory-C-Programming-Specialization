#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int decrypt(FILE *f)
{
    int key = 0;
    int array_char[256]={0};
    char c;
    while ((c=fgetc(f))!= EOF)
    {
        if(isalpha(c))
        {
            int idx = c;
            array_char[idx] = array_char[idx]+1;
        }
    }
    int index=0;
    for (int i =0; i<256;i++)
    {
        if (array_char[i]>=array_char[index])
        {
            index =i;
        }
    }
    int temp = index -'a';
    if (temp>=0 && temp <=3)
    {
        key = 22 +temp;
    }
    else
    {
        key = temp -4;
    }
    
    return key;

}


int main(int argc,char ** argv)
{
    if (argc !=2)
    {
        fprintf(stderr,"not enough arguments\n");
        return EXIT_FAILURE;
    }
    FILE *f = fopen(argv[1],"r");
    if (f==NULL){
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    int key = decrypt(f);
    printf("%d\n",key);
    if (fclose(f) != 0){
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}