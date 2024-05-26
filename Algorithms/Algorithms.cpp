#include <iostream>
#include <vector>

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

template <class T> Stack<T>::Stack() {			// 4
	top = -1;				// 1
	size = 1;				// 1
	arr = new T[size];			// 2
}

template <class T> Stack<T>::~Stack() {			// 1
	delete[] arr;			// 1
}

template <class T> void Stack<T>::Reallocate() {			// 7
	T* temp = new T[size * 2];			// 2
	memcpy(temp, arr, size*sizeof(T));			// 1
	size *= 2;			// 2
	delete[] arr;			// 1
	arr = temp;			// 1
}

template <class T> bool Stack<T>::IsEmpty() {			// 2
	return top == -1;			// 2
}

template <class T> int Stack<T>::GetLength() {			// 2
	return top + 1;			// 2
}

template <class T> void Stack<T>::ShowAll() {
	if (IsEmpty()) {			// 3
		cout << "Stack is empty" << endl;			// 1
	}
	for (int i = GetLength(); i > 0; i--) {			// 4 + 1 + (n)(0)Σ(1 + 1 + 1)
		cout << arr[i - 1] << " ";			// 1
	}
}

template <class T> void Stack<T>::Push(T value) {			// 6
	if (GetLength() == size) {			// 4
		Reallocate();			// 1
	}
	arr[++top] = value;			// 2
}

template <class T> T Stack<T>::ShowHead() {			// 5
	if (IsEmpty()) {			// 2
		return NULL;			// 1
	}
	return arr[top];			// 2
}

template <class T> T Stack<T>::Pop() {			// 5
	if (IsEmpty()) {			// 2
		return NULL;			// 1
	}
	return arr[top--];			// 2
}

template <class T> T* Stack<T>::GetHead() {			// 2
	return &arr[top];			// 2
}

template <class T> class StackSort : public Stack<T> {
public:
	using Stack<T>::GetLength;
	using Stack<T>::Pop;
	using Stack<T>::ShowHead;
	using Stack<T>::Push;
	using Stack<T>::GetHead;

	T Get(int pos);
	void Set(int pos, T num);
	void Sort(int N);
	T& operator[](int n);
};

template <class T> T StackSort<T>::Get(int pos) {			// 33 + 26n 
	Stack<T> temp;			// 4
	T target;			// 1

	for (int i = GetLength() - 1; i > pos; i--) {		// 4 + 1 + (0)(n - 1)Σ(1 + 1 + 11)
		temp.Push(Pop());			// 11
	}
	target = ShowHead();			// 5
	for (int i = temp.GetLength(); i > 0; i--) {			// 3 + 1 + (0)(n)Σ(1 + 1 + 11)
		Push(temp.Pop());			// 11
	}

	return target;			// 1
}

template <class T> void StackSort<T>::Set(int pos, T num) {			// 26 + 26n
	Stack<T> temp;			// 4
	
	for (int i = GetLength() - 1; i > pos; i--) {		// 4 + 1 + (0)(n - 1)Σ(1 + 1 + 11)
		temp.Push(Pop());			// 11
	}
	Pop();
	Push(num);
	for (int i = temp.GetLength(); i > 0; i--) {			// 3 + 1 + (0)(n)Σ(1 + 1 + 11)
		Push(temp.Pop());			// 11
	}
}

//template <class T> T StackSort<T>::operator[](int n) {
//	return Get(n);
//}

template <class T> T& StackSort<T>::operator[](int n) {			// 31 + 26n
	Stack<T> temp;			// 4
	T* target;			// 1

	for (int i = GetLength() - 1; i > n; i--) {			// 4 + 1 + (0)(n - 1)Σ(1 + 1 + 11)
		temp.Push(Pop());			// 11
	}
	target = GetHead();			// 2
	for (int i = temp.GetLength(); i > 0; i--) {			// 3 + 1 + (0)(n)Σ(1 + 1 + 11)
		Push(temp.Pop());			// 11
	}

	return *target;			// 2
}

template <class T> void StackSort<T>::Sort(int n) {
	int m = 0;			// 2

	for (int i = 0; i < n; i++) {			// 2 + 1 + (0)(n)Σ(1 + 1 + 33 + 26n)
		m = max(m, Get(i));			// 33 + 26n
	}

	StackSort<int> countStack = StackSort<int>();

	for (int i = 0; i <= m; i++) {			// 2 + 1 + (0)(m)Σ(1 + 1 + 6)
		countStack.Push(0);			// 6
	}

	for (int i = 0; i < n; i++) {			// 2 + 1 + (0)(n)Σ(1 + 1 + 130 + 104n)
		countStack.Set(Get(i), countStack.Get(Get(i)) + 1);			// 131 + 104n
	}

	for (int i = 1; i <= m; i++) {			// 2 + 1 + (0)(m)Σ(1 + 1 + 132 + 104n)
		countStack.Set(i, countStack.Get(i) + countStack.Get(i - 1));			// 132 + 104n

	}

	StackSort<int> outputStack;			// 4

	for (int i = 0; i < n; i++) { outputStack.Push(0); }			// 2 + 1 + (0)(n)Σ(1 + 1 + 6)

	for (int i = n - 1; i >= 0; i--)			// 3 + 1 + (0)(n - 1)Σ(1 + 1 + 262 + 208n)
	{
		outputStack.Set(countStack.Get(Get(i)) - 1, Get(i));			// 131 + 104n
		countStack.Set(Get(i), countStack.Get(Get(i)) - 1);			// 131 + 104n
	}

	//*this = outputStack&;

	for (int i = 0; i < n; i++) {			// 2 + 1 + (0)(n)Σ(1 + 1 + 36 + 26n)
		Set(i, outputStack.Pop());			// 36 + 26n
	}
}

int main()
{
	StackSort<int> stack;

	for (int i = 1; i <= 10; i++) {
		stack.Push(i);
	}
	//stack.ShowAll();
	//cout << endl;

	//cout << stack[1] << endl;
	stack[1] = 100;

	stack.ShowAll();
	cout << endl;
}
