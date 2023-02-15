#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	// counter variable
	int i = 0;

	// create node that is set equal to beginning of linked list
	node *current = head;

	// loops until end of linked list
	while (current != NULL)
	{
		// counts every node
		i++;

		// goes to next node until end
		current = current->next;
	}

	return i;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	// variable for number of nodes in linked list
	int len = length(head);

	// creates memory for the character array
	char *c = malloc((len + 1) * sizeof(char));

	// counter variable
	int i = 0;

	// loops until end of linked list
	while (head != NULL)
	{
		// adds letter in each node to character array
		c[i] = head->letter;

		// goes to next node until end
		head = head->next;
		i++;
	}

	// sets end of list to NULL terminator
	c[len] = '\0';

	return c;
}

// inserts character to the linkedlist
// if the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	// create new node to contain character
	node *newNode = (node*) malloc(sizeof(node));
	newNode->letter = c;
	newNode->next = NULL;
	
	// if head is empty, replace it with new node
	if (*pHead == NULL)
		*pHead = newNode;
	else
	{
		// create a node that contains previous
		node *lastNode = (node*) malloc(sizeof(node));
		lastNode = *pHead;

		// keeps track if there are 2+ nodes
		while (lastNode->next != NULL)
		{
			// goes to next node until end
			lastNode = lastNode->next;
		}
		// sets old tail equal to new tail
		lastNode->next = newNode;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	// create node to contain contents of what's being passed
	struct node *current = *pHead;

	// temporary variable to contents after the node being freed
	struct node *next;

	// loops until end of linked list
	while (current->next != NULL)
	{
		// sets next node equal to node after the one being freed
		next = current->next;

		// deallocates current node
		free(current);

		/* sets current node equal to next node 
		which was what current was pointing to*/
		current = next;
	}
	
	// sets linked list to NULL
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);

	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}