#include <stdio.h>
#include <stdlib.h>

int *Add(int *a, int *b)
{
    printf("Address of a in Add=%d\n", &a);
    int *c = (int *)malloc(sizeof(int));
    *c = (*a) + (*b);
    return c;
}

int ad(int a, int b)
{
    return a + b;
}

void printhello(char *name)
{
    printf("Hello %s\n", name);
}

int main()
{
    int a = 2, b = 4;
    printf("Address of a in main = %d\n", &a);
    // int c = Add(&a,&b);
    int *ptr = Add(&a, &b);

    printf("Sum= %d\n", *ptr);

    /// function to pointer
    int c;
    int (*p)(int, int);
    p = ad;
    c = p(2, 3);
    printf("%d\n\t\b", c);

    /// 
    void (*pt)(char*);
    pt= printhello;
    pt("Sam");

    return 0;
}
