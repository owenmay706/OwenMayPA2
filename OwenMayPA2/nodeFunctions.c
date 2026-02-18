#include "header.h"

Node* createNode(Record newRecord) {
	Node* newNode = malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->data = newRecord;
		newNode->next = NULL;
		newNode->prev = NULL;
	}

	return newNode;
}

int insertFront(Node** pList, Record newRecord) {

	Node* newNode = createNode(newRecord);
	int success = 0;

	if (newNode != NULL) {
		success = 1;

		if (*pList == NULL) {
			//empty list 
			*pList = newNode;
		}
		else
		{
			newNode->next = *pList;
			(*pList)->prev = newNode;
			*pList = newNode;
		}
	}
	return success;
}

void destroyList(Node** pList)
{
	Node* current = *pList;
	Node* temp = NULL;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}

	*pList = NULL;
}

Node* FindSongTitle(Node* pList) {
	char title[100];

	printf("Enter song title: ");
	fgets(title, sizeof(title), stdin);
	title[strcspn(title, "\n")] = '\0';

	Node* current = pList;

	while (current != NULL) {
		if (strcmp(current->data.title, title) == 0) {
			return current; // found
		}
		current = current->next;
	}

	return NULL; // not found
}