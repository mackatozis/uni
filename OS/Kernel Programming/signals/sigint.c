#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler (int signal);

int main (void) {
	int i;

	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		perror("signal");
		return 1;
	}

	for (i = 0; i < 1000000; printf("%d ", i++));
	return 0;
}

void sigint_handler (int signal) {
	printf("\nSIGINT has been recieved\nBye :)\n");
	exit(2);
}
