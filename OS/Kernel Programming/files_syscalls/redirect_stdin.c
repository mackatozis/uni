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
	
	if ((fd = open("stdin_redirect", O_RDONLY)) == -1) {
		perror("open");
		return 1;
	}

	if (dup2(fd, STDIN_FILENO) == -1) { //overwrite STDIN_FILENO with fd
		perror("dup2");
		return 2;
	}
	close(fd); //now fd == STDIN_FILENO, so fd is not needed any more

	for (i = 0; i < 10; ++i) {
		fgets(buf, BUF_SZ, stdin); //if fact it reads from the file stdin_redirect
		fputs(buf, stdout);
	}

	close(fd);

	return 0;
}
