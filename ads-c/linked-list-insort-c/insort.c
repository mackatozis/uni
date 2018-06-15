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


link insert(char *item, link startNode){
	link cn; //current node
	link t;

	char *element = strdup(item); //allocate memory for the new element

	//pseudonode (list head)
	link head = (struct node *)malloc(sizeof(struct node));
	head->next = startNode;
	head->data = NULL;

	//find a node that its next has content
	//bigger than from the element we want to insert
	//if none is found put it at the end of the list
	for (cn = head; cn->next!=NULL; cn = cn->next)
		if (strcmp(cn->next->data, element) > 0) break;
	
	//add the new node before the first bigger from it
	t = cn->next;
	cn->next = (struct node *)malloc(sizeof(struct node)); //the node that was pointing the bigger points now the new
	cn->next->data = element; //insert the data to the new node
	cn->next->next = t; //the new node now points to its bigger

	t = head->next;
	free(head); //free the allocated memory for the list head
	return t; //return the first (real) node of the list
}


void printList(link startNode){
	link cn; //current node
	
	for (cn = startNode; cn!=NULL; cn = cn->next){
		printf("%s\n",cn->data);
	}
}

void freeList(link startNode){
	link t;
	//delete all the nodes except the first
	if (startNode == NULL) return;
	
	while(startNode->next!=NULL){ //until nothing there is nothing after the first node
		
		t = startNode->next; //put temporary here the second node
		startNode->next = startNode->next->next; //link the first node with the third
	
		//now that the node is not linked to the list we free it
		free(t->data);
		free(t);
	}
	//remove the first node after the rest list have been free
	free(startNode->data);
	free(startNode);
}

int DeleteItem(char *item, link startNode){
	link cn; //current node
	link t;	
	if (startNode == NULL) return -1; //if the list is empty

	//pseudonode (list head)
	link head = (struct node *)malloc(sizeof(struct node));
	head->next = startNode;
	head->data = NULL;

	/*find the node who its next have to be deleted*/
	for (cn = head; cn->next!=NULL; cn = cn->next)
		if (strcmp(cn->next->data, item) == 0) break;
	if (cn->next==NULL) return 0; //an den uparxei telika o komvos

	t = cn->next; //put the node that hase to be deleted temporary here
	cn->next = cn->next->next; //link the current node with the next of the next node

	//now that the node is not linked to the list we free it
	free(t->data);
	free(t);

	free(head); //and finally we free the head

	return 1;
}






