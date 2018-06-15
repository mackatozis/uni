/***************************************************************\
*                                                               *
* Copyright (c) 2013 Manolis Agkopian                           *
* See the file LICENCE for copying permission.                  *
*                                                               *
\***************************************************************/

#ifndef _LINK_H_
#define _LINK_H_

typedef struct node *link;
struct node{
    char *data;
    link next;
};

/*
* Inserts a string to the linked list using insort sorting.
* The first element of the list is returned.
*/
link insert(char *item, link startNode);

/*
* Prints the data of all the nodes.
*/
void printList(link startNode);

/*
* Deletes all the linked list.
*/
void freeList(link startNode);

/*
* Deletes the node that contains element "item" in the list.
* Returns 1 on success, 0 if the node is not found
* and -1 on failure (if the list is empty).
*/
int DeleteItem(char *item, link startNode);

#endif /*_LINK_H_*/
