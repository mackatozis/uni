#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (void) {

	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1) { //create the pipe
		perror("pipe");
		return 1;
	}
	
	if ((pid = fork()) == -1) {
		perror("fork");
		return 1;
	}
	else if (pid == 0) { //inside the child
	/*The child will write stdout and the stdout will be redirected to the write end of the pipe*/

	close(pipefd[0]); //first we close the read end of the pipe
	dup2(pipefd[1], STDOUT_FILENO); //now STDOUT_FILENO is nothing more than a copy of pipefd[1]
	close(pipefd[1]); //now we can close pipefd[1]
	
	printf("%d-%d-%d %d:%d:%d", 21, 5, 2000, 12, 52, 32);

	}
	else { //inside the parent
	/*The parent will read stdin and the stdin will be redirected to the read end of the pipe*/
	
	int day, month, year, hour, minute, second;
	
	close(pipefd[1]); //first we close the write end of the pipe
	dup2(pipefd[0], STDIN_FILENO); //now STDIN_FILENO is nothing more than a copy of pipefd[0]
	close(pipefd[0]); //now we can close pipefd[0]
	
	scanf("%d-%d-%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second);
	printf("parent (%d): child (%d) said: %d-%d-%d %d:%d:%d\n", getpid(), pid, day, month, year, hour, minute, second);
	}

	return 0;
}
