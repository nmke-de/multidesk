#include <dirent.h>
#include "BarnabasBox/barnabas.h"
#include "BarnabasBox/Itoa/itoa.h"

char *cat(const char *);
int ls(const char *, struct dirent ***);
void print_list(struct dirent***, int, int, int);

// static inline functions
static inline int min(int a, int b) {
	return (a < b ? a : b);
}
static inline int max(int a, int b) {
	return (a > b ? a : b);
}

// Logger
#define DEBUG
#ifdef DEBUG
	#include <fcntl.h>
	extern int logfd;
	#define dsloginit() logfd = open("/tmp/dslogfile", O_CREAT | O_TRUNC | O_WRONLY, 0644)
	#define dslog(...) fdprintv(logfd, cargs(__VA_ARGS__, "\n"))
	#define dslogquit() close(logfd)
#else
	#define dsloginit()
	#define dslog(...)
	#define dslogquit()
#endif
