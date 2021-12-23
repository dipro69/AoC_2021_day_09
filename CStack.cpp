# include "CDataElement.h"
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

void CStack::pushItem(CDataElement* ptr_data_element)
{
	push(&ptr_top_stack_node, ptr_data_element);
}

int CStack::popItem()
{
	cout << pop(&ptr_top_stack_node) << " popped from stack\n";
	return 0;
}

int CStack::peekItem()
{
	cout << "Top element is " << peek(ptr_top_stack_node) << "\n";
	return 0;
}

int CStack::printItems()
{
	printStack(ptr_top_stack_node);

	return 0;
}

void CStack::pushFirst()
{
	push(&ptr_top_stack_node, NULL);
}

int CStack::exit()
{
	cout << "Elements present in stack : ";
	while (!isEmpty(ptr_top_stack_node))
	{
		// print top element in stack
		cout << peek(ptr_top_stack_node) << " ";
		// remove top element in stack
		pop(&ptr_top_stack_node);
	}
	cout << "\n";

	return 0;
}

CStackNode* CStack::newNode(CDataElement* ptr_data_element)
{
	// create a new pointer to a stack node object
	CStackNode* ptr_stackNode = new CStackNode();
	// put the data item in the new stack node data attribute
	ptr_stackNode->copy(ptr_data_element);
	// the new stack node doesn't point to another stack node yet
	ptr_stackNode->previous = NULL;
	// return the pointer to the new stack node object
	return ptr_stackNode;
}

int CStack::isEmpty(CStackNode* ptr_root)
{
	// check if this stack node object exists on the stack
	return !ptr_root;
}

/*
A pointer variable is an object that can point to another object. Here int *ptr = NULL; declares ptr as a pointer object, that potentially points to an object of int.

The value initially stored into this pointer object is NULL (it is initialized to NULL, so ptr does not point to any object).

Now, ptr too resides in memory. It needs enough bytes to contain the address of the pointed-to object. So it too needs to have an address. Therefore

ptr evaluates to the address of object that ptr points to.
&ptr evaluates to the location of the ptr object itself in memory
*ptr evaluates to the value of the object that ptr points to, if it points to an object. If it does not point to an object, then the behaviour is undefined.
*/

void CStack::push(CStackNode** ptr_root, CDataElement* ptr_data_element)
{
	// create a pointer to a new stack node object with the data item
	CStackNode* ptr_stackNode = newNode(ptr_data_element);
	// let the new StackNode object point to the root StackNode object
	ptr_stackNode->previous = *ptr_root;
	// replace the old root StackNode with the new StackNode
	*ptr_root = ptr_stackNode;
	// show a message
	cout << ptr_stackNode->getIndex() << " pushed to stack\n";
}

int CStack::pop(CStackNode** ptr_root)
{
	// check if this stack node object exists
	if (isEmpty(*ptr_root))
		return INT_MIN;
	// store the stack root object in a temp pointer
	CStackNode* ptr_temp = *ptr_root;
	// next pointer from object to pop becomes the new root pointer
	*ptr_root = (*ptr_root)->previous;
	// get th evalue to pop
	int popped = ptr_temp->getIndex();
	// delete the stack node object to pop in memory
	delete(ptr_temp);

	return popped;
}

int CStack::peek(CStackNode* ptr_root)
{
	if (isEmpty(ptr_root))
		return INT_MIN;
	return ptr_root->getIndex();
}

int CStack::printStack(CStackNode* ptr_root)
{
	CStackNode* ptr_temp_stack_node = NULL;
	ptr_temp_stack_node = ptr_root;

	cout << "Elements present in stack:\n";
	while (!isEmpty(ptr_temp_stack_node))
	{
		// print top element in stack
		cout << "element: " << peek(ptr_temp_stack_node) << "\n";
		// switch to previous stack node
		ptr_temp_stack_node = ptr_temp_stack_node->previous;
	}

	return 0;
}

CStackNode::CStackNode()
{
	this->previous = NULL;
}

int CStackNode::copy(CDataElement* ptr_copy_item)
{
	this->row = ptr_copy_item->getRow();
	this->col = ptr_copy_item->getRow();
	this->index = ptr_copy_item->getIndex();
	this->risk_level = ptr_copy_item->getRiskLevel();
	
	return 0;
}
