#include <stdio.h>
#include <stdlib.h>

void main () {

	char op, s[10];
	int num=0, result=0;
	
	do {
		fgets(s, sizeof(s), stdin);
		sscanf(s,"%c %d", &op, &num);

		switch(op) {
			case '+': if (num == 0) {
					break;
				}
				else if (num == 1) {
					result++;
				}
				else {
					result += num; 
				}
				break;
			case '-': if (num == 0) {
					break;
				}
				else if (num == 1) {
					result--;
				}
				else {
					result -= num; 
				}
				break;
			case '*': if (num == 0) {
					result = 0;
				}
				else if (num == 1) {
					break;
				}
				else if (num == 2) {
					result <<= num;
				}
				else {
					result *= num; 
				}
				break;
			case '/': if (num == 0) {
					printf("Can't divide with zero"); 
					break;
				}
				else if (num == 1) {
					break;
				}
				else if (num == 2) {
					result >>= num;
				}
				else {
					result /= num; 
				}
				break;
			case '=': break;
			default: printf("Wrong parameters"); break;
		}
	} while (op != '=');

	printf("Result: %d", result);
}
