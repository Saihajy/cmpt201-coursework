#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enter_input(char **lineptr, size_t *n, char **hist, int *filled_five);
void store_input(char *lineptr, char **hist);
void check_print(char *lineptr, char **hist);

int main() {
  char *lineptr;
  size_t n;
  char *hist[5] = {NULL};
  int filled_five = 0;
  while (1) {
    lineptr = NULL;
    n = 0;
    enter_input(&lineptr, &n, hist, &filled_five);
    check_print(lineptr, hist);
  }
}

void enter_input(char **lineptr, size_t *n, char **hist, int *filled_five) {
  printf("Enter input: ");
  ssize_t len = getline(lineptr, n, stdin);

  // Checking if it failed
  if (len == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  if (*filled_five < 5) {
    hist[*filled_five] = *lineptr;
    (*filled_five)++;
  } else {
    store_input(*lineptr, hist);
  }

  return;
}

void store_input(char *lineptr, char **hist) {
  free(hist[0]);

  for (int i = 0; i < 4; i++) {
    hist[i] = hist[i + 1];
  }

  hist[4] = lineptr;
}

void check_print(char *lineptr, char **hist) {
  if (lineptr[0] != 'p') {
    return;
  }
  if (lineptr[1] != 'r') {
    return;
  }
  if (lineptr[2] != 'i') {
    return;
  }
  if (lineptr[3] != 'n') {
    return;
  }
  if (lineptr[4] != 't') {
    return;
  }
  if (lineptr[5] != '\n') {
    return;
  }

  for (int i = 0; i < 5; i++) {
    if (hist[i] != NULL) {
      printf("%s", hist[i]);
    }
  }
}
