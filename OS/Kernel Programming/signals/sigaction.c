#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

void sigint_handler (int signal);

int state = 0;

int main (void) {
	struct sigaction act;
	time_t now;

	act.sa_handler = sigint_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	
	if (sigaction(SIGINT, &act, NULL) == -1) {
		perror("sigaction");
		return 1;
	}

	for (;;) {
		state = 0;
		time(&now);
		printf("%s", ctime(&now));
		sleep(1);
	}
	
	return 0;
}

void sigint_handler (int signal) {
	if (state++ > 0) { //if new SIGINT recieved before sleep(5) is over
		exit(2);
	}

	printf("\nYou have 5 seconds to press ^C again to quit.\n");
	fflush(stdout);
	sleep(5);
}
