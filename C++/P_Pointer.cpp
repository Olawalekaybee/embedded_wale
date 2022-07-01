#include <stdio.h>

void Incremebt(int *p) {
        *p +=(*p);
    }
int main()
{
    int d = 5;
    int* a = &d;
    int *b;
    b = a;

    printf("value of b %d\n", *b);

    /// pointer to variable.

    Incremebt(&d);

    printf("value of %d\n", d);
    


    return 0;
}
