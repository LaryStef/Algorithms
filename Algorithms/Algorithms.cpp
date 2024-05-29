#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

template <class T> class Stack {
private:
	T* arr;
	int top;
	int size;
	void Reallocate();
public:
	unsigned long long int N_op;

	Stack();
	~Stack();
	T Pop();
	T ShowHead();
	void Push(T num);
	bool IsEmpty();
	void ShowAll();
	int GetLength();
	T* GetHead();
};

template <class T> Stack<T>::Stack() {
	N_op = 0;
	top = -1;				N_op += 1;
	size = 1;				N_op += 1;
	arr = new T[size];			N_op += 2;
}

template <class T> Stack<T>::~Stack() {
	delete[] arr;
}

template <class T> void Stack<T>::Reallocate() {
	T* temp = new T[size * 2];			N_op += 2;
	memcpy(temp, arr, size * sizeof(T));			N_op += 1;
	size *= 2;			N_op += 2;
	delete[] arr;			N_op += 1;
	arr = temp;			N_op += 1;
}

template <class T> bool Stack<T>::IsEmpty() {
	N_op += 2;
	return top == -1;
}

template <class T> int Stack<T>::GetLength() {
	N_op += 2;
	return top + 1;
}

template <class T> void Stack<T>::ShowAll() {
	if (IsEmpty()) {
		cout << "Stack is empty" << endl;
	}

	for (int i = GetLength(); i > 0; i--) {
		cout << arr[i - 1] << " ";
	}
}

template <class T> void Stack<T>::Push(T value) {
	if (GetLength() == size) {
		N_op += 2;
		Reallocate();			N_op += 1;
	}
	arr[++top] = value;			N_op += 2;
}

template <class T> T Stack<T>::ShowHead() {
	N_op += 1;
	if (IsEmpty()) {
		return NULL;			N_op += 1;
	}
	N_op += 2;
	return arr[top];
}

template <class T> T Stack<T>::Pop() {
	N_op += 1;
	if (IsEmpty()) {
		return NULL;			N_op += 1;
	}
	N_op += 2;
	return arr[top--];
}

template <class T> T* Stack<T>::GetHead() {
	N_op += 2;
	return &arr[top];
}

template <class T> class StackSort : public Stack<T> {
public:
	using Stack<T>::GetLength;
	using Stack<T>::Pop;
	using Stack<T>::ShowHead;
	using Stack<T>::Push;
	using Stack<T>::GetHead;
	using Stack<T>::N_op;

	T Get(int pos);
	void Set(int pos, T num);
	void Sort(int N);
	T& operator[](int n);
};

template <class T> T StackSort<T>::Get(int pos) {
	Stack<T> temp;			N_op += 1;
	T target;			N_op += 1;

	N_op += 4;
	for (int i = GetLength() - 1; i > pos; i--) {
		temp.Push(Pop());			N_op += 2;
	}
	target = ShowHead();
	N_op += 3;
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());			N_op += 2;
	}

	N_op += 1;
	return target;
}

template <class T> void StackSort<T>::Set(int pos, T num) {
	Stack<T> temp;			N_op += 1;

	N_op += 4;
	for (int i = GetLength() - 1; i > pos; i--) {
		temp.Push(Pop());			N_op += 2;
	}
	Pop();
	Push(num);
	N_op += 3;
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());			N_op += 2;
	}
}

template <class T> T& StackSort<T>::operator[](int n) {
	Stack<T> temp;			N_op += 1;
	T* target;		 N_op += 1;

	N_op += 4;
	for (int i = GetLength() - 1; i > n; i--) {
		temp.Push(Pop()); N_op += 2;
	}
	target = GetHead();
	N_op += 3;
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());			N_op += 2;
	}

	N_op += 2;
	return *target;
}

//template <class T> void StackSort<T>::Sort(int n) {
//	int m = 0;			N_op += 2;
//
//	N_op += 3;
//	for (int i = 0; i < n; i++) {
//		m = max(m, Get(i));			N_op += 4;
//	}
//
//	StackSort<int> countStack; N_op += 1;
//
//	N_op += 3;
//	for (int i = 0; i <= m; i++) {
//		countStack.Push(0);		N_op += 2;
//	}
//
//	N_op += 3;
//	for (int i = 0; i < n; i++) {
//		countStack.Set(Get(i), countStack.Get(Get(i)) + 1);			N_op += 3;
//	}
//
//	N_op += 3;
//	for (int i = 1; i <= m; i++) {
//		countStack.Set(i, countStack.Get(i) + countStack.Get(i - 1));		N_op += 4;
//	}
//
//	StackSort<int> outputStack;		N_op += 1;
//
//	N_op += 3;
//	for (int i = 0; i < n; i++) { outputStack.Push(0); N_op += 2; }
//
//	N_op += 4;
//	for (int i = n - 1; i >= 0; i--)
//	{
//		outputStack.Set(countStack.Get(Get(i)) - 1, Get(i));			N_op += 1;
//		countStack.Set(Get(i), countStack.Get(Get(i)) - 1);		N_op += 1;
//		N_op += 2;
//	}
//
//	N_op += 3;
//	for (int i = 0; i < n; i++) {
//		Set(i, outputStack.Pop());			N_op += 2;
//	}
//
//	N_op += countStack.N_op + outputStack.N_op;
//}

template<class T> void StackSort<T>::Sort(int n) {

	StackSort<int> countStack;
	StackSort<int> resStack;

	for (int i = 0; i < n; i++) {
		countStack.Push(0);
		resStack.Push(0);
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (Get(i) > Get(j)) {
				countStack.Set(i, countStack.Get(i) + 1);
			}
			else {
				countStack.Set(j, countStack.Get(j) + 1);
			}

		}

	}

	for (int i = 0; i < n; i++) {
		resStack.Set(countStack.Get(i), Get(i));
	}

	for (int i = 0; i < n; i++) {

		Set(i, resStack.Pop());
	}
}

int main()
{
	//StackSort<int> stack;

	//for (int i = 0; i < 10; i++) {
	//	stack.Push(rand() % 101);
	//}

	//stack.ShowAll();
	//cout << endl;
	//stack.Sort(10);
	//stack.ShowAll();

	unsigned long long int start, final;

	for (int i = 1; i < 11; i++) {
		StackSort<int> stack;

		for (int j = 0; j < i * 100; j++) {
			stack.Push(rand() % 1000);
		}

		start = GetTickCount64();
		stack.Sort(i * 100);
		final = GetTickCount64();

		cout << "test: " << i << "\n";
		cout << "number of elements: " << i * 100 << "\n";
		cout << "sort time: " << final - start << "\n";
		cout << "number of operations: " << stack.N_op << "\n";

		cout << endl;
	}
	

	system("pause");
}
