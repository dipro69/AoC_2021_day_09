#include "CStack.h"
#include <iostream>

using namespace std;

CStack::CStack()
{
	CStackNode* ptr_stack_root = NULL;
	init();
}

CStack::~CStack()
{
	exit();
}

void CStack::init()
{

}

void CStack::pushItem(int data)
{
	push(&ptr_stack_root, data);
}

int CStack::popItem()
{
	cout << pop(&ptr_stack_root) << " popped from stack\n";
	return 0;
}

int CStack::peekItem()
{
	cout << "Top element is " << peek(ptr_stack_root) << "\n";
	return 0;
}

int CStack::exit()
{
	cout << "Elements present in stack : ";
	while (!isEmpty(ptr_stack_root))
	{
		// print top element in stack
		cout << peek(ptr_stack_root) << " ";
		// remove top element in stack
		pop(&ptr_stack_root);
	}
	cout << "\n";

	return 0;
}

CStackNode* CStack::newNode(int data)
{
	// create a new pointer to a stack node object
	CStackNode* ptr_stackNode = new CStackNode();
	// put the data item in the new stack node data attribute
	ptr_stackNode->data = data;
	// the new stack node doesn't point to another stack node yet
	ptr_stackNode->next = NULL;
	// return the pointer to the new stack node object
	return ptr_stackNode;
}

int CStack::isEmpty(CStackNode* ptr_root)
{
	// check if this stack node object exists on the stack
	return !ptr_root;
}

void CStack::push(CStackNode** ptr_root, int data)
{
	// create a pointer to a new stack node object with the data item
	CStackNode* ptr_stackNode = newNode(data);
	// let the new StackNode object point to the root StackNode object
	ptr_stackNode->next = *ptr_root;
	// replace the old root StackNode with the new StackNode
	*ptr_root = ptr_stackNode;
	// show a message
	cout << data << " pushed to stack\n";
}

int CStack::pop(CStackNode** ptr_root)
{
	// check if this stack node object exists
	if (isEmpty(*ptr_root))
		return INT_MIN;
	// store the stack root object in a temp pointer
	CStackNode* ptr_temp = *ptr_root;
	// next pointer from object to pop becomes the new root pointer
	*ptr_root = (*ptr_root)->next;
	// get th evalue to pop
	int popped = ptr_temp->data;
	// delete the stack node object to pop in memory
	delete(ptr_temp);

	return popped;
}

int CStack::peek(CStackNode* ptr_root)
{
	if (isEmpty(ptr_root))
		return INT_MIN;
	return ptr_root->data;
}
