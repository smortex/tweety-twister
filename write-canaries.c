#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "canaries.h"

int
main(int argc, char *argv[])
{
    char block[BLOCKSIZE];
    const char canaries[] = CANARIES;

    if (argc != 2) {
	errx(EXIT_FAILURE, "usage: %s device\n", argv[0]);
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR)) < 0) {
	err(EXIT_FAILURE, "open");
    }

    if (read(fd, block, sizeof(block)) != sizeof(block)) {
	err(EXIT_FAILURE, "read");
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
	err(EXIT_FAILURE, "lseek");
    }

    memcpy(block, canaries, sizeof(canaries));

    if (write(fd, block, sizeof(block)) != sizeof(block)) {
	err(EXIT_FAILURE, "write");
    }

    if (lseek(fd, -sizeof(block), SEEK_END) < 0) {
	err(EXIT_FAILURE, "lseek");
    }

    if (read(fd, block, sizeof(block)) != sizeof(block)) {
	err(EXIT_FAILURE, "read");
    }

    if (lseek(fd, -sizeof(block), SEEK_END) < 0) {
	err(EXIT_FAILURE, "lseek");
    }

    memcpy(block + sizeof(block) - sizeof(canaries), canaries, sizeof(canaries));

    if (write(fd, block, sizeof(block)) != sizeof(block)) {
	err(EXIT_FAILURE, "write");
    }

    close(fd);

    return 0;
}
