#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  while (1) {
    sleep(3);
    printf("Still sleeping\n");
  }
}
