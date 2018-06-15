/*
 * The MIT License
 *
 * Copyright 2013 Alexandros Efthymiadis.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX 41

int fib(int );

main() 
{
    pid_t pid;
	int fd[2], i;
	char message[20];

	if (pipe(fd) == -1) {
		perror("pipe");
		exit(1);
	}
	
	pid = fork();	/* create child process*/
	if (pid == -1) {	/* create check */
		perror("fork");	/* fork error check*/
		exit(2);
	}

	if (pid != 0) {	/* Parent */
		/* close the reading side */
		close(fd[0]);
		/* stdout becomes fd[1] */
		dup2(fd[1], 1);
		/* close the fd[1] */
		close(fd[1]);
		for (i = 0; i < MAX; i++) {
			printf("%d\n", fib(i));
			/* Parent ignores SIGUSR1 and SIGUSR2.
			 * If Parent receives SIGINT signal
			 * he prints the last element that
			 * was send to his child.
			 */ 
			signal(SIGUSR1, SIG_IGN);
			signal(SIGUSR2, SIG_IGN);
			if (signal(SIGINT, SIG_DFL)) {
				fprintf(stderr, "I couldn't send %d", fib(i));
			}
		}
	} else {	/* Clild */
		/* close the writing side */
		close(fd[1]);
		/* stdin becomes fd[0] */
		dup2(fd[0], 0);
		/* close the fd[0] */
		close(fd[0]);

		/* Child ignores these signals */
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, SIG_IGN);

		execl("/usr/bin/sort", "sort", "-nr", (char *)NULL);
		perror("execl");
	}
}

int fib(int n)
{
	if (n < 2)
		return n;
	return (fib(n-1) + fib(n-2));
}
