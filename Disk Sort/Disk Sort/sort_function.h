#ifndef SORT_FUNCTION_H
#define SORT_FUNCTION_H
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

template <class T>
void copy_array(T dest[], const T src[], unsigned int size) {
    for(int i=0;i<size;i++){
        dest[i] = src[i];
    }
}

//return true if a[] is in ascending order
template <class T>
bool verify(const T a[], unsigned int  size) {
	for (int i = 0; i < size-1; i++) {
		if (a[i] > a[i + 1])return false;
	}
	return true;
}

//return a string "SORTED" or "NOT SORTED" depending if a[] is sorted
template <class T>
string verifystr(const T a[], unsigned int  size) {
	return verify(a, size) ? "SORTED" : "NOT SORTED";
}

//print the array if status_only is true along with info on sortedness of a[]
template <class T>
void print_array(const T a[], int size, bool status_only = false) {
	cout << "[";
	for (int i = 0; i < size; i++) {
		cout << a[i];
		if (i + 1 != size) cout << ",";
	}
	cout << "]" << endl;
}

//print a[] from start to end
template <class T>
void print_array_segment(T a[], unsigned int start, unsigned int end) {
	if (end < start) return;
	cout << "[";
	for (int i = start; i < end; i++) {
		cout << a[i];
        if (i + 1 != end) cout << ",";
	}
	cout << "]" << endl;
}

template <class T>
void merge(T* a, int mid,int size) {
	T* L = new int[size / 2];
	T* R = new int[size-mid];

	int i = 0;
	int j = 0;
	int index = 0;
	for (int i = 0; i < mid; i++) {
		L[i] = a[i];
	}
	for (int i = 0; i < size - mid; i++) {
		R[i] = a[i + mid];
	}

	while (i < mid && j < size - mid) {
		if (L[i] <= R[j]) {
			a[index] = L[i];
			i++;
		}
		else {
			a[index] = R[j];
			j++;
		}
		index++;
	}

	for (int u = i; u < mid; u++) {
		a[index] = L[u];
		index++;
	}

	for (int u = j; u < size - mid; u++) {
		a[index] = R[u];
		index++;
	}
	delete[] L;
	delete[] R;
}

template <class T>
void merge_sort(T a[], unsigned int size) {
    if(size <= 1) return;
    int mid = size/2;
    merge_sort(a,mid);
    merge_sort(a+mid,size-mid);
	merge(a, mid, size);
}

template <class T>
void _swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template <class T>
void insertion_sort(T a[], unsigned int size) {
    for(int i=1;i<size;i++){
         for(int j=i;j>0;j--){
            if(a[j-1] > a[j])
                swap(a[j],a[j-1]);
            else
                break;
         }
    }
}

template<class T>
unsigned int partition(T a[], unsigned int n)
{
    int pivot = a[0];
    unsigned int big_index = 1;
    unsigned int small_index = n -1;
    unsigned int pivot_index;
    while(big_index <= small_index)
    {
        while(big_index != n && a[big_index] <= pivot)
            big_index++;
        while(a[small_index] > pivot)
            small_index--;
        if(big_index < small_index)
        {
            swap(a[big_index],a[small_index]);
        }
    }
    pivot_index = small_index;
    a[0] = a[pivot_index];
    a[pivot_index] = pivot;
    return pivot_index;
}

template<class T>
void quick_sort(T a[], unsigned int size)
{
    unsigned int pivot;
    unsigned int before_pivot;
    unsigned int after_pivot;

    if(size < 100) {
        insertion_sort(a,size);
    }
    else {
        if(size <= 1)return;
        pivot = partition(a,size);
        before_pivot = pivot;
        after_pivot = size - before_pivot - 1;
        quick_sort(a,before_pivot);
        quick_sort((a + pivot + 1), after_pivot);
    }
}

template <class T>
void bubble_sort(T a[], unsigned int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}
#endif // !SORT_FUNCTION_H
