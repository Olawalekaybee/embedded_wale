#include <stdio.h>

void print(char* d) {
    int i =0;
    while(d[i] !='\0'){
        printf("%s\n\t", d);
        i++;
    }
    printf("\n");

}
// void multi_Array(int* a){
// int i, j, k;
//  //i=k=j=0;
 
// for(i =0; i<(sizeof(a)/sizeof(a[0])); i++){
//     for(j = 0; j<((sizeof(a)/sizeof(a[0])); j++) {
//      int* status[][] = { } ;
//        printf("%d\n\t", *status);
//        c=true;
//     }
// }



int main()
{
    char C[5];
    C[0] = 'B';
    C[1] = 'A';
    C[2] = 'L';
    C[3] = 'O';
    C[4] = '\0';

    printf("%s\n", C); 

    char d[20] = "Hello";
    print(d);

   

    return 0;
}