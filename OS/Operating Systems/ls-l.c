/*
 * The MIT License
 *
 * Copyright 2013 Alexandros Efthymiadis.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* gcc ls-l.c -o lsl */
/* ./lsl PATH_TO_DIR */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {	

	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	char buf[strlen(argv[1]) + NAME_MAX + 2];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((mydir = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "Can't open '%s'\n", argv[1]);
		exit(1);
	}

	while((myfile = readdir(mydir)) != NULL) {
		sprintf(buf, "%s/%s", argv[1], myfile->d_name);
		stat(buf, &mystat);  
		printf("%d",(int)mystat.st_size);
		printf(" %s\n", myfile->d_name);
	}
	closedir(mydir);
}
