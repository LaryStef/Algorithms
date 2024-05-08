#include <iostream>

using namespace std;

template <class T> class Stack {
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

template <class T> Stack<T>::Stack() {
	top = -1;
	size = 1;
	arr = new T[size];
}

template <class T> Stack<T>::~Stack() {
	delete[] arr;
}

template <class T> void Stack<T>::Reallocate() {
	T* temp = new T[size * 2];
	copy(arr, arr + size, temp);
	arr = move(temp);
	size *= 2;
}

template <class T> bool Stack<T>::IsEmpty() {
	return top == -1;
}

template <class T> int Stack<T>::GetLength() {
	return top + 1;
}

template <class T> void Stack<T>::ShowAll() {
	if (IsEmpty()) {
		cout << "Stack is empty" << endl;
	}
	for (int i = 0; i < GetLength(); i++) {
		cout << arr[i] << " ";
	}
}

template <class T> void Stack<T>::Push(T value) {
	if (GetLength() == size) {
		Reallocate();
	}
	arr[++top] = value;
}

template <class T> T Stack<T>::ShowHead() {
	if (IsEmpty()) {
		return NULL;
	}
	return arr[top];
}

template <class T> T Stack<T>::Pop() {
	if (IsEmpty()) {
		return NULL;
	}
	return arr[top--];
}

template <class T> class StackSort : public Stack<T> {
public:
	using Stack<T>::GetLength;
	using Stack<T>::Pop;
	using Stack<T>::ShowHead;
	using Stack<T>::Push;

	T Get(int pos);
	void Set(int pos, T num);
	void Sort(int N);
};

template <class T> T StackSort<T>::Get(int pos) {
	Stack<T> temp = Stack<T>();
	T target;

	for (int i = GetLength() - 1; i > pos; i--) {
		temp.Push(Pop());
	}
	target = ShowHead();
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());
	}

	return target;
}

template <class T> void StackSort<T>::Set(int pos, T num) {
	Stack<T> temp = Stack<T>();
	
	for (int i = GetLength() - 1; i > pos; i--) {
		temp.Push(Pop());
	}
	temp.Pop();
	Push(num);
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());
	}
}

template <class T> void StackSort<T>::Sort(int n) {
	return NULL;
}

int main()
{
	StackSort<int> stack = StackSort<int>();

	for (int i = 0; i < 20; i++) {
		stack.Push(i);
	}
	cout << stack.Get(17) << endl;
	stack.ShowAll();
}
