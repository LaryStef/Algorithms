
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

template <class T> Stack<T>::Stack() {
	top = 0;
	size = 0;
	arr = new T[size];
}

template <class T> Stack<T>::~Stack() {
	delete[] arr;
}

template <class T> void Stack<T>::Reallocate() {
	T* temp = new T[size * 2];
	copy(arr, arr + size, temp);
	arr = move(temp);
	delete arr;
	size *= 2;
}
	
template <class T> bool Stack<T>::IsEmpty() {
	return top == 0;
}

template <class T> int Stack<T>::GetLength() {
	return top;
}

template <class T> void Stack<T>::ShowAll() {
	if (IsEmpty()) {
		cout << "Stack is empty" << endl;
	}
	for (int i = 0; i < size; i++) {
		cout << arr[i] << endl;
	}
}

template <class T> void Stack<T>::Push(T value) {
	if (GetLength() == size - 1) {
		Reallocate();
	}
	arr[++top] = value;
}

template <class T> T Stack<T>::ShowHead() {
	if (!IsEmpty()) {
		return NULL;
	}
	return arr[top];
}

template <class T> T Stack<T>::Pop() {
	if (!IsEmpty) {
		return NULL;
	}
	return arr[top--];
}
