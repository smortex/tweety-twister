#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "canaries.h"

int
main(int argc, char *argv[])
{
    const char canaries[] = CANARIES;

    if (argc != 2) {
	errx(EXIT_FAILURE, "usage: %s device\n", argv[0]);
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR)) < 0) {
	err(EXIT_FAILURE, "open");
    }

    if (write(fd, canaries, sizeof(canaries)) != sizeof(canaries)) {
	err(EXIT_FAILURE, "write");
    }

    if (lseek(fd, -sizeof(canaries), SEEK_END) < 0) {
	err(EXIT_FAILURE, "lseek");
    }

    if (write(fd, canaries, sizeof(canaries)) != sizeof(canaries)) {
	err(EXIT_FAILURE, "write");
    }

    close(fd);

    return 0;
}
