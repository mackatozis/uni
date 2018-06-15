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

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define N 12
#define initialCapacity 6


int main(int argc, char* argv[]) {

	IntVectorPtr vec = VecNew(initialCapacity);
	int element, position, found, i;
	srand(time(NULL)); 
	
	//Fill Vector
	for(i=0; i<N; i++)
		VecAdd(vec,rand()%100);
	
	//Print unsorted Vector
	for(i=0; i<N; i++)
	 	printf("%d ",vec->data[i]);

	printf("\nMax element: %d\n", VecMax(vec,vec->size));
	printf("Min element: %d\n", VecMin(vec,vec->size));
	printf("Average of elements: %.1lf\n",VecAverage(vec,vec->size));

	// To use vecErase function uncomment this section
	/*
	printf("Choose element's position: (this element will be deleted)\n");
	scanf("%d",&position);
	VecErase(vec,position);
	*/
	
	if(argv[1] == NULL || strcmp("-r",argv[1])==0) {
	
		VecQuickSort2(vec, 0, vec->size-1);

		//Print sorted Vector
		for(i=0;i<N;i++)
		 	printf("%d ",vec->data[i]);

		printf("\nPlease give an element for search:\n");
		scanf("%d", &element);

		if(argv[1] == NULL)
			found = VecBinarySearch2(vec,element,0,vec->size);					
		else if (strcmp("-r",argv[1])==0)
			found = VecBinarySearch3(vec,element,0,vec->size);
		
		if(found >= 0)	
			printf("The element found in %d posititon.\n", found);
		else	
			printf("The element not found.\n");

	}
	else if(strcmp("-l",argv[1])==0) {

		VecQuickSort(vec);

		//Print sorted Vector
		for(i=0; i<N; i++)
		 	printf("%d ",vec->data[i]);

		printf("\nPlease give an element for search:\n");
		scanf("%d", &element);
		found = VecBinarySearch(vec,element);
		if(found >= 0)
			printf("The element found in %d posititon.\n", found);
		else
			printf("The element not found.\n");
	}
	else
		printf("Your argument is invalid.\n");

	VecDelete(vec);
	return 0;
}
