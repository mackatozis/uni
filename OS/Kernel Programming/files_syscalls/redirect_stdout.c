#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SZ 256

int main (void) {
	int fd, i;
	char buf[BUF_SZ];
	
	if ((fd = open("stdout_redirect", O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1) {
		perror("open");
		return 1;
	}

	if (dup2(fd, STDOUT_FILENO) == -1) { //overwrite STDOUT_FILENO with fd
		perror("dup2");
		return 2;
	}
	close(fd); //now fd == STDOUT_FILENO, so fd is not needed any more

	for (i = 0; i < 10; ++i) {
		fgets(buf, BUF_SZ, stdin);
		fputs(buf, stdout);  //if fact it writes to the file stdout_redirect
	}

	close(fd);

	return 0;
}
