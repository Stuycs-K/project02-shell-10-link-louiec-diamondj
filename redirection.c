#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>

int testStdoutRedirect(char** args) {
  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], ">") == 0) return 1;
  }
  return 0;
}

int testStdinRedirect(char** args) {
  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "<") == 0) return 1;
  }
  return 0;
}

void stdoutRedirect(char** args) {
  int redirIndex = 0;
  while (strcmp(args[redirIndex],">") != 0) {
    redirIndex++;
  }
  printf("redirIndex = %d\n", redirIndex);
  args[redirIndex] = NULL;
  int fd1 = open(args[redirIndex + 1], O_WRONLY);
  int stdout = STDOUT_FILENO;
  int backup_stdout = dup(stdout);
  dup2(fd1, stdout);
  execvp(args[0], args);
  dup2(backup_stdout, stdout);
}
