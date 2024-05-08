#pragma once
#include <iostream>

using namespace std;

template <class T> class Stack
{
private:
	T* arr;
	int top;
	int size;
	void Reallocate();
public:
	Stack();
	~Stack();
	T Pop();
	T ShowHead();
	void Push(T num);
	bool IsEmpty();
	void ShowAll();
	int GetLength();
};

