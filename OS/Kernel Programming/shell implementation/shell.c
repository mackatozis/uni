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

/* Simple Linux Shell implementation */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 80

#define blue  "\033[1;34m" 
#define black  "\033[1;00m" 

int parse(char *line, char *argv[]);
void execute(char **argv);

int main() 
{
        char buf[INPUT_SIZE], *argv[INPUT_SIZE];
		int countArgs;
 
        while(1) {
                // print prompt
                printf("%s$ %s", blue, black);
				// get input
				fgets(buf, sizeof(buf), stdin);
				if(strcmp(buf, "quit\n") == 0)
					exit(0);

				countArgs = parse(buf, argv);

				if(strcmp(*argv, "cd") == 0)
					chdir(argv[1]);
				else
					execute(argv);
        }
        return 0;
}


int parse(char *line, char *argv[])
{
	int countArgs = 0;
	char *Ptr = line;

	while(*Ptr != '\0')
	{
		*argv = Ptr;
		countArgs++;

		while(*Ptr != ' ' && *Ptr != '\t' && *Ptr != '\0' && *Ptr != '\n')	
			Ptr++;

		while((*Ptr == ' ' || *Ptr == '\t' || *Ptr == '\n'))
		{
			*Ptr = '\0';
			Ptr++;
		}
		argv++;
	}
	*argv = '\0';
	return countArgs;
}


void execute(char **argv)
{
	pid_t pid;
	short flag = 0;
	char *temp;
	temp = (char*) malloc (strlen(*argv)+10);

	if (*argv[0] != '/')
	{
		strcpy(temp, "/bin/");
		strcat(temp, *argv);

		flag = 1;
	}

	pid = fork();
	if(pid < 0)
	{
		printf("Error occured");
		exit(-1);
	}
	else if(pid == 0)
	{
		if (flag == 1)
		{
		  	if (execvp(temp, argv) == -1)
			{
				strcpy(temp, "/usr/bin/");
				strcat(temp, *argv);
			}	
			if (execvp(temp, argv) == -1)
			{
				perror("execvp failed");
				exit(127);	// Possible problem with $PATH or a typo
			}
		}		
		else
			if (execvp(*argv, argv) == -1)
			{
				perror("execvp failed");
				exit(127);	// Possible problem with $PATH or a typo
			}
	}
	else
	{
		wait(NULL);
	}
	free(temp);
}
