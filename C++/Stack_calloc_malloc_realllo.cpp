#include <stdio.h>
#include <stdlib.h>

int main()
{ /// c
    int n;
    printf("Enter size of array\n");
    scanf("%d", &n);
    int *A = (int *)malloc(n * sizeof(int)); // dynamic allocated array
    for (int i = 0; i < n; i++)
    {
        A[i] = i + 1;
    }

    int *B = (int *)realloc(A, (n / 4) * sizeof(int));
    printf("prev block address = %d, new address = %d\n", A,B);

    for (int i = 0; i < n; i++)
    {
        printf("%d\n\t", B[i]);
    }

    return 0;
}
