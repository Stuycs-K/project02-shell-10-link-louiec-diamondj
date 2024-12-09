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
#include <sys/wait.h>

// takes an array of arguments, returns 1 if ">" is found, 0 otherwise
int testStdoutRedirect(char** args) {
  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], ">") == 0) return 1;
  }
  return 0;
}

// takes an array of arguments, returns 1 if "<" is found, 0 otherwise
int testStdinRedirect(char** args) {
  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "<") == 0) return 1;
  }
  return 0;
}

// takes an array of arguments known to have ">" and runs the command, redirection file output as necessary
void stdoutRedirect(char** args) {
  int p = fork();
  if (p < 0) {
    perror("fork failed\n");
  } else if (p == 0) {
    int redirIndex = 0;
    while (strcmp(args[redirIndex],">") != 0) {
      redirIndex++;
    }
    args[redirIndex] = NULL;
    int file = open(args[redirIndex + 1], O_WRONLY | O_TRUNC);
    int stdout = STDOUT_FILENO;
    int backup_stdout = dup(stdout);
    dup2(file, stdout);
    execvp(args[0], args);
    dup2(backup_stdout, stdout);
  } else {
    int status;
    wait(&status);
  }
}

// takes an array of arguments known to have "<" and runs the command, redirecting input and necessary
void stdinRedirect(char** args) {
  int p = fork();
  if (p < 0) {
    perror("fork failed\n");
  } else if (p == 0) {
    int redirIndex = 0;
    while (strcmp(args[redirIndex],"<") != 0) {
      redirIndex++;
    }
    args[redirIndex] = NULL;
    FILE* file = fopen(args[redirIndex + 1], "r");
    int stdin = STDIN_FILENO;
    int backup_stdin = dup(stdin);
    dup2(fileno(file), stdin);
    fclose(file);
    execvp(args[0], args);
    dup2(backup_stdin, stdin);
  } else {
    int status;
    wait(&status);
  }
}
