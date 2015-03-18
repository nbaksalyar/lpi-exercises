#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main (int argc, char **argv) {
  int f, i;
  char buf[128];

  f = open("test.txt", O_CREAT | O_WRONLY);

  if (f == -1) {
    printf("%s error", strerror(errno));
    close(f);

    return 1;
  }

  for (i = 0; i < 128; i++) {
    buf[i] = 'a';
  }

  write(f, buf, 128);

  close(f);

  return 0;
}
