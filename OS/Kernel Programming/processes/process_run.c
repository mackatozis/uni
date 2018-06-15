#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void get_exec_name (char *path, char *exec_name);

int main (int argc, char **argv) {
	pid_t pid;
	int i;
	char exec_name[256];
	char *exec_args[30];

	if (argc < 2) {
		printf("Usage: %s /path/to/executable [<arg1> <arg2> ...]\n", argv[0]);
		return 1;
	}
	
	get_exec_name(argv[1], exec_name);

	exec_args[0] = malloc(strlen(exec_name) * sizeof(char));

	strcpy(exec_args[0], exec_name);
	for (i = 2; i < argc; ++i) {
		exec_args[i-1] = malloc(strlen(argv[i]) * sizeof(char));
		strcpy(exec_args[i-1], argv[i]);
	}
	exec_args[i-1] = NULL;
	
	
	printf("Executing %s ...\n", exec_name);
	execv(argv[1], exec_args);
	
	perror(argv[0]); //execv returns only on error
	return 2;
}

void get_exec_name (char *path, char *exec_name) {
	int i, path_len = 0, last_slash = -1;
	
	path_len = strlen(path);
	for (i = 0; i < path_len; ++i) {
		if (path[i] == '/') {
			last_slash = i;
		}
	}
	
	if (last_slash == -1) {
		strcpy(exec_name, path);
	}
	else {
		strcpy(exec_name, &path[last_slash + 1]);
	}
}
