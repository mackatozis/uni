#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUMS_SZ 64
#define BUF_SZ 256

void main (void) {
	int fd, i, k, j, file_sz, tmp;
	int nums[NUMS_SZ];
	unsigned char buf[BUF_SZ];
	unsigned char next_byte;

	fd = open("datfile.dat", O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit (1);
	}
	
	if ((file_sz = read(fd, buf, BUF_SZ)) == -1) {
		perror("read");
		close(fd);
		exit (2);
	}
	
	for (i = 0, k = 0; k < file_sz; ++i) {
		nums[i] = 0;
		
		//read one 4 byte integer saved as big endian (higher byte lower address)
		tmp = (int) buf[k++];
		tmp <<= 24;
		tmp &= 0xFF000000;
		nums[i] |= tmp;
		
		tmp = (int) buf[k++];
		tmp <<= 16;
		tmp &= 0x00FF0000;
		nums[i] |= tmp;
		
		tmp = (int) buf[k++];
		tmp <<= 8;
		tmp &= 0x0000FF00;
		nums[i] |= tmp;
		
		tmp = (int) buf[k++];
		tmp &= 0x000000FF;
		nums[i] |= tmp;
	}
	
	for (j = 0; j < i; ++j) {
		printf("%d ", nums[j]);
	}

	close(fd);

	exit (0);
}
