#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUMS_SZ 64
#define BUF_SZ 256

int main (void) {
	int fd, i, k, j, file_sz, tmp;
	int nums[NUMS_SZ];
	unsigned char buf[BUF_SZ];
	unsigned char next_byte;

	fd = open("test.dat", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	
	file_sz = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	for (i = 0; i < file_sz / 4; ++i) {
		read(fd, &nums[i], sizeof(int));
	}
	
	for (j = 0; j < i; ++j) {
		printf("%d ", nums[j]);
	}
	putchar('\n');

	close(fd);

	return 0;
}
