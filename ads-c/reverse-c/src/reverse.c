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
#include <string.h>

#define STACK_SIZE 1024

char stack[STACK_SIZE];
int sp = 0;

void push(char ch);
char pop();

void push(char ch) {
	printf("Pushed %c at %d\n", ch, sp);
	stack[sp]=ch;
	++sp;
}

char pop() {
	printf("Popped %c at %d\n", stack[sp], sp);
	return stack[--sp];
}

int main() {
	int i;
	char c;

	printf("Give a string: \n");
	while(c!=EOF) {	
		c=getchar();	
		if (c=='\n') break;	
		push(c);
		i++;
	}
	printf("The string have been reversed!\n");
	while(sp!=-1)	putchar(pop());		
	return 0;
}

