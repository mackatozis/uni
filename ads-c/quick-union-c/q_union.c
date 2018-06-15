/***************************************************************\
*                                                               *
* Copyright (c) 2013 Manolis Agkopian                           *
* See the file LICENCE for copying permission.                  *
*                                                               *
\***************************************************************/

/*****************************************************************************************************\
* At the quick union algorithm, in order to check if two nodes are linked, we check if they are      *
* in the the same tree (if they are under the same root). If they are not linked, we put the one     *
* under the root of the other. At the algorithm with weights, when we have to link two nodes, we     *
* check who belongs to the smallest tree and we link it to the bigger tree. By this way we create    *
* a standalone tree with many branches. When we have a tree with many branches, it takes very little *
* time to reach the root, because we cross a smaller route, so we optimize the speed of the find     *
* function and the whole algorithm becomes much faster.                                              *
\*****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10 //number of nodes

int check_node(char *r);

int main (void) {
	int id[N], treeSize[N], i, j, p, q, n;
	char r[10];

	for (i = 0; i < N; ++i) {
		id[i] = i; //init the node IDs

		treeSize[i]=1; //at the beginning every node is a standalone tree because no one node is linked to no one (size == 1)
	}

	for (;;) {
		
		/*INPUT*/
		printf("Give the 1st node or -1 to terminate: ");
		fgets(r, 10, stdin);
		n = strlen(r);
		r[n-1] = '\0'; //remove the '\n' at the end
		
		p = check_node(r); //check if it's num and 0 to N-1
		if (p == -1) break;

		printf("Give the 2nd node or -1 to terminate: ");
		fgets(r, 10, stdin);
		n = strlen(r);
		r[n-1] = '\0'; //remove the '\n' at the end
		
		q = check_node(r); //check if it's num and 0 to N-1
		if (q == -1) break;

		/*FIND*/ 
		//if we find an item that points itself this is the root of the tree
		for (i = p; i != id[i]; i = id[i]); //find the root of tree p
		for (j = q; j != id[j]; j = id[j]); //find the root of tree q
		if (i==j) { //check if the two trees have common node
			 puts("Nodes already linked.\n");
			 continue;
		}

		/*UNION*/
		if (treeSize[i] < treeSize[j]) { //if j == root of q
			id[i] = j; //put node p under the same root as q
			treeSize[j] += treeSize[i];
		}
		else{ //if i == root of  p
			id[j]=i; //put node q under the same root as p
			treeSize[i] += treeSize[j];
		}
		puts("Nodes linked!\n");

	}

	return 0;
}


int check_node (char *r) {
	int i, node, n;
	
	do {  
		for (i = 0; r[i] != '\0'; ++i) { //check if it's positive integer
			if (r[i] < '0' || r[i] > '9') {
			puts(r);
			   if (r[0] == '-' && r[1] == '1' && r[2] == '\0') //only the negative number -1 is accepted because its purpose it to terminate the process
				   break;
			   fprintf(stderr, "\nError! The nodes can be only positive integers!\n");
			   printf("Give the node again or -1 to terminate: ");
			   fgets(r, 10, stdin);
			   n = strlen(r);
			   r[n-1] = '\0'; //remove the '\n' at the end
		
			   i = -1;
			}
		}
		
		node = atoi(r);
		if (node > N-1) { //check if node < N
			printf("Error! the node must be 0 - %d! Try again: ", N-1);
			fgets(r, 10, stdin);
			n = strlen(r);
			r[n-1] = '\0'; //remove the '\n' at the end
		}
	} while(node > N-1);
	
	return node;
}













