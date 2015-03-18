#include <fcntl.h>
#include <stdio.h>

int main() {
  printf("%d", fcntl(1, F_GETFL));
  return 0;
}
