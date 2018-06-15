#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void fire_alarm_clock (int signal);

int main (int argc, char **argv) {
	pid_t pid;
	
	
	if (argc != 2 || atoi(argv[1]) < 1) {
		printf("Usage: %s <seconds>\n", argv[0]);
		return 1;
	}
	
	
	if ((pid = fork()) == -1) {
		perror("fork");
		return 1;
	}
	else if (pid == 0) { //inside the child
		signal(SIGALRM, fire_alarm_clock);
		alarm(atoi(argv[1]));
		pause(); //wait for the alarm to fire
		return 0;
	}
	else { //inside the parent
		printf("The alarm will fire in %d seconds.\n", atoi(argv[1]));
		wait(NULL); //wait for child process to finish
		return 0;
	}
}

void fire_alarm_clock (int signal) {
	system("aplay rooster.wav");
}
