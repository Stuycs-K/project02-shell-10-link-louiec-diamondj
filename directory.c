#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Takes an array of strings, returns void, and changes current directory when you type cd
void cd(char ** args){
  const char * home = getenv("HOME");
  if(args[1] == NULL){
    chdir(home);
  }
  else{
    chdir(args[1]);
  }
}

//Takes no arguments, returns void, and prints the prompts by getting cwd then moving to the part after the home directory.
void prompt(){
  char buff[256];
  char * temp;
  getcwd(buff,sizeof(buff));
  const char * home = getenv("HOME");
  if(strlen(buff) < strlen(home)){
    printf("%s",buff);
  }
  else{
    temp = buff;
    temp += strlen(home);
    printf("~%s$ ",temp);
  }
  fflush(stdout);
}
