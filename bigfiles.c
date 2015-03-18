#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int fd;
  off_t off;
  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("%s pathname offset\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  off = atoll(argv[2]);
  lseek(fd, off, SEEK_SET);
  write(fd, "test", 4);
  exit(EXIT_SUCCESS);
}
