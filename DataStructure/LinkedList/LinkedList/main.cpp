#include <iostream>

using namespace std;

//definition of Node
class Node {
public:
	int data;
	Node *next;
};

void PrintLinkedList(Node *node) {
	printf("Node values:");
	while (node != NULL) {
		printf(" %d ", node->data);
		node = node->next;
	}
	printf("\n");
}

/*
There are three ways of inserting new nodes:
1) At the front of the linked list
2) After a given node.
3) At the end of the linked list.

so we will define three functions:
* push() - > At the front of the linked list

* InsertAfter() - > After a given node.

* append() - > At the end of the linked list.
*/

void push(Node **head_node_ref, int new_data) {
	//**head_node_ref -> pointer to another pointer
	//Creating new nodes
	Node *new_node = NULL;

	//Allocate new node in the heap
	new_node = new Node();

	//insert data in the new node
	new_node->data = new_data;

	//insert next node at the head ref
	new_node->next = *head_node_ref;

	//And head node will point to new node
	*head_node_ref = new_node;
}

void append(Node **head_node_ref, int new_data) {
	//Creating new nodes
	Node *new_node = NULL;

	//Allocate new node in the heap
	new_node = new Node();

	//insert data in the new node
	new_node->data = new_data;

	//insert next node at NULL as it will be append at the last of the node
	new_node->next = NULL;

	//Check if the head node is the last node
	if (*head_node_ref == NULL) {
		*head_node_ref = new_node;
		return;
	}
	else {
		//if not then
		Node *last = *head_node_ref;

		//Keep moving toward the last node
		while (last->next != NULL) {
			last = last->next;
		}
		//When last node is found, add that new node at the end of the last node
		last->next = new_node;

	}
}

void InsertAfterNode(Node *previous_node, int new_data) {
	//Check whether the previous node is NULL or not. If it is NULL we cant add any node after that
	if (previous_node == NULL) {
		cout << "The previous node can't be NULL" << endl;
		return;
	}

	//If not then
	//Creating new nodes
	Node *new_node = NULL;
	//Allocate new node in the heap
	new_node = new Node();

	//insert data in the new node
	new_node->data = new_data;

	//connect new node next to previous node next
	new_node->next = previous_node->next;

	//previous_node->next should point to new node
	previous_node->next = new_node;
}


void DeleteNode(Node **head_node_ref, int value) {
	//Creating new nodes
	Node *temp = NULL, *prev = NULL;
	//Allocate new node in the heap
	temp = new Node();
	prev = new Node();

	temp = *head_node_ref;
	//if head_node_ref is NULL
	if (temp == NULL) {
		cout << "The input node can not be NULL" << endl;
		return;
	}

	//If the value exist at the first node
	if (temp != NULL && temp->data == value) {
		*head_node_ref = temp->next;	//move head ref to temp->next
		free(temp);	//free temp
		return;
	}

	// Search for the value to be deleted, keep track of the 
	// previous node as we need to change 'prev->next' 
	while (temp != NULL and temp->data != value) {
		prev = temp;
		temp = temp->next;
	}

	//un-link the node from linked List
	prev->next = temp->next;
	free(temp);
}

int main() {
	//Creating new nodes
	Node *head = NULL;
	Node *second = NULL;
	Node *third = NULL;

	//Allocate 5 nodes in the heap
	head = new Node();
	second = new Node();
	third = new Node();

	head->data = 2;	// assign data in first node
	head->next = second; // Link first node with

	second->data = 3;	// assign data in first node
	second->next = third; // Link second node with

	third->data = 6;	// assign data in first node
	third->next = NULL; // Link fifth node with NULL as this is the end node of Linked List

	PrintLinkedList(head);

	push(&head, 1);
	PrintLinkedList(head);

	push(&head, 0);
	PrintLinkedList(head);

	append(&head, 7);
	PrintLinkedList(head);

	append(&head, 8);
	PrintLinkedList(head);

	InsertAfterNode(head->next->next->next, 4);
	PrintLinkedList(head);

	InsertAfterNode(head->next->next->next->next, 5);
	PrintLinkedList(head);

	DeleteNode(&head, 7);
	PrintLinkedList(head);

	DeleteNode(&head, 10);

	return 0;
}