#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SZ 256

int main (void) {
	char buf[BUF_SZ];
	int fd, buf_len, n;
	pid_t pid;

	/*The server will create 2 named pipes for full duplex communication*/
	unlink("/tmp/test_fifo1");
	unlink("/tmp/test_fifo2");
	
	if (mkfifo("/tmp/test_fifo1", 0664) == -1) {
		perror("mkfifo");
		return 1;
	}
	else if (mkfifo("/tmp/test_fifo2", 0664) == -1) {
		perror("mkfifo");
		return 1;
	}
	
	/*Because when a process waits for input gets blocked we need a second to do the write part if the other is blocked*/
	if ((pid = fork()) == -1) {
		perror("fork");
		return 1;
	}
	else if (pid == 0) { //the child will read to the one pipe
	
		if ((fd = open("/tmp/test_fifo1", O_RDONLY)) == -1) {
			perror("open");
			return 1;
		}
		
		for (;;) {
			n = read(fd, buf, BUF_SZ);
			buf[n] = '\0';
			
			puts(buf);
		}
		
	}
	else { //the parent will write to the other

		if ((fd = open("/tmp/test_fifo2", O_WRONLY)) == -1) {
			perror("open");
			return 1;
		}
		
		for (;;) {
			fgets(buf, BUF_SZ, stdin);
			buf_len = strlen(buf);
			buf[buf_len-1] = '\0'; //remove '\n'
		
			write(fd, buf, BUF_SZ);
		}
	}

	return 0;
}
