#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void initialize_block(struct header *block, uint64_t size, struct header *next) {
  (*block).size = size;
  (*block).next = next;
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[256];
  ssize_t len = snprintf(buf, 256, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *start = sbrk(256);
  if (start == (void *)-1) {
    return 1;
  }

  struct header *first = (struct header *)start;
  struct header *second = (struct header *)((char *)start + 128);

  initialize_block(first, 128, NULL);
  initialize_block(second, 128, first);

  memset((char *)first + sizeof(*first), 0, 128 - sizeof(*first));
  memset((char *)second + sizeof(*second), 1, 128 - sizeof(*second));

  print_out("First block:     %p\n", &first, sizeof(first));
  print_out("Second block:      %p\n", &second, sizeof(second));
  print_out("First block size:      %lu\n", &first->size, sizeof(first->size));
  print_out("First block next:      %p\n", &first->next, sizeof(first->next));
  print_out("Second block size:     %lu\n", &second->size, sizeof(second->size));
  print_out("Second block next:     %p\n", &second->next, sizeof(second->next));

  for (size_t i = 0; i < 128 - sizeof(*first); i++) {
    unsigned char byte = *((unsigned char *)first + sizeof(*first) + i);
    char line[2] = {(char)('0' + byte), '\n'};
    write(STDOUT_FILENO, line, 2);
  }

  for (size_t i = 0; i < 128 - sizeof(*second); i++) {
    unsigned char byte = *((unsigned char *)second + sizeof(*second) + i);
    char line[2] = {(char)('0' + byte), '\n'};
    write(STDOUT_FILENO, line, 2);
  }
}
