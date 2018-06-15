/***************************************************************\
*                                                               *
* Copyright (c) 2013 Manolis Agkopian                           *
* See the file LICENCE for copying permission.                  *
*                                                               *
\***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insort.h"


int main(void){
	char *p;
	char s[1024]; //string buffer
	link nodeList = NULL;

	puts("");
	for(;;){
		printf("Give a string or nothing to stop...\n");
		fgets(s, 1024, stdin);

		p = strchr(s,'\n');
		*p = '\0';

		if (s[0]=='\0') break; //loop until user press enter
		nodeList = insert(s, nodeList);
	}

	printf("--List Elements--\n");
	printList(nodeList);
	
	printf("\nGive the item you want to delete from the list: ");
	scanf("%s",s);
	if (DeleteItem(s, nodeList))
		printf("Element has been deleted.\n\n");
	else
		fprintf(stderr, "Element does not exist.\n\n");

	printf("--List Elements--\n");
	printList(nodeList);

	freeList(nodeList);
	putchar('\n');
	return(0);
}







