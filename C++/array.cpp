#include<stdio.h>

int SumofElements(int *A, int size){ //or A[0];
 int i, sum = 0;

 for(i=0; i<size; i++ ) {
    sum += A[i];
 }
 return sum;
}

int main()
{
    int A[] = {1, 2, 3, 4, 5};
    int size= sizeof(A)/sizeof(A[0]);
    int Total = SumofElements(A, size);
    printf("sum of elements = %d\n\t",Total);
    return 0;
}
