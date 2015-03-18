#include <fcntl.h>

int main(int argc, char *argv[]) {
  int f = open(argv[1], O_WRONLY | O_APPEND);
  lseek(f, 0, SEEK_SET);
  write(f, "hello", 5);
  pwrite(f, "hello", 5, 0);
  close(f);
}
