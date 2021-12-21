#pragma once

// A structure to represent a stack
class CStackNode
{
public:
	int data;
	CStackNode* next;
};

// the class which manages the stack nodes
class CStack
{
public:
	CStack();
	~CStack();
	void pushItem(int data);
	int popItem();
	int peekItem();
private:
	void init();
	int exit();
	CStackNode* newNode(int data);
	int isEmpty(CStackNode* ptr_root);
	void push(CStackNode** ptr_root, int data);
	int pop(CStackNode** ptr_root);
	int peek(CStackNode* ptr_root);

	CStackNode* ptr_stack_root;
};

