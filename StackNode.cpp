// C++ program for linked list implementation of stack
// #include <bits/stdc++.h>
// #include "StackNode.h"
using namespace std;

// A structure to represent a stack
class StackNode
{
public:
	int data;
	StackNode* next;
};

StackNode* newNode(int data);
int isEmpty(StackNode* ptr_root);
void push(StackNode** ptr_root, int data);
int pop(StackNode** ptr_root);
int peek(StackNode* ptr_root);
void printINT_MIN();

StackNode* newNode(int data)
{
	StackNode* ptr_stackNode = new StackNode();
	ptr_stackNode->data = data;
	ptr_stackNode->next = NULL;
	return ptr_stackNode;
}

int isEmpty(StackNode* ptr_root)
{
	return !ptr_root;
}

void push(StackNode** ptr_root, int data)
{
	// create a new StackNode
	StackNode* ptr_stackNode = newNode(data);
	// let the new StackNode point to the former root StackNode
	ptr_stackNode->next = *ptr_root;
	// replace the old root StackNode with the new StackNode
	*ptr_root = ptr_stackNode;
	// show a message
	cout << data << " pushed to stack\n";
}

int pop(StackNode** ptr_root)
{
	if (isEmpty(*ptr_root))
		return INT_MIN;
	StackNode* ptr_temp = *ptr_root;
	*ptr_root = (*ptr_root)->next;
	int popped = ptr_temp->data;
	free(ptr_temp);

	return popped;
}

int peek(StackNode* ptr_root)
{
	if (isEmpty(ptr_root))
		return INT_MIN;
	return ptr_root->data;
}

void printINT_MIN()
{
	cout << "\nÏNT_MIN" << INT_MIN << "\n";
}

// This is code is contributed by rathbhupendra
