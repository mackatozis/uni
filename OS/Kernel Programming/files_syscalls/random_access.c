#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (void) {
	int fd, i, tmp, offset;
	int num;
	off_t sz;
	unsigned char num_bytes[4];

	fd = open("datfile.dat", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	
	sz = lseek(fd, 0, SEEK_END); //get the filesize
	do {
		printf("Give the offset of the integer: ");
		scanf("%d", &offset);
	} while (offset > (sz / 4) - 1 || offset < 0);
	
	if (lseek(fd, offset * sizeof(int), SEEK_SET) == -1) {
		perror("lseek");
		return 2;
	}
	
	read(fd, num_bytes, 4);
	
	num = 0;
		
	//read one 4 byte integer saved as big endian (higher byte lower address)
	tmp = (int) num_bytes[0];
	tmp <<= 24;
	tmp &= 0xFF000000;
	num |= tmp;
	
	tmp = (int) num_bytes[1];
	tmp <<= 16;
	tmp &= 0x00FF0000;
	num |= tmp;
	
	tmp = (int) num_bytes[2];
	tmp <<= 8;
	tmp &= 0x0000FF00;
	num |= tmp;
	
	tmp = (int) num_bytes[3];
	tmp &= 0x000000FF;
	num |= tmp;
	
	printf("num: %d\n", num);

	return 0;
}
