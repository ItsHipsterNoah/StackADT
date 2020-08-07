#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <iostream>


struct Node
{
	int data;
	Node* next;
};

class Stack
{
public:
	Stack();
	bool isEmpty();
	bool isFull();
	void push(int data);
	void pop(void);
	int top(void);
	void print(void);
	~Stack();
private:
	Node* topPtr;
};

Stack::Stack() : topPtr{ nullptr }
{
}

bool Stack::isEmpty()
{
	return !topPtr;
}

bool Stack::isFull()
{
	try
	{
		Node* newNode = new Node();
		delete newNode;
		return true;
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

void Stack::push(int data)
{
	Node* newNode = new Node();
	newNode->data = data;
	// if list is empty, create a new node
	if (!topPtr) {
		this->topPtr = newNode;
	}
	else {
		newNode->next = topPtr;
		topPtr = newNode;
	}
}


int Stack::top(void)
{
	return topPtr->data;
}

void Stack::print(void)
{
	Node* tracker{ topPtr };
	while (tracker) {
		std::cout << tracker->data << std::endl;
		tracker = tracker->next;
	}
}


void Stack::pop(void)
{
	if (!topPtr) {
		std::cout << "ERROR! Stack is empty" << std::endl;
	}
	else {
		Node* temp = topPtr->next;
		delete topPtr;
		topPtr = temp;
	}
}

Stack::~Stack()
{
	Node* temp{ nullptr };
	while (topPtr) {
		temp = topPtr->next;
		delete topPtr;
		topPtr = temp;
	}
	delete topPtr;
}


int main()
{
	std::cout << std::boolalpha << std::endl;
	Stack stack;
	stack.push(5);
	stack.push(4);
	stack.push(3);
	stack.push(2);
	stack.push(1);
	stack.print();
	std::cout << stack.isEmpty() << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < 5; i++) {
		stack.pop();
	}
	stack.print();
	std::cout << stack.isEmpty() << std::endl;
	_CrtDumpMemoryLeaks();
}