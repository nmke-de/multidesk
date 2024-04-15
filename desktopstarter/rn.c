#include <fcntl.h>
#include <unistd.h>

#include "main.h"

//#define abs(x) ((x) < 0 ? -(x) : (x))
#define abs(x) ((unsigned long) (x))

union ul {
	char bytes[sizeof(unsigned long)];
	unsigned long number;
};

unsigned long rn(int min, int max) {
	union ul rn;
	int fd = open("/dev/urandom", 0);
	read(fd, rn.bytes, sizeof(unsigned long));
	close(fd);
	return abs(rn.number) % max + min;
}
