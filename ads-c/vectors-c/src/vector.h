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

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED


typedef struct {

	int size;
	int capacity;
	int *data;
} IntVector, *IntVectorPtr;

IntVectorPtr VecNew(int  initialCapacity);
void VecDelete(IntVectorPtr vector);
int VecAdd(IntVectorPtr vector, int element);
int VecErase(IntVectorPtr vector, int position);
int VecGet(IntVectorPtr vector, int position);
int VecMin(IntVectorPtr vector, int size);
int VecMax(IntVectorPtr vector, int size);
double VecAverage(IntVectorPtr vector, int size);
int compare(const void *arg1, const void *arg2);
void VecQuickSort(IntVectorPtr vector);
void VecQuickSort2(IntVectorPtr vector, int start, int end);
int VecBinarySearch(IntVectorPtr vector, int element);
int VecBinarySearch2(IntVectorPtr vector, int element, int start, int end);
int VecBinarySearch3(IntVectorPtr vector, int element, int start, int end);

#endif	/* end VECTOR_H_INCLUDED */
