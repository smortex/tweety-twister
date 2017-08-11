#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "canaries.h"

int
main(int argc, char *argv[])
{
    char block[BLOCKSIZE];
    const char canaries_ref[] = CANARIES;

    if (argc != 2) {
	errx(EXIT_FAILURE, "usage: %s device\n", argv[0]);
    }

    int fd;
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
	err(EXIT_FAILURE, "open");
    }

    if (read(fd, block, sizeof(block)) != sizeof(block)) {
	err(EXIT_FAILURE, "read");
    }

    if (memcmp(block, canaries_ref, sizeof(canaries_ref)) != 0) {
	errx(EXIT_FAILURE, "Wrong canaries at beginning of device");
    }

    if (lseek(fd, -sizeof(block), SEEK_END) < 0) {
	err(EXIT_FAILURE, "lseek");
    }

    if (read(fd, block, sizeof(block)) != sizeof(block)) {
	err(EXIT_FAILURE, "read");
    }

    if (memcmp(block + sizeof(block) - sizeof(canaries_ref), canaries_ref, sizeof(canaries_ref)) != 0) {
	errx(EXIT_FAILURE, "Wrong canaries at end of device");
    }

    close(fd);

    printf("Disk look OK\n");

    return 0;
}
