#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   int val;
   char str[20];
   
   strcpy(str, "0987654321");
   val = atoi(str);
   printf("String value = %s, Int value = %d\n", str, val);

   strcpy(str, "Olawale");
   val = atoi(str);
   printf("String value = %s, Int value = %d\n", str, val);

   return(0);
}
