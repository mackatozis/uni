/*
* PI calculation using the Leibniz formula:
* (1/1) - (1/3) + (1/5) - (1/7) +...+ (1/n) = pi/4 , where n is the last odd number
* 
* The process must fork a child. The child then, have to calculate PI
* and send it to its father in order to print it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUF_SZ 256
#define TERMS 100000 /*The bigger the better*/

int main (void) {
	pid_t pid;
	ssize_t n;
	int pipefd[2];
	char buf[BUF_SZ];

	//create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return EXIT_FAILURE;
	}

	//fork a child
	if ((pid = fork()) == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}
	else if (pid == 0) { //inside the child
		int i;
		long double pi = 0, den = 1, num = 1;

		close(pipefd[0]); //close read end
		
		//calculate pi/4
		for (i = 0; i < TERMS; ++i) {
			pi += num / den;
			num *= -1;
			den += 2;
		}
		pi *= 4; //convert pi/4 to pi

		sprintf(buf, "%.10Lf", pi); //convert pi to string

		//write it to the pipe
		n = write(pipefd[1], buf, strlen(buf));
		if (n != strlen(buf)) {
			perror("write");
			return EXIT_FAILURE;
		}

		close(pipefd[1]); //close write end
		return EXIT_SUCCESS;
	}
	else { //inside the parent
		int status;

		close(pipefd[1]); //close write end
		
		n = read(pipefd[0], buf, BUF_SZ); //read form the pipe

		waitpid(pid, &status, 0); //wait for child to die
		if (WEXITSTATUS(status) != EXIT_SUCCESS) {
			return EXIT_FAILURE;
		}

		if (n == -1) {
			perror("read");
			return EXIT_FAILURE;
		}
		buf[n] = '\0';

		puts(buf); //print the recieved string

		close(pipefd[0]); //close read end
		return EXIT_SUCCESS;
	}
}
