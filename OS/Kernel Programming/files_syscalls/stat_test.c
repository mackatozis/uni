#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define _BSD_SOURCE

int main (void) {
	struct stat file_status;
    char buffer[25];
    struct tm* tm_info;

	if (stat("datfile.dat", &file_status) != 0) {
		perror("stat");
		return 1;
	}

	printf("st_dev: %d %d\n", major(file_status.st_dev), minor(file_status.st_dev));
	printf("st_ino: %d\n", file_status.st_ino);
	printf("st_mode: %o\n", file_status.st_mode);
	printf("st_nlink: %d\n", file_status.st_nlink);
	printf("st_uid: %d\n", file_status.st_uid);
	printf("st_gid: %d\n", file_status.st_gid);
	printf("st_rdev: %d\n", file_status.st_rdev);
	printf("st_size: %d\n", file_status.st_size);
	printf("st_blksize: %d\n", file_status.st_blksize);
	printf("st_blocks: %d\n", file_status.st_blocks);
	
	tm_info = localtime(&(file_status.st_atime));
	strftime(buffer, 25, "%d-%m-%Y %H:%M:%S", tm_info);
	printf("st_atime: %s\n", buffer);
	
	tm_info = localtime(&(file_status.st_mtime));
	strftime(buffer, 25, "%d-%m-%Y %H:%M:%S", tm_info);
	printf("st_mtime: %s\n", buffer);
	
	tm_info = localtime(&(file_status.st_ctime));
	strftime(buffer, 25, "%d-%m-%Y %H:%M:%S", tm_info);
	printf("st_ctime: %s\n", buffer);

	return 0;
}
