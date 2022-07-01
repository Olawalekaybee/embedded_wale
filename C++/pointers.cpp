#include <stdio.h>

int main()
{

    int a = 2;
    int b = 3;
    int c = 5;

    // printing address without pointer
    printf("%p \n", &a);
    printf("%p \n", &b);
    printf("%p \n", &c);
    printf("\n");
    // declare and assign the pointers
    int *pTA = &a;
    int *pTB = &b;
    int *pTC = &c;

    // printing address with pointer
    printf("%p \n", pTA);
    printf("%p \n", pTB);
    printf("%p \n", pTC);
    printf("\n");
    // derefrencing (process of getting the value assigned to an address)
    printf("%i \n", *pTA);
    printf("%i \n", *pTB);
    printf("%i \n", *pTC);
    printf("\n");

    // Operation // int = 4byte, char=1byte, float=4byte
    printf("%i \n", (*pTA - 1));
    printf("%i \n", (*pTB * 2));
    printf("\n");

    

    return 0;
}