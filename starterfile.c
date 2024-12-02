#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void parse_args( char * line, char ** arg_ary ){
  int i = 0;
  strcat(line," \0");
  while(i != -1){
    char * token;
    token = strsep( &line, " " );
    if (strcmp(token,"\0")==0){
      arg_ary[i]=NULL;
      i = -1;
      break;
    }
    arg_ary[i]=token;
    i++;
  }
}
