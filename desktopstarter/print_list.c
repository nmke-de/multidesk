#include "main.h"

/**
Print a list of desktops with a selection on a screen.
`offset` is an aesthetic parameter.
*/
void print_list(struct dirent ***list, int len_i, int selection, int offset){
	dslog("Entered print_list with selection ", itoa(selection, 10));
	int row = 0, col = 0;
	bsize(&row, &col);
	--row;
	bputs("Select with j/k, press Return to start, r to select random, q to cancel.\n");
	int start = max(0, selection - row + 1 + offset);
	int end = min(len_i, row + start - 1);
	for(int i = start; i < end; i++) {
		bputs((selection == i ? ">>  " : "   "), (*list)[i]->d_name, "\n");
	}
}
