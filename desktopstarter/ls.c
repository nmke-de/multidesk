#include <stdlib.h>
#include <sys/stat.h>

#include "main.h"

/**
Helper function that returns true if `entry` is a directory.
*/
static int filter(const struct dirent *entry) {
	dslog("Checking out ", entry->d_name);
	if (*(entry->d_name) == '.')
		return 0;
	static struct stat sb;
	// Check existence of file
	if (stat(entry->d_name, &sb) < 0)
		return 0;
	// Check if file is directory
	int res = S_ISDIR(sb.st_mode);
	if (!res)
		dslog(entry->d_name, " is not a directory.");
	return res;
}

/**
Return a list of directory entries of directory `dirname`.
*/
int ls(const char *dirname, struct dirent ***entries) {
	dslog("Entered ls()");
	chdir(dirname);
	dslog("Changed directory to ", dirname);
	int res = scandir(".", entries, filter, alphasort);
	dslog("Completed scandir() call with ", itoa(res, 10), " entries found.");
	return res;
}
