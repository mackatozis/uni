/*
 * The MIT License
 *
 * Copyright 2012 Alexandros Efthymiadis.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define uknown 4
#define maxF 93

int size = 0;
unsigned long long int *knownF = 0;

void resizeF(int nsize) {

	unsigned long long int *tempF, *delF = knownF;

	int i;

	tempF = (unsigned long long int*) malloc(nsize * sizeof(unsigned long long int));

	if(knownF)
		memcpy(tempF, knownF, size * sizeof(unsigned long long int));

	for (i = size; i < nsize; i++)
		tempF[i] = uknown;

	if(nsize > 0) {
		tempF[0] = 0;
		if(nsize > 1)
			tempF[1] = 1;
	}
	knownF = tempF;
	size = nsize;

	if(delF)
		free(delF);
}

unsigned long long int rF(int n) {

	if(n > maxF || n < 0)
		return 0;

	if(n >= size)
		resizeF(n + 1);

	if(knownF[n] != uknown)
		return knownF[n];

	return (knownF[n] = rF(n - 1) + rF(n - 2));
}

unsigned long long int iF(int n) {
	
	int i = 2;

	if(n > maxF || n < 0)
		return 0;

	if(n >= size) 
		resizeF(n + 1);

	while(knownF[n] == uknown) {
		if(knownF[i] == uknown) 
			knownF[i] = knownF[i - 1] + knownF[i - 2];
		i++;
	}
	return knownF[n];
}

int main(int argc, char **argv) {

	if(argc < 2) {
		printf("Usage: %s int\n", argv[0]);
		return 1;
	}
	int n = atoi(argv[1]);

	printf("%llu\n", iF(n));

	if(knownF)
		free(knownF);

	return 0;
} 
