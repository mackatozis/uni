#include <stdio.h>
#include <stdlib.h>

void main () {
	char op; char s[10];
	int num=0; float result=.0;
	
	do {
		fgets(s, sizeof(s), stdin);
		sscanf(s,"%c %d", &op, &num);

		switch(op) {
			case '+': result += num; break;
			case '-': result -= num; break;
			case '*': result *= num; break;
			case '/': result /= num; break;
			case '=': break;
			default: printf("Wrong parameters"); break;
		}
	} while (op != '=');

	printf("%.2f", result);
}
