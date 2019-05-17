#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>
#include "Debug_Macros.h"
using namespace std;

template<typename T>
class Vector {
public:
	Vector();
	Vector(unsigned int cap);
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void push_back(const T& item);
	void pop_back();
	void pop_front();
	void clear();
	bool is_empty() const;
	int size() const;
	unsigned int capacity() const;
	T at(unsigned int i) const;
	friend ostream& operator<<(ostream& outs, const Vector<T>& vector) {
		vector.print(outs);
		return outs;
	}
	T& operator[](const unsigned int index);
	T& operator[](const unsigned int index) const;
private:
	void print(ostream& outs) const;
	void grow();
private:
	T* arr;
	unsigned int cap;
	unsigned int _size;
};

template<typename T>
Vector<T>::Vector()
{
	DEBUG("VECTOR CREATED OF CAP 4");
	DEBUG("===================");
	cap = 4;
	_size = 0;
	arr = new T[cap];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	DEBUG("VECTOR COPY CONSTRUCTOR");
	DEBUG("===================");
	this->_size = other._size;
	this->cap = other.cap;
	this->arr = new T[cap];
	for (unsigned int i = 0; i < other._size; i++) {
		this->arr[i] = other.arr[i];
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this == &other) return *this;
	DEBUG("VECTOR ASSIGMENT OPEARTOR");
	DEBUG("===================");
	this->clear();
	this->_size = other._size;
	this->cap = other.cap;
	this->arr = new T[cap];
	for (unsigned int i = 0; i < other._size; i++) {
		this->arr[i] = other.arr[i];
	}
	return *this;
}

template<typename T>
T& Vector<T>::operator[](const unsigned int index)
{
	return arr[index];
}

template<typename T>
T& Vector<T>::operator[](const unsigned int index) const
{
	return arr[index];
}

template<typename T>
Vector<T>::Vector(unsigned int cap)
{
	DEBUG("VECTOR CREATED OF CAP " +
		string(to_string(cap)));
	DEBUG("===================");
	this->cap = cap;
	_size = 0;
	arr = new T[this->cap];
}

template<typename T>
Vector<T>::~Vector()
{
	DEBUG("VECTOR DEALLOCATED");
	DEBUG("===================");
	delete[] arr;
}

template<typename T>
void Vector<T>::push_back(const T& item)
{
	DEBUG("VECTOR PUSH BACK");
	//DEBUG(item);
	DEBUG("===================");
	//Check if it has enough space
	//if not grow the array
	this->grow();
	arr[_size] = item;
	this->_size++;
}

template<typename T>
void Vector<T>::pop_back()
{
	if (_size == 0) {
		return;
	}
	_size--;
}

template<typename T>
void Vector<T>::pop_front()
{
	if (_size == 0) {
		return;
	}
	for (unsigned int i = 1; i < _size; i++) {
		arr[i - 1] = arr[i];
	}
	_size--;
}

template<typename T>
void Vector<T>::clear()
{
	delete[] arr;
	_size = 0;
	cap = 4;
	arr = new T[cap];
}

template<typename T>
bool Vector<T>::is_empty() const
{
	return (_size >= 1) ? 0 : 1;
}

template<typename T>
int Vector<T>::size() const
{
	return _size;
}

template<typename T>
unsigned int Vector<T>::capacity() const
{
	return cap;
}

template<typename T>
T Vector<T>::at(unsigned int i) const
{
	return arr[i];
}

template<typename T>
void Vector<T>::print(ostream& outs) const
{
	cout << "[";
	for (unsigned int i = 0; i < _size; i++) {
		outs << arr[i];
		if (i + 1 != _size)cout << ",";
	}
	cout << "]";
}

template<typename T>
void Vector<T>::grow()
{
	if (_size < cap) {
		return;
	}
	DEBUG("VECTOR GROWING TO: " +
		to_string(cap * 2));
	DEBUG("===================");
	T* temp = new T[cap * 2];
	for (unsigned int i = 0; i < _size; i++) {
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	cap *= 2;
}
#endif // VECTOR_H
