#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/*
@requires One arguements, an automata .aut
@assings ??
@ensures recognize langage 

https://www.tutorialspoint.com/cprogramming/c_file_io.html
*/
int main(int argc,char *argv[]){     
   FILE *fp;
   char buff[255];

   fp = fopen(argv[1], "r");
   fscanf(fp, "%s", buff);
   printf("1 : %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("2: %s\n", buff );
   
   fgets(buff, 255, (FILE*)fp);
   printf("3: %s\n", buff );
   fclose(fp);

   return 0;
}