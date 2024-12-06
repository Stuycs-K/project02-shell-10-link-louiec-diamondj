#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parse.h"
#include "pipe.h"
#include "directory.h"
#include "redirection.h"

int main(){
  char buffer[256];
  char modBuff[256];
  char pipeBuff[256];
  while (1) {
    prompt();
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
