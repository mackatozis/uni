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
		char buf[256];
		int n;
		
		close(pipefd[1]); //close the write end (the child reads only)
		
		n = read(pipefd[0], buf, 256); //read what parent sent
		buf[n] = '\0';
		printf("child (%d): parent (%d) says \"%s\"\n", getpid(), getppid(), buf);
		
		close(pipefd[0]);
	}
	else { //inside the parent
		int n;
	
		close(pipefd[0]); //close the read end (the parent writes only)
		
		n = write(pipefd[1], "Hello my child", strlen("Hello my child"));
		if (n != strlen("Hello my child")) {
			perror("write");
			return 1;
		}
		
		wait(NULL); //wait for child to terminate
		
		close(pipefd[1]);
	}

	return 0;
}
