#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *lineptr = NULL;
  size_t n = 0;

  while (1 == 1) {
    printf("Enter programs to run.\n");

    ssize_t len = getline(&lineptr, &n, stdin);

    if (len == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    if (len > 0 && lineptr[len - 1] == '\n') {
      lineptr[len - 1] = '\0';
    }

    pid_t pid = fork();

    if (pid < 0) {
      perror("fork failed");
    } else if (pid == 0) {
      execlp(lineptr, lineptr, NULL);

      perror("Exec failure");
      exit(EXIT_FAILURE);
    } else {
      if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid failed");
      }
    }
  }
}
