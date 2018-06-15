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

#define NORMAL 				00
#define OUTPUT_REDIRECTION 	11
#define INPUT_REDIRECTION 	22
#define PIPELINE 			33
#define BACKGROUND			44
#define OUTPUT_APP	55

#define blue  "\033[1;34m" 
#define black  "\033[1;00m" 

int parse(char *, char **, char **, int *);
void chop(char *);
void execute(char **, int, char **);

int main() 
{
        char buf[INPUT_SIZE], *argv[INPUT_SIZE], *supplement = NULL;
		int countArgs, mode;
 
        while(1) 
		{
				mode = NORMAL;
                // print prompt
                printf("%s$ %s", blue, black);
				// get input
				fgets(buf, sizeof(buf), stdin);
				if(strcmp(buf, "quit\n") == 0)
					exit(0);

				countArgs = parse(buf, argv, &supplement, &mode);

				if(strcmp(*argv, "cd") == 0)
					chdir(argv[1]);
				else
					execute(argv, mode, &supplement);
        }
        return 0;
}


int parse(char *line, char *argv[], char **supplementPtr, int *modePtr)
{
	int countArgs = 0, terminate = 0;
	char *Ptr = line;

	while(*Ptr != '\0' && terminate == 0)
	{
		*argv = Ptr;
		countArgs++;

		while(*Ptr != ' ' && *Ptr != '\t' && *Ptr != '\0' && *Ptr != '\n' && terminate == 0)
		{
			switch(*Ptr)
			{
				case '&':
					*modePtr = BACKGROUND;
					break;
				case '>':
					*modePtr = OUTPUT_REDIRECTION;
					*argv = '\0';
					Ptr++;
					if(*Ptr == '>')
					{
						*modePtr = OUTPUT_APP;
						Ptr++;
					}
					while(*Ptr == ' ' || *Ptr == '\t')
						Ptr++;
					*supplementPtr = Ptr;
					chop(*supplementPtr);
					terminate = 1;
					break;
				case '<':
					*modePtr = INPUT_REDIRECTION;
					*argv = '\0';
					Ptr++;
					while(*Ptr == ' ' || *Ptr == '\t')
						Ptr++;
					*supplementPtr = Ptr;
					chop(*supplementPtr);
					terminate = 1;
					break;
				case '|':
					*modePtr = PIPELINE;
					*argv = '\0';
					Ptr++;
					while(*Ptr == ' ' || *Ptr == '\t')
						Ptr++;

					*supplementPtr = Ptr;
					terminate = 1;
					break;
			}
			Ptr++;
		}
		while((*Ptr == ' ' || *Ptr == '\t' || *Ptr == '\n') && terminate == 0)
		{
			*Ptr = '\0';
			Ptr++;
		}
		argv++;
	}
	*argv = '\0';
	return countArgs;
}

void chop(char *Ptr)
{
	while(*Ptr != ' ' && *Ptr != '\t' && *Ptr != '\n')
		Ptr++;
	
	*Ptr = '\0';
}


void execute(char **argv, int mode, char **supplementPtr)
{
	pid_t pid, pid2;
	FILE *fp;
	int mode2 = NORMAL, countArgs, status1, status2;
	char *argv2[INPUT_SIZE], *supplement2 = NULL;
	int Pipe[2];
	if(mode == PIPELINE)
	{
		if(pipe(Pipe))					//create pipe
		{
			fprintf(stderr, "Pipe failed!");
			exit(-1);
		}
		parse(*supplementPtr, argv2, &supplement2, &mode2);
	}
	pid = fork();
	if( pid < 0)
	{
		printf("Error occured");
		exit(-1);
	}
	else if(pid == 0)
	{
		switch(mode)
		{
			case OUTPUT_REDIRECTION:
				fp = fopen(*supplementPtr, "w+");
				dup2(fileno(fp), 1);
				break;
			case OUTPUT_APP:
				fp = fopen(*supplementPtr, "a");
				dup2(fileno(fp), 1);
				break;
			case INPUT_REDIRECTION:
				fp = fopen(*supplementPtr, "r");
				dup2(fileno(fp), 0);
				break;
			case PIPELINE:
				close(Pipe[0]);		//close input of pipe
				dup2(Pipe[1], fileno(stdout));
				close(Pipe[1]);
				break;
		}
		execvp(*argv, argv);
	}
	else
	{
		if(mode == BACKGROUND)
			;
		else if(mode == PIPELINE)
		{
			waitpid(pid, &status1, 0);		//wait for process 1 to finish
			pid2 = fork();
			if(pid2 < 0)
			{
				printf("error in forking");
				exit(-1);
			}
			else if(pid2 == 0)
			{
				close(Pipe[1]);		//close output to pipe
				dup2(Pipe[0], fileno(stdin));
				close(Pipe[0]);
				execvp(*argv2, argv2);
			}
			else
			{
				;
				close(Pipe[0]);
				close(Pipe[1]);
			}
		}
		else
			waitpid(pid, &status1, 0);
	}
}
