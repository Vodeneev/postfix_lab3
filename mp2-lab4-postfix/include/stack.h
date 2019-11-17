#ifndef __STACK_H__
#define __STACK_H__
#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
	T* begin;
	T* end;
	int size;
public:
	Stack();
	Stack(int _n);
	Stack(const Stack& _A);
	~Stack();
	void Push(T a);
	T top();
	T pop();
	bool empty();
	int Size();
	bool operator==(Stack<T>& a);
	friend ostream& operator<<(ostream& out, const Stack& a) {

		for (int i = 0; i < a.end - a.begin; i++)
			out << a.begin[i] << ' ';
		return out;

	}
};
template <class T>
Stack<T>::Stack() {
	size = 1000;
	begin = new T[size];
	end = begin;
}
template <class T>
Stack<T>::Stack(int _n) {
	if (_n < 0)
		throw 1;
	size = _n;
	begin = new T[size];
	end = begin;
}

template <class T>
Stack<T>::Stack(const Stack& _A) {
	begin = new T[_A.size];
	size = _A.size;
	end = begin + (_A.end - _A.begin);
	for (int i = 0; i < _A.end - _A.begin; i++)
	{
		begin[i] = _A.begin[i];
	}

}

template <class T>
void Stack<T>::Push(T a) {
	if ((end - begin) > size - 1) {
		size = size + int(size * 1.3);
		T* tmp = new T[size];
		for (int i = 0; i < end - begin; i++)
			tmp[i] = begin[i];
		end = tmp + (end - begin);
		delete[] begin;
		begin = tmp;
	}
	*end = a;
	end++;

}

template <class T>
T Stack<T>::top() {
	if (end == begin)
		throw 777;
	return *(end - 1);
}

template <class T>
T Stack<T>::pop() {
	if (end == begin)
		throw 777;
	T elem = *(end - 1);
	end--;
	return elem;

}
template <class T>
bool Stack<T>::empty() {
	if (begin == end)
		return true;
	else
		return false;
}
template <class T>
int Stack<T>::Size() {
	return size;
}

template <class T>
Stack<T> :: ~Stack() {
	delete[] begin;
}
template <class T>
bool Stack<T>::operator==(Stack<T>& a)
{
	if (end - begin != a.end - a.begin)
		return false;
	for (int i = 0; i < end - begin; ++i)
		if (a.begin[i] != begin[i])
			return false;
	return true;
}
#endif
