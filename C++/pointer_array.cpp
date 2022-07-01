#include <stdio.h>

int main()
{
    int A[] = {2, 4, 5, 6, 7};
    int i = 0;
    for (int i = 0; i < 5; i++)
    {
        printf("Value of A[i] %d\n", *(A + i));       //  deferencing  a pointer array
        //printf("Value of A[i] %d\n = %d\n", (A + i)); // getting address  assigned to an arrray
    }

    int disp[2][3];
    int j, k;
    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 3; k++)
        {
           printf("Enter value for disp[%d][%d]:\n", j, k);
           scanf("%d", &disp[i][j]);
        
        }
    }
    printf("two dimensional Array element:\n");
    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 3; k++) {
           printf("%d", disp[j][k]);
           if(k==2) {
            printf("\n");
           }
        }
    }

    return 0;
}
