# include "CDataElement.h"
#pragma once

// A structure to represent a stack
class CStackNode : public CDataElement
{
public:
	CStackNode();
	CStackNode* previous;
	int copy(CDataElement* ptr_copy_item);
};

// the class which manages the stack nodes
class CStack
{
public:
	CStack();
	~CStack();
	void pushItem(CDataElement* ptr_data_element);
	int popItem();
	int peekItem();
	int printItems();
	void pushFirst();
private:
	void init();
	int exit();
	CStackNode* newNode(CDataElement* ptr_data_element);
	int isEmpty(CStackNode* ptr_root);
	void push(CStackNode** ptr_root, CDataElement* ptr_data_element);
	int pop(CStackNode** ptr_root);
	int peek(CStackNode* ptr_root);
	int printStack(CStackNode* ptr_root);

	CStackNode* ptr_top_stack_node;
};

