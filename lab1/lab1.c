#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *lineptr = NULL;
  size_t n = 0;

  while (1 == 1) {
    printf("Please enter some text: ");

    ssize_t len = getline(&lineptr, &n, stdin);

    if (len == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    printf("Tokens:\n");

    char *buff;
    int notempty = 0;

    char *str = strtok_r(lineptr, " ", &buff);

    while (str != NULL) {
      notempty++;
      printf("   %s\n", str);
      str = strtok_r(NULL, " ", &buff);
    }

    if (notempty == 0) {
      printf("No input enter!\n");
    }
  }
  free(lineptr);

  return 0;
}
