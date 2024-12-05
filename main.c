#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parse.h"
#include "redirection.h"

void cd(char ** args);
void piper(char * args);

int main(){
  char buffer[256];
  char modBuff[256];
  char pipeBuff[256];
  while (1) {
    //Prompt
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
    ptr = getcwd(buf,size);
    printf("%s/$ ",ptr);
    //free(buf);
    fgets(buffer,255,stdin);
    sscanf(buffer, "%[^\n]", modBuff);
    strcpy(pipeBuff,modBuff);
    char* cmds[16];
    char* args[16];
    parse_cmds(modBuff,cmds);
    for (int i = 0; cmds[i] != NULL; i++) {
      parse_args(cmds[i],args);
      if(strchr(pipeBuff,'|') || strstr(pipeBuff," |") || strstr(pipeBuff,"| ") || strstr(pipeBuff," | ")){
        piper(pipeBuff);
        continue;
      }
      if(strcmp("exit",args[0])==0) exit(0);
      if(strcmp("cd",args[0])==0){
        cd(args);
        continue;
      }
      if (testStdoutRedirect(args)) {
        stdoutRedirect(args);
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
