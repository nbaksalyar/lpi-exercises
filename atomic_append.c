#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: atomic_append file numbytes [x]\n");
    exit(EXIT_SUCCESS);
  }

  int numbytes = atoi(argv[2]);
  char noappend = (argc > 3 && *argv[3] == 'x');

  int fd = open(argv[1], O_CREAT | O_WRONLY | (noappend ? 0 : O_APPEND), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

  for (int i = 0; i < numbytes; i++) {
    if (noappend) {
      lseek(fd, 0, SEEK_END);
    }
    write(fd, "x", 1);
  }

  close(fd);
}
