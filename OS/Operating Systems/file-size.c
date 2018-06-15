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

/* gcc file-size.c -o fsize */
/* ./fsize filename */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	unsigned long int size; FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Usage:%s file\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Οpen error:\"%s\".\n", argv[1]);
		exit(2);
	}

	fseek(fp, 0, SEEK_END);	// seek to end of file
	size = ftell(fp);	// get current file pointer

	if (size <= 1024)
		printf("%lu Bytes", size);
	else if (size <= 1024*1024)
		printf("%.1lf KB", (double)size/(1024.0));
	else if (size <= 1024*1024*1024)
		printf("%.1lf MB", (double)size/(1024.0*1024.0));
	else
		printf("%.1lf GB", (double)size/(1024.0*1024.0*1024.0));

	fclose(fp);
	return 0;
}
