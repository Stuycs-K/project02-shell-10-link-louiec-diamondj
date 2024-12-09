#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

// takes string of potentially multiple commands and a char** to sort the commands
// each command (separated by semicolons) is put into a unique index of the char** cmd_ary
void parse_cmds(char* line, char** cmd_ary) {
  int i = 0;
  while ((cmd_ary[i] = strsep(&line, ";"))) {
    i++;
  }
  cmd_ary[i] = NULL;
}

// takes string of potentially multiple arguments in one command and a char** to sort the arguments
// each argument (separated by spaces) is put into a unique index of the char** arg_ary
void parse_args(char* line, char** arg_ary){
  int i = 0;
  while((arg_ary[i] = strsep(&line, " "))){
    i++;
  }
  arg_ary[i] = NULL;
}
