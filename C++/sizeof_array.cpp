#include <stdio.h>

void c(int *a)
{
    int i, j;

    for (int i = 0; i < 2; i++)
    {
       for (int j = 0; j < (sizeof(a) / sizeof(a[0])); j++)
        {
            int sum = ++a[i];
            printf("%d\n", sum);
        }
    }
}

int main()
{

    // int arr[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
   
    
   // c(arr, 3, 0);
    // int a=sizeof(arr[3]);

    // printf("%d\n", a);

    return (0);
}