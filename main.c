#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parse.h"

int main(){
  char buffer[256];
  char modBuff[256];
  while (1) {
    fgets(buffer,255,stdin);
    sscanf(buffer, "%[^\n]", modBuff);
    char* args[16];
    parse_args(modBuff,args);
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
  return 0;
}
