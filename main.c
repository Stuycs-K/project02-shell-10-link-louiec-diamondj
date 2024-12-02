#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main(){
  char buffer[256];
  fgets(buffer,255,stdin);
  printf("%s\n",buffer);
  return 0;
}
