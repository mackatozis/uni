#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main (int argc, char **argv) {
	DIR *dp;
	struct dirent *drp;
	
	if (argc != 2) {
		printf("Usage: %s </path/to/directory>", argv[0]);
		return 1;
	}
	else if ((dp = opendir(argv[1])) == NULL) {
		perror(argv[0]);
	}

	while ((drp = readdir(dp)) != NULL) {
		printf("filename: %s\t inode: %d\n", drp->d_name, drp->d_ino);
	}
	
	closedir(dp);
	
	return 0;
}
