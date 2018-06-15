#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler (int signal);

pid_t pid;

int main (void) {

	if ((pid = fork()) == -1) {
		perror("fork");
		return 1;
	}
	else if (pid == 0) { //inside the child
		int i;
	
		signal(SIGINT, SIG_IGN); //for this to work, the child must ignore the SIGINT signal
		
		for (i = 0; i < 20; ++i) {
			printf("Child says: %d\n", i);
			sleep(1);
		}
		
		return i;
	}
	else { //inside the parent
		int status;
		
		signal(SIGINT, sigint_handler);
		
		waitpid(pid, &status, 0); //wait for child to terminate normaly
		printf("Child terminated with code: %d\n", WEXITSTATUS(status));
	}

	return 0; //only the parent will reach this point
}

void sigint_handler (int signal) { //with each ^C the parent will alternate start/stop the child, until the child is terminated normaly
	static int i = 0;
	
	if (i == 0) {
		i = 1;
		kill(pid, SIGSTOP);
	}
	else {
		i = 0;
		kill(pid, SIGCONT);
	}
}


