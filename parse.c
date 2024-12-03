#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void parse_args( char * line, char ** arg_ary ){
  int i = 0;
  while((arg_ary[i] = strsep(&line, " "))){
    i++;
  }
  arg_ary[i] = NULL;
}
