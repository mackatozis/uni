#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {
	pid_t pid;
	int status, i;
	
	if ((pid = fork()) == -1) {
		perror("fork");
		return 1;
	}
	else if (pid == 0) { //inside the child
		for (i = 0; i < 1000; ++i) {
			printf("child (%d): %d\n", getpid(), i);
		}
		
		return 2; //the parent will exit with status code 2
	}
	else { //inside the parent
		for (i = 0; i < 1000; ++i) {
			printf("parent (%d): %d\n", getpid(), i);
		}
		
		waitpid(pid, &status, 0); //wait for child to finish
		printf("Child returned with status code: %d\n", WEXITSTATUS(status));
		
		return 3; //the parent will exit with status code 3
	}
}
