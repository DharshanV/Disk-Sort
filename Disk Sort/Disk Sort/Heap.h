#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <iomanip>
#include <assert.h>
#include "vector.h"
using namespace std;

template<typename T>
class Heap {
public:
	Heap();
	Heap(unsigned int size);
	Heap(const Heap<T>& other);
	Heap<T>& operator=(const Heap<T>& other);
	void insert(const T& insert_me);
	T pop();
	bool is_empty() const;
	int size() const;
	friend ostream& operator << (ostream& outs, const Heap<T>& print_me) {
		print_me.print_tree(outs);
		return outs;
	}
public:
	void heapSort(Vector<T>& vector);
private:
	void print_tree(ostream& outs = cout) const;
	void print_tree(unsigned int root,
		int level = 0, ostream& outs = cout) const;
	bool is_leaf(int i) const;
	unsigned int parent_index(unsigned int i);
	int left_child_index(int i)const;
	int right_child_index(int i) const;
	int big_child_index(unsigned int i) const;
	void swap_with_parent(int i);
private:
	Vector<T> vector;
};

template<typename T>
Heap<T>::Heap() {
}

template<typename T>
Heap<T>::Heap(unsigned int size)
{
	this->vector = Vector<T>(size);
}

template<typename T>
Heap<T>::Heap(const Heap<T>& other)
{
	this->vector = Vector<T>(other.vector);
}

template<typename T>
Heap<T>& Heap<T>::operator=(const Heap<T>& other)
{
	if (this == &other) return *this;
	this->vector.clear();
	this->vector = Vector<T>(other.vector);
	return *this;
}

template<typename T>
void Heap<T>::heapSort(Vector<T>& vector)
{
	vector = Vector<T>(this->vector.size());
	Heap<T> temp(*this);
	while (!temp.is_empty())
	{
		vector.push_back(temp.pop());
	}
}

template<typename T>
void Heap<T>::print_tree(ostream& outs) const
{
	print_tree(0, 0, outs);
}

template<typename T>
void Heap<T>::print_tree(unsigned int root, int level, ostream & outs) const
{
	if ((int)root > vector.size() - 1) { return; }
	print_tree(right_child_index(root), level + 1, outs);
	outs << setw(level * 4) << vector.at(root) << endl;
	print_tree(left_child_index(root), level + 1, outs);
}

template<typename T>
bool Heap<T>::is_leaf(int i) const
{
	//Its a leaf when there no nodes left or right of it
	if (left_child_index(i) < vector.size()) { return false; }
	if (right_child_index(i) < vector.size()) { return false; }
	return true;
}

template<typename T>
unsigned int Heap<T>::parent_index(unsigned int i)
{
	//-1 when i is 0 since the root has not parent
	if (i <= 0 || i > int(vector.size())) return -1;
	return (i - 1) / 2;
}

template<typename T>
int Heap<T>::left_child_index(int i) const
{
	return i * 2 + 1;
}

template<typename T>
int Heap<T>::right_child_index(int i) const
{
	return i * 2 + 2;				//Since heap starts from 0
}

template<typename T>
int Heap<T>::big_child_index(unsigned int i) const
{
	if (i < 0 || i >= vector.size()) return -1;
	if (vector[left_child_index(i)] < 
		vector[right_child_index(i)]) {
		return left_child_index(i);
	}
	else {
		return right_child_index(i);
	}
}

template<typename T>
void Heap<T>::swap_with_parent(int i)
{
	int parentIndex = parent_index(i);
	if (parentIndex == -1) return;
	T temp = vector[parentIndex];
	vector[parentIndex] = vector[i];
	vector[i] = temp;
}

template<typename T>
void Heap<T>::insert(const T& insert_me)
{
	vector.push_back(insert_me);
	unsigned int i = vector.size() - 1;
	unsigned int pIndex = parent_index(i);
	//Adjust the new insert by bubbling back
	//up if its greater, until its valid
	while (i > 0 && vector[pIndex] > vector[i]) {
		swap_with_parent(i);
		i = pIndex;
		pIndex = parent_index(i);
	}
}

template<typename T>
T Heap<T>::pop()
{
	assert(!(vector.size() == 0));
	//Swap between the last and first, and 
	//remove the last element
	T temp = vector[0];
	vector[0] = vector[vector.size() - 1];
	vector.pop_back();

	//Sink the new 0th element
	//to its correct place
	//By comparaing its childerns,
	//and swaping with the biggest one
	unsigned int i = 0;
	int bIndex = big_child_index(i);
	while (i >= 0 && vector[i] > vector[bIndex]) {
		swap_with_parent(bIndex);
		i = bIndex;
		bIndex = big_child_index(i);
	}
	return temp;
}

template<typename T>
bool Heap<T>::is_empty() const
{
	return (vector.size() > 0) ? 0 : 1;

}

template<typename T>
int Heap<T>::size() const
{
	return vector.size();
}
#endif // !HEAP_H
