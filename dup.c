#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  const char *filename = (argc > 1 ? argv[1] : "stdout.log");
  const int superfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH);
  
  printf("closing fd %d\n", STDOUT_FILENO);

  if (close(STDOUT_FILENO) == -1) {
    err(STDOUT_FILENO, NULL);
    return -1;
  }

  const int newstdout = fcntl(superfile, F_DUPFD, STDOUT_FILENO);

  if (newstdout < 0) {
    err(STDOUT_FILENO, NULL);
    return -1;
  }

  printf("%d\n", newstdout);

  printf("hello world! this is an output to STDOUT, but really it should be in file stdout.log\n");

  return 0;
}
