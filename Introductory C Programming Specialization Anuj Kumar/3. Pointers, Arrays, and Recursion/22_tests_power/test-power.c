#include<stdio.h>
#include<stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void){
    unsigned int ans;

    ans = power(0,0);
    if (ans!=1){ return EXIT_FAILURE;}
    ans = power(0,1);
    if (ans!=0){return EXIT_FAILURE;}
    ans = power(0,10);
    if (ans!=0)
    {
        return EXIT_FAILURE;
    }
    
    ans = power(10,0);
    if (ans!=1){ return EXIT_FAILURE;}
    ans = power(1,0);
    if (ans!=1){ return EXIT_FAILURE;}


    ans = power(2,31);
    if (ans!=2147483648){ return EXIT_FAILURE;}
    
    ans = power(5,5);
    if (ans!=3125){ return EXIT_FAILURE;}
    ans = power(2*3,2);
    if (ans!=36){ return EXIT_FAILURE;}

    ans = power(10,5);
    if (ans !=100000){return EXIT_FAILURE;}

    return EXIT_SUCCESS;
}
