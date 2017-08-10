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
    char canaries[] = CANARIES;
    const char canaries_ref[] = CANARIES;

    if (argc != 2) {
	errx(EXIT_FAILURE, "usage: %s device\n", argv[0]);
    }

    int fd;
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
	err(EXIT_FAILURE, "open");
    }

    if (read(fd, canaries, sizeof(canaries)) != sizeof(canaries)) {
	err(EXIT_FAILURE, "read");
    }

    if (memcmp(canaries, canaries_ref, sizeof(canaries)) != 0) {
	errx(EXIT_FAILURE, "Wrong canaries at beginning of device");
    }

    if (lseek(fd, -sizeof(canaries), SEEK_END) < 0) {
	err(EXIT_FAILURE, "lseek");
    }

    if (read(fd, canaries, sizeof(canaries)) != sizeof(canaries)) {
	err(EXIT_FAILURE, "read");
    }

    if (memcmp(canaries, canaries_ref, sizeof(canaries)) != 0) {
	errx(EXIT_FAILURE, "Wrong canaries at end of device");
    }

    close(fd);

    printf("Disk look OK\n");

    return 0;
}
