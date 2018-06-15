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
#include "vector.h"


IntVectorPtr VecNew(int initialCapacity) {

	IntVectorPtr vec = (IntVectorPtr)malloc(sizeof(IntVector));	

	if (vec == NULL)
		return NULL;

	vec->data = (int *)malloc(initialCapacity*sizeof(int));
	if (vec->data == NULL)
	{
		free(vec);	
		return NULL;
	}
	vec->size = 0;
	vec->capacity = initialCapacity;
}	/*  end VecNew */


void VecDelete(IntVectorPtr vector) {

	if (vector != NULL) {
		if (vector->data != NULL)
			free(vector->data);
	free(vector);
	}
}	/*  end VecDelete */


int VecAdd(IntVectorPtr vector, int element) {

	IntVectorPtr vec=vector;
	if(vec->size==vec->capacity) {
		int *newData = (int *)realloc(vec->data,vec->capacity*2*sizeof(int));
		if(newData == NULL)
			return -1;
		vec->data=newData;
		vec->capacity *= 2;
	}
	vec->data[vec->size]=element;
	return vec->size++;
}	/*  end VecAdd */


int VecErase(IntVectorPtr vector, int position) {
	if ( vector == NULL || vector->data==NULL || vector->size == 0)
		return -1;
	if (position < 0 || vector->size <= position) 
		return -1;
	if (position == vector->size-1)
		vector->size--;
	else
		vector->data[position] = vector->data[--vector->size];
	return position;
}	/*  end VecErase */


int VecGet(IntVectorPtr vector, int position) {

	if (vector == NULL || vector->data == NULL)
		return 0;
	if (position < 0 || position >= vector->size)
		return 0;
	return vector->data[position];
}	/*  end VecGet */

int VecMin(IntVectorPtr vector, int size) {

        int i,min=VecGet(vector,0);
        for(i=0;i<size;i++) {
                if(VecGet(vector,i)<min)
                        min=VecGet(vector,i);
        }	
        return min;
}	/*  end VecMin */

int VecMax(IntVectorPtr vector, int size) {

        int i,max=VecGet(vector,0);
        for(i=0;i<size;i++) {
                if(VecGet(vector,i)>max)
                        max=VecGet(vector,i);
        }	
        return max;
}	/*  end VecMax */	
	
double VecAverage(IntVectorPtr vector, int size) {

        int i, sum=0;
        for(i=0;i<size;i++)
                sum+=VecGet(vector,i);
        return (double)sum/(double)size;
}


int compare(const void *arg1,const void *arg2) {
	return *((int*)arg1)-*((int*)arg2);
}	/*  end compare */


void VecQuickSort(IntVectorPtr vector) {
	qsort(vector->data, vector->size, sizeof(int),compare);
}	/*  end VecQuickSort */


int VecBinarySearch(IntVectorPtr vector, int element) {

	int *found;
	if ((vector == NULL) || (vector->data == NULL))
		return -1;

	found = (int *)bsearch(&element, vector->data, vector->size, sizeof(int), compare);
   	return found-vector->data;
}	/*  end VecBinarySearch */


void VecQuickSort2(IntVectorPtr vector, int start, int end)
{	
	int l=start, r=end, tmp, piv=vector->data[(start+end)/2];

	while(l<=r) {

		while(vector->data[l] < piv)	l++;
		while(vector->data[r] > piv)	r--;
		
		if(l<=r) {
			tmp = vector->data[l];
			vector->data[l]=vector->data[r];
			vector->data[r]=tmp;
			l++;
			r--;
		}
	}
	if(start < r)
		VecQuickSort2(vector,start,r);
	if(l < end)
		VecQuickSort2(vector,l,end);
}	/*  end VecQuickSort */


int VecBinarySearch2(IntVectorPtr vector, int element, int start, int end) 
{
	int mid;
	do {
		mid = (start+end)/2; 

		if(vector->data[mid] < element) 
			start = mid + 1;
		else if(vector->data[mid] > element) 
			end = mid - 1;
		else if(vector->data[mid] == element) 
			return mid;
		
	} while(start <= end);
}	/*  end VecBinarySearch2 */


int VecBinarySearch3(IntVectorPtr vector, int element, int start, int end) {

	int mid;
	if(end<start)
		return -1;

	mid = (end+start)/2;

	if(element < vector->data[mid])
		return VecBinarySearch2(vector, element, start, mid-1);
	else if(element > vector->data[mid])
		return VecBinarySearch2(vector, element, mid+1, end);
	else
		return mid; 
}	/*  end VecBinarySearch3 */
