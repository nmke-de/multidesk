#include "main.h"

#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#define barnabas(...) binit();{__VA_ARGS__}bquit();

extern char **environ;
int logfd;

static const int offset = 2;

int main(int argc, char **argv) {
	// Get environment variable DESKTOP_LIST
	const char *desktoplist = getenv("DESKTOP_LIST");
	if (!desktoplist) {
		logln("Please set the DESKTOP_LIST environment variable!");
		_exit(1);
	}

	// Check whether a desktop is already running
	const char *display = getenv("DISPLAY");
	const char *wayland_display = getenv("WAYLAND_DISPLAY");
	const char *desktop_started = getenv("DESKTOP_STARTED");
	if (display || wayland_display || desktop_started) {
		logln("A desktop is already running – exiting.");
		_exit(4);
	}


	// Initialize logger
	dsloginit();

	// Selection of desktop
	int selection = 0;
	// List of desktops
	struct dirent ***desktops = malloc(0);
	int n_desktops = ls(desktoplist, desktops);

	dslog("Found ", itoa(n_desktops, 10), "desktops");

	// BarnabasBox UI
	barnabas (
		dslog("Started BarnabasBox UI");
		int rows, cols;
		print_list(desktops, n_desktops, selection, offset);
		dslog("Printed desktops first time.");
		for (char in[2] = {0, 0};; read(STDIN_FILENO, in, 1)) {
			dslog("Read code ", itoa(*in, 10));
			bsize(&rows, &cols);
			// Evaluate input
			switch (*in) {
			case 'k':
				selection = max(0, selection - 1);
				break;
			case 'j':
				selection = min(n_desktops - 1, selection + 1);
				break;
			case 'r':
				selection = rn(0, n_desktops - 1);
			case '\n':
				goto eval;
			case 'q':
				bquit();
				logln("No desktop selected.");
				dslogquit();
				// Make sure this program won't be called recursively in this case.
				setenv("DESKTOP_STARTED", "yes", 1);
				chdir(getenv("HOME"));
				execvp("get_login", (char * const*) cargs("get_login"));
				_exit(2);
			default:
				continue;
			}
			bwash();
			print_list(desktops, n_desktops, selection, offset);
		}
eval:
	)
	
	char *desktopname = (*desktops)[selection]->d_name;
	
	// Register desktop to .loaded
	char registry[strlen(desktoplist) + 9];
	strncpy(registry, desktoplist, strlen(desktoplist));
	strncpy(registry + strlen(desktoplist), "/.loaded", 9);
	int regfd = open(registry, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fdprintv(regfd, cargs(desktopname, "\n"));
	close(regfd);
	
	// Execute desktop
	char buf[strlen(desktoplist) + strlen(desktopname) + 9];
	strncpy(buf, desktoplist, strlen(desktoplist));
	buf[strlen(desktoplist)] = '/';
	strncpy(buf + strlen(desktoplist) + 1, desktopname, strlen(desktopname));
	strncpy(buf + strlen(desktoplist) + strlen(desktopname) + 1, "/main.sh", 8);
	buf[strlen(desktoplist) + strlen(desktopname) + 9] = 0;
	dslogquit();
	execve(buf, (char * const*)cargs(buf), environ);
	logln("Fatal error when executing ", desktopname, "/main.sh – exiting.");
	_exit(3);
}
