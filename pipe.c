#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*Takes a string, returns void
Separates the user inputted string by the pipe, then popens the first command in read mode to get the output and popens the second command in write mode to give in the output from first command*/
void piper(char * args){
  char * second_cmd = args;
  char * first_cmd = strsep(&second_cmd,"|");
  FILE * input = popen(first_cmd,"r");
  char data[256];
  FILE * file = popen(second_cmd,"w");
  while(fgets(data,sizeof(data),input) != NULL){
    fputs(data,file);
  }
  fclose(input);
  fclose(file);
}
