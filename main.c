#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parse.h"

void cd(char ** args);
void prompt();

int main(){
  char buffer[256];
  char modBuff[256];
  while (1) {
    prompt();
    long path_max;
    size_t size;
    char *buf;
    char *ptr;
    path_max = pathconf(".", _PC_PATH_MAX);
    if (path_max == -1){
      size = 1024;
    }else if (path_max > 10240){
      size = 10240;
    }else{
      size = path_max;
    }
    //ptr = strcat("/",getcwd(buf,size));
    //printf("%s\n",strsep(&ptr,getenv("HOME")));
    //printf()
    //free(ptr);
    fgets(buffer,255,stdin);
    sscanf(buffer, "%[^\n]", modBuff);
    char* cmds[16];
    char* args[16];
    parse_cmds(modBuff,cmds);
    for (int i = 0; cmds[i] != NULL; i++) {
      parse_args(cmds[i],args);
      if(strcmp("exit",args[0])==0) exit(0);
      if(strcmp("cd",args[0])==0){
        cd(args);
        continue;
      }
      pid_t p = fork();
      if (p < 0) {
        perror("fork failed\n");
      } else if (p == 0) {
        execvp(args[0], args);
      } else {
        int status;
        wait(&status);
      }
    }
  }
  return 0;
}
//Takes an array of strings, returns void, and changes current directory
void cd(char ** args){
  const char * home = getenv("HOME");
  if(args[1] == NULL){
    chdir(home);
  }
  else{
    chdir(args[1]);
  }
}

//Takes no arguments, returns void, and prints the prompt.
void prompt(){
  long path_max;
  size_t size = 256;
  char *buf;
  char *ptr;
  printf("%s\n",getcwd(buf,size));
  ptr = getcwd(buf,size);
  /*
  while (strcmp(strsep(&ptr,"/"),getenv("HOME"))!=0) {
    printf("hi");
  }
  */
  printf("~/%s/$ ",ptr);
  free(ptr);
}
