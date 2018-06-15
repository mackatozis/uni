#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define NUMS_SZ 10
#define BUF_SZ 40


int main (void) {
	int fd, i, k;
	int nums[NUMS_SZ] = {5, 10, 546, 89, 45645, 899, 47, 456456, 69, 1231212};
	unsigned char buf[BUF_SZ];
	unsigned char next_byte;

	fd = open("datfile.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644); //create the file and open for read, or if exists overwrite
	if (fd == -1) {
		perror("open");
		return 1;
	}
	
	for (i = 0, k = 0; i < NUMS_SZ; ++i) {
		
		//write one 4 byte integer as big endian to the file (higher byte lower address)
		next_byte = nums[i] >> 24;
		next_byte &= 0x000000FF;
		buf[k++] = next_byte;
		
		next_byte = nums[i] >> 16;
		next_byte &= 0x000000FF;
		buf[k++] = next_byte;
		
		next_byte = nums[i] >> 8;
		next_byte &= 0x000000FF;
		buf[k++] = next_byte;
		
		next_byte = nums[i];
		next_byte &= 0x000000FF;
		buf[k++] = next_byte;
	}
	

	if (write(fd, buf, BUF_SZ) != BUF_SZ) {
		perror("write");
		close(fd);
		return 2;
	}

	close(fd);

	return 0;
}
