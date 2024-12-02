#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "parse.h"

int main(){
  char buffer[256];
  fgets(buffer,255,stdin);
  char* args[16];
  parse_args(buffer,args);
  execvp(args[0],args);
  return 0;
}
