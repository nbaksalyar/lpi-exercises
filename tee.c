#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

#define VERSION "0.2.1"

static const int BUFFER_SIZE = 2048;

extern int optind, errno;

int tee(const char *dstfile, const int append) {
  const int appendflags = (append ? O_APPEND : 0);
  const mode_t defaultmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  const int dest = open(dstfile, O_CREAT | O_WRONLY | (appendflags), defaultmode);
  if (dest == -1) {
    fprintf(stderr, "error opening output file: %s\n", strerror(errno));
    return 1;
  }

  char buf[BUFFER_SIZE];
  int numread = 0;

  while ((numread = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0) {
    if (write(dest, buf, numread) == -1) {
      fprintf(stderr, "error writing to output file: %s\n", strerror(errno));
      return 1;
    }
    write(STDOUT_FILENO, buf, numread);
  }

  if (close(dest) == -1) {
    fprintf(stderr, "error closing output file: %s\n", strerror(errno));
    return 1;
  }

  return 0;
}

static void print_usage(char *progname) {
  printf("usage: %s [options] [output file] \n"
	 " -a --append: do not truncate the output file \n"
	 " -v --version: show version of this program \n"
	 " -h --help: show this message\n", progname);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 0;
  } else {
    int opt, append = 0;

    const struct option options[] = {
      {"append", 0, NULL, 'a'},
      {"help", 0, NULL, '?'},
      {"version", 0, NULL, 'v'},
      {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "av?", &options[0], NULL)) != -1) {
      switch (opt) {
      case 'a':
	append = 1;
	break;
      case 'v':
	printf("tee v " VERSION " by nbaksalyar\n");
	return 0;
      case '?':
	print_usage(argv[0]);
	return 0;
      }
    }

    if (optind >= argc) {
      fprintf(stderr, "please specify a filename to output data\n");
      return EXIT_FAILURE;
    }

    if (tee(argv[optind], append) > 0) {
      return EXIT_FAILURE;
    }

    return 0;
  }
}
