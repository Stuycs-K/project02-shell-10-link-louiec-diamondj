#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parse.h"

void cd(char ** args);
<<<<<<< HEAD
void piper(char * args);
void prompt();
=======
void prompt();
void piper(char * args);
>>>>>>> refs/remotes/origin/main

int main(){
  char buffer[256];
  char modBuff[256];
  char pipeBuff[256];
  while (1) {
    prompt();
<<<<<<< HEAD
=======
    fflush(stdout);
>>>>>>> refs/remotes/origin/main
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

<<<<<<< HEAD
=======
//Takes no arguments, returns void, and prints the prompt.
void prompt(){
  long path_max;
  size_t size = 256;
  char *buf;
  char *ptr;
  //ptr = strcat("/",getcwd(buf,size));
  //printf("%s\n",strsep(&ptr,getenv("HOME")));
  ptr = getcwd(buf,size);
  printf("~/%s/$ ",ptr);
  free(ptr);
  //printf()
  //free(ptr);
}

>>>>>>> refs/remotes/origin/main
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

//Takes no arguments, returns void, and prints the prompt.
void prompt(){
  char buff[256];
  char * temp;
  getcwd(buff,sizeof(buff));
  const char * home = getenv("HOME");
  temp = buff;
  temp += strlen(home);
  printf("~%s$ ",temp);
}
