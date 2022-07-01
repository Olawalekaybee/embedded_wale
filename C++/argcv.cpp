#include<stdio.h>
  
int main(int argc,char* argv[])
{
    int counter;
    printf("Program Name Is: %s",argv[0]);
    if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d\n",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }
      int i =0; int value = 2;
    for(i = 0; i<5; i++){
        value+= value;
       printf("number value:%d\t\n", value);
    }  
    int val = 1;
    for(i = 0; i<5; i++){
        val+= val;
       printf("number value:%d\t\n", val);
    }
    return 0;
}