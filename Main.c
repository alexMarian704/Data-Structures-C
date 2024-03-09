#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node {
	char* name;
	Node* nextNode;
};

struct LinkedList {
	Node* head;
	int size;
};

void printLinkedList(LinkedList* list) {
	Node* temp = list->head;
	while (temp != NULL) {
		printf("%s -> ", temp->name);
		temp = temp->nextNode;
	}
	printf("NULL\n");
}

Node* createNewNode(const char* name) {
	if (strlen(name) == 0) return NULL;

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Failed to allocate memory for node\n");
		return NULL;
	}

	newNode->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
	if (newNode->name == NULL) {
		free(newNode);
		printf("Failed to allocate memory for name\n");
		return NULL;
	}
	strcpy(newNode->name, name);
	newNode->nextNode = NULL;

	return newNode;
}

void push(LinkedList* list, const char* name) {
	if (strlen(name) == 0) return;

	Node* newNode = createNewNode(name);
	if (newNode == NULL) return;

	if (list->head == NULL) {
		list->head = newNode;
	}
	else {
		Node* temp = list->head;
		while (temp->nextNode != NULL) {
			temp = temp->nextNode;
		}
		temp->nextNode = newNode;
	}
	list->size++;
}

void freeLinkedList(LinkedList* list) {
	Node* temp = list->head;
	while (temp != NULL) {
		Node* next = temp->nextNode;
		free(temp->name);
		free(temp);
		temp = next;
	}
	list->head = NULL;
	list->size = 0;
}

void pushFront(LinkedList* list, const char* name) {
	if (strlen(name) == 0) return;
	Node* newHead = createNewNode(name);
	if (newHead == NULL) return;

	newHead->nextNode = list->head;
	list->head = newHead;
	list->size++;
}

void insertAt(LinkedList* list, const char* name, int poz) {
	if (strlen(name) == 0) return;
	Node* newNode = createNewNode(name);

	if (newNode == NULL) return;
	if (poz < 0 || poz > list->size) return;

	if (poz == 0) {
		pushFront(list, newNode);
		return;
	}
	if (poz == list->size) {
		push(list, newNode);
		return;
	}

	Node* temp = list->head;
	Node* previous = NULL;
	for (int actualPoz = 0; actualPoz < poz; actualPoz++) {
		previous = temp;
		temp = temp->nextNode;
	}
	newNode->nextNode = temp;
	if(previous != NULL)
		previous->nextNode = newNode;
	list->size++;
}

void deleteAt(LinkedList* list, int poz) {
	if (poz < 0 || poz >= list->size) return;
	if (list->head == NULL) return;

	Node* temp = list->head;
	Node* previous = NULL;
	for (int index = 0; index < poz; index++) {
		previous = temp;
		temp = temp->nextNode;
	}
	if (previous != NULL) {
		previous->nextNode = temp->nextNode;
		free(temp->name);
		free(temp);
	}
	else {
		Node* oldHead = list->head;
		list->head = list->head->nextNode;
		free(oldHead->name);
		free(oldHead);
	}
	list->size--;
}

bool isEmpty(LinkedList* list) {
	return list->head == NULL;
}

void deleteNodeByValue(LinkedList* list, const char* name) {
	if (list->head == NULL || strlen(name) == 0) return;

	Node* temp = list->head;
	Node* prev = NULL;

	while (temp != NULL && strcmp(temp->name, name) != 0) {
		prev = temp;
		temp = temp->nextNode;
	}
	if (temp != NULL && strcmp(temp->name, name) == 0) {
		if (prev != NULL) {
			prev->nextNode = temp->nextNode;
		}
		else {
			list->head = temp->nextNode;
		}
		free(temp->name);
		free(temp);
		list->size--;
	}
	else {
		printf("Value %s not found\n", name);
	}
}

void reverseList(LinkedList* list) {
	Node* prev = NULL;
	Node* current = list->head;
	Node* next = NULL;

	while (current != NULL) {
		next = current->nextNode;
		current->nextNode = prev;
		prev = current;
		current = next;
	}

	list->head = prev;
}

Node* find(LinkedList* list, const char* name) {
	if (list->head == NULL || strlen(name) == 0) return NULL;

	Node* temp = list->head;
	while (temp != NULL) {
		if (strcmp(temp->name, name) == 0) return temp;
		temp = temp->nextNode;
	}

	return NULL;
}

int main() {
	LinkedList list = { NULL, 0 };
	
	push(&list, "Node1");
	push(&list, "Node2");

	printLinkedList(&list);
	printf("Size: %d\n", list.size);

	pushFront(&list, "Node3");
	printLinkedList(&list);

	insertAt(&list, "Node4", 1);
	printLinkedList(&list);

	deleteAt(&list, 2);
	printLinkedList(&list);

	reverseList(&list);
	printLinkedList(&list);

	deleteNodeByValue(&list, "Node4");
	printLinkedList(&list);

	Node* findNode = find(&list, "Node3");
	if (findNode == NULL)
		printf("Node not found\n");
	else
		printf("Value of the node: %s\n", findNode->name);

	freeLinkedList(&list);
	printLinkedList(&list);

	printf("Size: %d\n", list.size);
	printf("Empty: %d", isEmpty(&list));

	return 0;
}