#include<stdio.h>
#include<stdlib.h>

int main()
{
    //in c lang
    int a ;
    int*p;
    p=(int*)malloc(sizeof(int));
    *p=10;
    free(p);

    /// saving array in malloc
    p=(int*)malloc(20*sizeof(int));

    //in c++

   int a;
   int *p;
   p= new int;
   *p = 10;
   delete p;
   //array format

   p = new int[20];
   delete[]p;




    return 0;
}
