#include <stdio.h>
#include <math.h>
#include<stdlib.h>

int compare(int a, int b){
    if(a>b) return -1;
    return 1;
}
int compares(const void* a, const void* b){
    int A = *((int*)a); // typecasting to int* and getting value
    int B = *((int*)b);
    return A-B;
}

void BubbleSort(int *A, int n, int(*compare)(int, int))
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (compare(A[j] , A[j + 1]) > 0)
            {
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int i, A[] = {3, 2, 1, 5, 6, 4};
    int d[] = {3, -2, 1, 5, -6, 4};
    BubbleSort(A,6, compare);
    for(int i=0; i<6; i++) printf("%d\n", A[i]);printf("\n");
    qsort(d,6,sizeof(int), compares);
    for(int i=0; i<6; i++) printf("%d\n", d[i]);
    return 0;
}
