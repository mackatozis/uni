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

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	int nodes, connections, counter=0;
	int flag=1, flag2=1;
	int temp=1, temp2=0;
	int array[100], array2[100];
	int i, j;
	int last=nodes, start=1, min=100;

	scanf("%d %d", &nodes, &connections);
	
	for (i=0; i<100; i++) {
		array[i]=0;
		array2[i]=0;
	}


	for (i=0; i<3*connections; i+=3) {
		scanf("%d ",&array[i]);
		scanf("%d ",&array[i+1]);
		scanf("%d",&array[i+2]);
	}
    
	for (i=0; i<3*connections; i++) {

		if (array[i] == temp) {

				for (j=0; j<nodes; j++) {
					if (array2[j] == array[i+1]) 
						flag2=0;
				}
				if (flag2) {
					min=array[i+2];
					temp2=array[i+1];
				}

				i=i+3;
				while (array[i] == temp) {
					if (array2[j] == array[i+1])
						flag2=0;


					if (flag2) {
						if (min > array[i+2]) {
							min=array[i+2];
							temp2=array[i+1];
						}
					}

					i=i+3;
				}
				i--;
				temp=temp2;
				counter=counter+min;
		} else 
			i=i+2;

		if (temp == last)
			i=3*connections;
	}

	flag2=1;

	for (i=3*connections-1; i>=0; i--) {

		if (array[i-1] == temp) {

			for (j=0; j<nodes; j++) {
				if (array2[j] == array[i-2]) 
					flag2=0;
			}
			if (flag2) {
				min=array[i];
				temp2=array[i-2];
			}

			i=i-3;

			while (array[i-1] == temp) {
				if (array2[j] == array[i-2]) 
					flag2=0;

				if (flag2) {
					if (min > array[i]) {
						min=array[i];
						temp2=array[i-2];
				    }
				}

				i=i-3;
			}

			i++;
			temp=temp2;
			counter=counter+min;
		} else
			i=i-2;		
	}
		
	printf("\n%d\n", counter);
	return 0;
}
