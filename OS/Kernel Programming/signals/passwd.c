#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define BUF_SZ 256
#define TRY_LIM 3
#define PASSWD "password" //super secret password

void alarm_handler (int signal);

int main (void) {
	char buf[BUF_SZ];
	int buf_len, tries = 0;

	signal(SIGALRM, alarm_handler); //install the alarm hander
	alarm(10); //set the alarm to 10 seconds
	
	for (;;) {
		printf("Give your password: ");
		fgets(buf, BUF_SZ, stdin);
		buf_len = strlen(buf);
		buf[buf_len-1] = '\0'; //remove the '\n' from the end of the string
		
		if (strcmp(buf, PASSWD) == 0) {
			alarm(0); //cancel the alarm
			printf("Welcome Back!\n");
			break;
		}
		else {
			fprintf(stderr, "WRONG! You have %d tries left...\n", TRY_LIM - ++tries);
			if (tries == TRY_LIM) {
				exit(EXIT_FAILURE);
			}
		}
	}

	return EXIT_SUCCESS;
}

void alarm_handler (int signal) {
	fprintf(stderr, "\nTo late! :(\n");
	exit(EXIT_FAILURE);
}
